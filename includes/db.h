#ifndef DB_H
#define DB_H

#include "app.h"

int db_open(AppContext *ctx, const char *db_path);
void db_close(AppContext *ctx);
void db_print_stmt(sqlite3_stmt *stmt);
int db_print_query(sqlite3 *db, const char *sql);

#endif