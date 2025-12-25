#ifndef FTL_BOREALIS_H
#define FTL_BOREALIS_H

#include <stdint.h>
#include <stddef.h>
#include "unit.h"

// ================================
// Core ID types
// ================================

// IDs used across IR and symbol table
typedef uint32_t ftl_id;
typedef uint16_t ftl_type;

// Reserved range for immediates
#define FTL_IMM_BASE 100000u
#define FTL_IS_IMM(x) ((x) >= FTL_IMM_BASE)
#define FTL_MAKE_IMM(v) ((ftl_id)(FTL_IMM_BASE + (v)))

// ================================
// IR instruction
// ================================

typedef struct {
    ftl_opcode_borealis opcode;
    ftl_id a;   // destination / primary
    ftl_id b;   // operand / meta / imm
    ftl_id c;   // operand / imm
} ftl_ir_inst;

// IR program buffer
typedef struct {
    ftl_ir_inst *code;
    size_t count;
    size_t capacity;
} ftl_ir_program;

// ================================
// Symbol system
// ================================

typedef struct {
    ftl_id id;
    const char *name;   // owned by Borealis
    ftl_type type;
} ftl_symbol;

// ================================
// Error handling
// ================================

typedef struct {
    int code;
    const char *msg;
} borealis_error;

// ================================
// Borealis context
// ================================

typedef struct {
    // IR output
    ftl_ir_program ir;

    // Symbol table
    ftl_symbol *symbols;
    size_t symbol_count;
    size_t symbol_capacity;

    // Error state (non-fatal, sticky)
    borealis_error error;
} borealis_ctx;

// ================================
// Lifecycle
// ================================

void borealis_init(borealis_ctx *ctx);
void borealis_free(borealis_ctx *ctx);

// ================================
// Main entry
// ================================

// Parses flattened source into IR
// Assumes Corona already ran
int borealis_run(borealis_ctx *ctx, const char *source);

// ================================
// IR emission
// ================================

void borealis_emit(
    borealis_ctx *ctx,
    ftl_opcode_borealis opcode,
    ftl_id a,
    ftl_id b,
    ftl_id c
);

// ================================
// Symbol handling
// ================================

// Create or retrieve a symbol
ftl_id borealis_symbol_new(
    borealis_ctx *ctx,
    const char *name,
    ftl_type type
);

// Get symbol by ID (NULL if invalid)
ftl_symbol *borealis_symbol_get(
    borealis_ctx *ctx,
    ftl_id id
);

// ================================
// Error helpers
// ================================

static inline int borealis_has_error(const borealis_ctx *ctx) {
    return ctx->error.code != 0;
}

static inline const char *borealis_error_msg(const borealis_ctx *ctx) {
    return ctx->error.msg;
}

#endif // FTL_BOREALIS_H
