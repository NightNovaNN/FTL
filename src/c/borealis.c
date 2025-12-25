#include "include/borealis.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define INIT_IR_CAP 128
#define INIT_SYM_CAP 64

// ---------------- utils ----------------

static char *trim(char *s) {
    while (isspace(*s)) s++;
    char *e = s + strlen(s);
    while (e > s && isspace(*(e - 1))) --e;
    *e = 0;
    return s;
}

static int is_empty(const char *s) {
    return !s || !*s;
}

// ---------------- IR / symbol mgmt ----------------

static void ir_grow(borealis_ctx *ctx) {
    if (ctx->ir.count < ctx->ir.capacity) return;
    ctx->ir.capacity *= 2;
    ctx->ir.code = realloc(
        ctx->ir.code,
        ctx->ir.capacity * sizeof(ftl_ir_inst)
    );
}

static void sym_grow(borealis_ctx *ctx) {
    if (ctx->symbol_count < ctx->symbol_capacity) return;
    ctx->symbol_capacity *= 2;
    ctx->symbols = realloc(
        ctx->symbols,
        ctx->symbol_capacity * sizeof(ftl_symbol)
    );
}

void borealis_init(borealis_ctx *ctx) {
    memset(ctx, 0, sizeof(*ctx));

    ctx->ir.capacity = INIT_IR_CAP;
    ctx->ir.code = calloc(ctx->ir.capacity, sizeof(ftl_ir_inst));

    ctx->symbol_capacity = INIT_SYM_CAP;
    ctx->symbols = calloc(ctx->symbol_capacity, sizeof(ftl_symbol));
}

void borealis_free(borealis_ctx *ctx) {
    for (size_t i = 0; i < ctx->symbol_count; i++)
        free((void *)ctx->symbols[i].name);

    free(ctx->symbols);
    free(ctx->ir.code);
}

// ---------------- symbols ----------------

ftl_id borealis_symbol_new(borealis_ctx *ctx, const char *name, ftl_type type) {
    for (size_t i = 0; i < ctx->symbol_count; i++) {
        if (strcmp(ctx->symbols[i].name, name) == 0)
            return ctx->symbols[i].id;
    }

    sym_grow(ctx);

    ftl_id id = (ftl_id)ctx->symbol_count;
    ctx->symbols[id] = (ftl_symbol){
        id,
        strdup(name),
        type
    };
    ctx->symbol_count++;
    return id;
}

ftl_symbol *borealis_symbol_get(borealis_ctx *ctx, ftl_id id) {
    if (id >= ctx->symbol_count) return NULL;
    return &ctx->symbols[id];
}

// ---------------- IR emit ----------------

void borealis_emit(
    borealis_ctx *ctx,
    ftl_opcode_borealis op,
    ftl_id a,
    ftl_id b,
    ftl_id c
) {
    ir_grow(ctx);
    ctx->ir.code[ctx->ir.count++] = (ftl_ir_inst){ op, a, b, c };
}

// ---------------- parsing helpers ----------------

static void parse_decl(borealis_ctx *ctx, char *t) {
    char type[16], name[32];
    int val;

    if (sscanf(t, "%15s %31s = %d;", type, name, &val) != 3)
        return;

    ftl_id id = borealis_symbol_new(ctx, name, 1);
    borealis_emit(ctx, OP_VAR_DECL, id, 1, FTL_MAKE_IMM(val));
}

static void parse_assign(borealis_ctx *ctx, char *t) {
    char lhs[32];
    int val;

    if (sscanf(t, "%31s = %d;", lhs, &val) != 2)
        return;

    ftl_id id = borealis_symbol_new(ctx, lhs, 1);
    borealis_emit(ctx, OP_ASSIGN, id, 0, FTL_MAKE_IMM(val));
}

static void parse_binop(borealis_ctx *ctx, char *t) {
    char dst[32], a[32], b[32], op;

    if (sscanf(t, "%31s = %31s %c %31s;", dst, a, &op, b) != 4)
        return;

    ftl_id d = borealis_symbol_new(ctx, dst, 1);
    ftl_id x = borealis_symbol_new(ctx, a, 1);
    ftl_id y = borealis_symbol_new(ctx, b, 1);

    switch (op) {
        case '+': borealis_emit(ctx, OP_ADD, d, x, y); break;
        case '-': borealis_emit(ctx, OP_SUB, d, x, y); break;
        case '*': borealis_emit(ctx, OP_MUL, d, x, y); break;
        case '/': borealis_emit(ctx, OP_DIV, d, x, y); break;
    }
}

static void parse_return(borealis_ctx *ctx, char *t) {
    char a[32], b[32], op;

    if (sscanf(t, "return %31s %c %31s;", a, &op, b) == 3) {
        borealis_emit(
            ctx,
            OP_RETURN_EXPR,
            borealis_symbol_new(ctx, a, 1),
            (ftl_id)op,
            borealis_symbol_new(ctx, b, 1)
        );
    }
}

static void parse_call(borealis_ctx *ctx, char *t) {
    char fn[32];

    if (sscanf(t, "%31[^ (](", fn) != 1)
        return;

    if (!strchr(t, ')'))
        return;

    borealis_emit(
        ctx,
        OP_CALL,
        borealis_symbol_new(ctx, fn, 0),
        0, 0
    );
}

static void parse_ctrl(borealis_ctx *ctx, char *t) {
    if (strncmp(t, "if ", 3) == 0)
        borealis_emit(ctx, OP_IF, 0, 0, 0);
    else if (strncmp(t, "else if ", 8) == 0)
        borealis_emit(ctx, OP_ELSE_IF, 0, 0, 0);
    else if (strncmp(t, "else", 4) == 0)
        borealis_emit(ctx, OP_ELSE, 0, 0, 0);
    else if (strncmp(t, "fn ", 3) == 0)
        borealis_emit(ctx, OP_FUNC_BEGIN, 0, 0, 0);
}

// ---------------- main entry ----------------

int borealis_run(borealis_ctx *ctx, const char *src) {
    char *copy = strdup(src);
    if (!copy) return 0;

    char *line = strtok(copy, "\n");

    while (line) {
        char *t = trim(line);

        if (is_empty(t)) {
            line = strtok(NULL, "\n");
            continue;
        }

        // ignore include suffix
        if (t[0] == ':') {
            line = strtok(NULL, "\n");
            continue;
        }

        // order matters
        parse_decl(ctx, t);
        parse_binop(ctx, t);
        parse_assign(ctx, t);

        if (strncmp(t, "return", 6) == 0)
            parse_return(ctx, t);
        else if (strchr(t, '('))
            parse_call(ctx, t);
        else
            parse_ctrl(ctx, t);

        line = strtok(NULL, "\n");
    }

    free(copy);
    return 1;
}
