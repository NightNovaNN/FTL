#include <stdio.h>
#include "borealis.h"
#include "corona/corona.h"

int main(void) {
    corona_ctx cctx;
    borealis_ctx bctx;

    corona_ctx_init(&cctx);
    borealis_init(&bctx);

    // load test file
    if (!corona_load_file(&cctx, "src/c/test/coronal_test/test.fl")) {
        printf("Corona load error: %s\n", cctx.error.msg);
        return 1;
    }

    if (!corona_run(&cctx)) {
        printf("Corona error: %s\n", cctx.error.msg);
        return 1;
    }

    const char *src = corona_output(&cctx);

    // run Borealis
    if (!borealis_run(&bctx, src)) {
        printf("Borealis error: %s\n", bctx.error.msg);
        return 1;
    }

    // dump IR
    printf("---- BOREALIS IR ----\n");
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
    printf("---------------------\n");

    borealis_free(&bctx);
    corona_ctx_free(&cctx);
    return 0;
}