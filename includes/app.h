#ifndef APP_H
#define APP_H

#include <sqlite3.h>

typedef struct {
    sqlite3 *db;
    int user_id;
    int driver_id;
    char role[32];
    char login[64];
} AppContext;

#endif