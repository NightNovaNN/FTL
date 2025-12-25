#include "include/borealis.h"
#include "include/quark.h"
#include <stdio.h>
#include <string.h>

// optional fast backends
#ifdef FTL_USE_FORTRAN
extern int quark_fortran_opt(ftl_ir_inst *ir, size_t count);
#endif

#ifdef FTL_USE_ASM
extern int quark_asm_opt(ftl_ir_inst *ir, size_t count);
#endif

// ---------------- utils ----------------

static int is_imm(ftl_id x) {
    return FTL_IS_IMM(x);
}

static int imm_val(ftl_id x) {
    return (int)(x - FTL_IMM_BASE);
}

// ---------------- C reference passes ----------------

static int pass_const_fold(borealis_ctx *ctx) {
    int changed = 0;

    for (size_t i = 0; i < ctx->ir.count; i++) {
        ftl_ir_inst *in = &ctx->ir.code[i];

        if ((in->opcode == OP_ADD ||
             in->opcode == OP_SUB ||
             in->opcode == OP_MUL ||
             in->opcode == OP_DIV) &&
            is_imm(in->b) && is_imm(in->c)) {

            int x = imm_val(in->b);
            int y = imm_val(in->c);
            int r;

            if (in->opcode == OP_ADD) r = x + y;
            else if (in->opcode == OP_SUB) r = x - y;
            else if (in->opcode == OP_MUL) r = x * y;
            else {
                if (y == 0) continue;
                r = x / y;
            }

            in->opcode = OP_ASSIGN;
            in->b = 0;
            in->c = FTL_MAKE_IMM(r);
            changed = 1;
        }
    }

    return changed;
}

static int pass_dead_code(borealis_ctx *ctx) {
    int changed = 0;
    size_t symc = ctx->symbol_count;

    if (symc == 0)
        return 0;

    int used[symc];
    memset(used, 0, sizeof(used));

    // mark used operands
    for (size_t i = 0; i < ctx->ir.count; i++) {
        ftl_ir_inst *in = &ctx->ir.code[i];

        if (!FTL_IS_IMM(in->b) && in->b < symc)
            used[in->b] = 1;
        if (!FTL_IS_IMM(in->c) && in->c < symc)
            used[in->c] = 1;

        // never kill calls / returns / control
        if (in->opcode == OP_CALL ||
            in->opcode == OP_RETURN ||
            in->opcode == OP_RETURN_EXPR ||
            in->opcode == OP_IF ||
            in->opcode == OP_ELSE ||
            in->opcode == OP_ELSE_IF)
            used[in->a] = 1;
    }

    size_t w = 0;
    for (size_t i = 0; i < ctx->ir.count; i++) {
        ftl_ir_inst in = ctx->ir.code[i];

        if (in.a < symc &&
            !used[in.a] &&
            (in.opcode == OP_ASSIGN ||
             in.opcode == OP_ADD ||
             in.opcode == OP_SUB ||
             in.opcode == OP_MUL ||
             in.opcode == OP_DIV)) {
            changed = 1;
            continue;
        }

        ctx->ir.code[w++] = in;
    }

    ctx->ir.count = w;
    return changed;
}

static void quark_optimize_c(borealis_ctx *ctx) {
    int changed;
    int iter = 0;

    do {
        changed = 0;
        changed |= pass_const_fold(ctx);
        changed |= pass_dead_code(ctx);
        iter++;
    } while (changed && iter < 8);
}

// ---------------- driver ----------------

void quark_optimize(borealis_ctx *ctx) {
    int ok = 0;

#ifdef FTL_USE_ASM
    ok = quark_asm_opt(ctx->ir.code, ctx->ir.count);
#endif

#ifdef FTL_USE_FORTRAN
    if (!ok)
        ok = quark_fortran_opt(ctx->ir.code, ctx->ir.count);
#endif

    if (!ok) {
        fprintf(stderr,
            "warning: optimized backends unavailable, using reference C backend\n");
        quark_optimize_c(ctx);
    }
}
