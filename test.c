#include <stdio.h>
#include <string.h>

#include "borealis.h"
#include "quark.h"
#include "corona/corona.h"

int main(void) {
    // ---------------- inline FTL source ----------------
    const char *ftl_src =
        "int a = 10;\n"
        "int b = 20;\n"
        "c = a + b;\n"
        "if a > 0 { echof(c); }\n";

    // ---------------- contexts ----------------
    corona_ctx   cctx;
    borealis_ctx bctx;

    corona_ctx_init(&cctx);
    borealis_init(&bctx);

    // Manually inject source (no file IO)
    cctx.source.data   = ftl_src;
    cctx.source.length = strlen(ftl_src);
    cctx.current_file  = "<inline>";

    // Run Corona (still needed for consistency)
    if (!corona_run(&cctx)) {
        printf("Corona error: %s\n", cctx.error.msg);
        return 1;
    }

    // Run Borealis
    if (!borealis_run(&bctx, corona_output(&cctx))) {
        printf("Borealis failed\n");
        return 1;
    }

    // Optimize
    quark_optimize(&bctx);

    // ---------------- dump IR ----------------
    printf("---- FTL IR ----\n");
    for (size_t i = 0; i < bctx.ir.count; i++) {
        ftl_ir_inst *in = &bctx.ir.code[i];
        printf(
            "%zu: OP=%d A=%u B=%u C=%u\n",
            i,
            in->opcode,
            in->a,
            in->b,
            in->c
        );
    }
    printf("----------------\n");

    borealis_free(&bctx);
    corona_ctx_free(&cctx);

    return 0;
}
