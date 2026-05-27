#include <stdio.h>
#include <string.h>
#include "app.h"
#include "db.h"
#include "auth.h"
#include "menu.h"

int main(int argc, char *argv[]) {
    AppContext ctx;
    const char *db_path = "data/autopark.db";

    memset(&ctx, 0, sizeof(ctx));

    if (argc > 1) {
        db_path = argv[1];
    }

    if (!db_open(&ctx, db_path)) {
        return 1;
    }

    while (auth_login(&ctx)) {
        main_menu(&ctx);
        auth_logout(&ctx);
    }

    db_close(&ctx);
    printf("Bye!\n");
    return 0;
}