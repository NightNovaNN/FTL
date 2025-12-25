#ifndef FTL_CORONA_H
#define FTL_CORONA_H

#include <stddef.h>
#include "context.h"

// =====================================
// Corona — Source Loader & Preprocessor
// =====================================
//
// Responsibilities:
// - Load source files
// - Resolve include(...) directives
// - Produce flattened source output
// - Report preprocessing errors
//
// =====================================

// Load a source file into the context
int corona_load_file(corona_ctx *ctx, const char *path);

// Register an include search path
int corona_add_include_path(corona_ctx *ctx, const char *path);

// Run preprocessing (expands includes)
// Mutates:
//   ctx->output
int corona_run(corona_ctx *ctx);

// Get flattened source output
// Valid only after corona_run
const char *corona_output(const corona_ctx *ctx);

// Get length of flattened output
size_t corona_output_len(const corona_ctx *ctx);

// Error helpers
int corona_has_error(const corona_ctx *ctx);
const corona_error *corona_get_error(const corona_ctx *ctx);

#endif // FTL_CORONA_H
