#include <stdio.h>
#include <string.h>
#include "auth.h"
#include "utils.h"

int auth_login(AppContext *ctx) {
    char login[64];
    char password[64];

    while (1) {
        sqlite3_stmt *stmt = NULL;
        const char *sql =
            "SELECT id, role, AUTOPARK_DRIVERS_id "
            "FROM AUTOPARK_USERS "
            "WHERE login = ? AND password = ?;";

        printf("\n=== AUTHORIZATION ===\n");
        read_line("Login (or 'exit'): ", login, sizeof(login));
        if (strcmp(login, "exit") == 0) {
            return 0;
        }

        read_line("Password: ", password, sizeof(password));

        if (sqlite3_prepare_v2(ctx->db, sql, -1, &stmt, NULL) != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(ctx->db));
            return 0;
        }

        sqlite3_bind_text(stmt, 1, login, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, password, -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            ctx->user_id = sqlite3_column_int(stmt, 0);
            ctx->driver_id = sqlite3_column_int(stmt, 2);

            const unsigned char *role = sqlite3_column_text(stmt, 1);

            strncpy(ctx->login, login, sizeof(ctx->login) - 1);
            ctx->login[sizeof(ctx->login) - 1] = '\0';

            if (role) {
                strncpy(ctx->role, (const char *)role, sizeof(ctx->role) - 1);
                ctx->role[sizeof(ctx->role) - 1] = '\0';
            } else {
                strcpy(ctx->role, "driver");
            }

            sqlite3_finalize(stmt);
            printf("Login successful. Role: %s\n", ctx->role);
            return 1;
        }

        sqlite3_finalize(stmt);
        printf("Invalid login or password.\n");
    }
}

void auth_logout(AppContext *ctx) {
    ctx->user_id = 0;
    ctx->driver_id = 0;
    ctx->role[0] = '\0';
    ctx->login[0] = '\0';
}