#include <stdio.h>
#include "db.h"

int db_open(AppContext *ctx, const char *db_path) {
    if (sqlite3_open(db_path, &ctx->db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(ctx->db));
        return 0;
    }

    sqlite3_exec(ctx->db, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);
    return 1;
}

void db_close(AppContext *ctx) {
    if (ctx->db) {
        sqlite3_close(ctx->db);
        ctx->db = NULL;
    }
}

void db_print_stmt(sqlite3_stmt *stmt) {
    int cols = sqlite3_column_count(stmt);
    int rc;
    int has_rows = 0;

    for (int i = 0; i < cols; i++) {
        printf("%-22s", sqlite3_column_name(stmt, i));
    }
    printf("\n");

    for (int i = 0; i < cols; i++) {
        printf("%-22s", "--------------------");
    }
    printf("\n");

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        has_rows = 1;
        for (int i = 0; i < cols; i++) {
            const unsigned char *text = sqlite3_column_text(stmt, i);
            printf("%-22s", text ? (const char *)text : "NULL");
        }
        printf("\n");
    }

    if (!has_rows) {
        printf("No rows found.\n");
    }

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQLite step error: %s\n", sqlite3_errstr(rc));
    }
}

int db_print_query(sqlite3 *db, const char *sql) {
    sqlite3_stmt *stmt = NULL;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    db_print_stmt(stmt);
    sqlite3_finalize(stmt);
    return 1;
}