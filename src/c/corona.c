#include "include/corona/corona.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CORONA_BUF_INIT 4096

// ---------------- buffer helpers ----------------

static int buf_init(corona_output_buf *b) {
    b->cap = CORONA_BUF_INIT;
    b->len = 0;
    b->data = malloc(b->cap);
    if (!b->data) return 0;
    b->data[0] = '\0';
    return 1;
}

static int buf_grow(corona_output_buf *b, size_t need) {
    if (b->len + need < b->cap) return 1;

    size_t new_cap = b->cap * 2;
    while (new_cap < b->len + need)
        new_cap *= 2;

    char *n = realloc(b->data, new_cap);
    if (!n) return 0;

    b->data = n;
    b->cap = new_cap;
    return 1;
}

static int buf_append(corona_output_buf *b, const char *s, size_t n) {
    if (!buf_grow(b, n + 1)) return 0;
    memcpy(b->data + b->len, s, n);
    b->len += n;
    b->data[b->len] = '\0';
    return 1;
}

// ---------------- error helpers ----------------

static void corona_set_error(corona_ctx *ctx, int code, const char *msg) {
    if (ctx->error.code) return;   // sticky
    ctx->error.code = code;
    ctx->error.msg = msg;
}

// ---------------- file helpers ----------------

static char *read_file(const char *path, size_t *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    rewind(f);

    char *buf = malloc((size_t)sz + 1);
    if (!buf) {
        fclose(f);
        return NULL;
    }

    fread(buf, 1, (size_t)sz, f);
    buf[sz] = '\0';
    fclose(f);

    if (out_len) *out_len = (size_t)sz;
    return buf;
}

// build path relative to current file
static int build_relative_path(
    char *out,
    size_t out_sz,
    const char *base,
    const char *file
) {
    const char *slash = strrchr(base, '/');
#ifdef _WIN32
    const char *bslash = strrchr(base, '\\');
    if (!slash || (bslash && bslash > slash)) slash = bslash;
#endif

    if (!slash)
        return snprintf(out, out_sz, "%s", file) < (int)out_sz;

    size_t dir_len = (size_t)(slash - base + 1);
    if (dir_len + strlen(file) >= out_sz) return 0;

    memcpy(out, base, dir_len);
    strcpy(out + dir_len, file);
    return 1;
}

// ---------------- preprocessing ----------------

static int corona_process_source(
    corona_ctx *ctx,
    const char *src,
    const char *current_file
) {
    const char *p = src;

    while (*p) {

        // include(...)
        if (strncmp(p, "include(", 8) == 0) {
            p += 8;

            while (*p == ' ' || *p == '"') p++;
            const char *start = p;

            while (*p && *p != '"' && *p != ')') p++;
            if (*p == '\0') {
                corona_set_error(ctx, 2, "malformed include");
                return 0;
            }

            size_t len = (size_t)(p - start);
            char file[256];
            memcpy(file, start, len);
            file[len] = '\0';

            while (*p && *p != ')') p++;
            if (*p != ')') {
                corona_set_error(ctx, 2, "malformed include");
                return 0;
            }
            p++; // skip ')'

            char fullpath[512];
            if (!build_relative_path(
                    fullpath,
                    sizeof(fullpath),
                    current_file,
                    file)) {
                corona_set_error(ctx, 3, "include path too long");
                return 0;
            }

            size_t flen;
            char *inc = read_file(fullpath, &flen);
            if (!inc) {
                corona_set_error(ctx, 4, "include file not found");
                return 0;
            }

            if (!corona_process_source(ctx, inc, fullpath)) {
                free(inc);
                return 0;
            }

            free(inc);
            continue;
        }

        // normal char
        if (!buf_append(&ctx->output, p, 1)) {
            corona_set_error(ctx, 5, "out of memory");
            return 0;
        }

        p++;
    }

    return 1;
}

// ---------------- public API ----------------

void corona_ctx_init(corona_ctx *ctx) {
    memset(ctx, 0, sizeof(*ctx));
}

void corona_ctx_free(corona_ctx *ctx) {
    free((void *)ctx->source.data);
    ctx->source.data = NULL;

    free(ctx->output.data);
    ctx->output.data = NULL;
    ctx->output.len = ctx->output.cap = 0;

    free(ctx->includes.paths);
    ctx->includes.paths = NULL;
    ctx->includes.count = 0;
}

int corona_add_include_path(corona_ctx *ctx, const char *path) {
    size_t n = ctx->includes.count + 1;
    const char **p = realloc(ctx->includes.paths, n * sizeof(char *));
    if (!p) return 0;

    p[n - 1] = path;
    ctx->includes.paths = p;
    ctx->includes.count = n;
    return 1;
}

int corona_load_file(corona_ctx *ctx, const char *path) {
    size_t len = 0;
    char *src = read_file(path, &len);
    if (!src) {
        corona_set_error(ctx, 1, "failed to read source file");
        return 0;
    }

    ctx->source.data = src;
    ctx->source.length = len;
    ctx->source.pos = 0;
    ctx->current_file = path;
    return 1;
}

int corona_run(corona_ctx *ctx) {
    if (!buf_init(&ctx->output)) {
        corona_set_error(ctx, 6, "out of memory");
        return 0;
    }

    if (!corona_process_source(
            ctx,
            ctx->source.data,
            ctx->current_file)) {
        return 0;
    }

    return 1;
}

const char *corona_output(const corona_ctx *ctx) {
    return ctx->output.data;
}

size_t corona_output_len(const corona_ctx *ctx) {
    return ctx->output.len;
}

int corona_has_error(const corona_ctx *ctx) {
    return ctx->error.code != 0;
}

const corona_error *corona_get_error(const corona_ctx *ctx) {
    return &ctx->error;
}
