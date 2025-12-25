#include <stdio.h>
#include "corona/corona.h"

int main(void) {
    corona_ctx ctx;

    corona_ctx_init(&ctx);

    if (!corona_load_file(&ctx, "src/c/test/coronal_test/test.fl")) {
        printf("load error: %s\n", ctx.error.msg);
        return 1;
    }

    if (!corona_run(&ctx)) {
        printf("corona error: %s\n", ctx.error.msg);
        return 1;
    }

    printf("---- CORONA OUTPUT ----\n");
    printf("%s\n", corona_output(&ctx));
    printf("-----------------------\n");

    corona_ctx_free(&ctx);
    return 0;
}
