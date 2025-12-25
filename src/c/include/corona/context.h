#ifndef FTL_CORONA_CONTEXT_H
#define FTL_CORONA_CONTEXT_H

#include <stddef.h>
#include <stdint.h>

// ================================
// Input source buffer
// ================================

typedef struct {
    const char *data;   // owned by Corona
    size_t length;
    size_t pos;
} corona_source;

// ================================
// Include search paths
// ================================

typedef struct {
    const char **paths; // borrowed strings
    size_t count;
} corona_includes;

// ================================
// Error state (sticky)
// ================================

typedef struct {
    int code;
    const char *msg;    // static string
    size_t line;        // optional (0 if unknown)
    size_t col;         // optional (0 if unknown)
} corona_error;

// ================================
// Output buffer
// ================================

typedef struct {
    char *data;         // owned by Corona
    size_t len;
    size_t cap;
} corona_output_buf;

// ================================
// Corona context
// ================================

typedef struct {
    corona_source source;
    corona_includes includes;
    corona_error error;

    corona_output_buf output;

    // file currently being processed (for relative includes)
    const char *current_file;
} corona_ctx;

// ================================
// Lifecycle
// ================================

void corona_ctx_init(corona_ctx *ctx);
void corona_ctx_free(corona_ctx *ctx);

#endif // FTL_CORONA_CONTEXT_H
