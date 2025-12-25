#include "include/corona/corona.h"
#include "include/borealis.h"
#include "include/quark.h"
#include <stdio.h>

int main(void) {
    corona_ctx cctx;
    borealis_ctx bctx;

    corona_ctx_init(&cctx);

    if (!corona_load_file(&cctx, "test.ftl")) {
        printf("Corona load failed\n");
        return 1;
    }

    if (!corona_run(&cctx)) {
        printf("Corona error: %s\n", corona_get_error(&cctx)->msg);
        return 1;
    }

    printf("---- Flattened Source ----\n");
    printf("%s\n", corona_output(&cctx));

    borealis_init(&bctx);
    borealis_run(&bctx, corona_output(&cctx));

    quark_optimize(&bctx);

    // dump IR
    FILE *f = fopen("temp.ftir", "w");
    for (size_t i = 0; i < bctx.ir.count; i++) {
        ftl_ir_inst *in = &bctx.ir.code[i];
        fprintf(f, "%u %u %u %u\n",
            in->opcode, in->a, in->b, in->c);
    }
    fclose(f);

    printf("IR written to temp.ftir\n");

    borealis_free(&bctx);
    corona_ctx_free(&cctx);

    return 0;
}
