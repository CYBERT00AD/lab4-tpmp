#include <stdio.h>
#include "drivers.h"
#include "db.h"
#include "utils.h"

void drivers_list(AppContext *ctx) {
    const char *sql =
        "SELECT id, employee_no, last_name, category, experience, address, birth_year, AUTOPARK_VECHICLES_id "
        "FROM AUTOPARK_DRIVERS "
        "ORDER BY id;";
    db_print_query(ctx->db, sql);
}

void drivers_add(AppContext *ctx) {
    sqlite3_stmt *stmt = NULL;
    const char *sql =
        "INSERT INTO AUTOPARK_DRIVERS "
        "(employee_no, last_name, category, experience, address, birth_year, AUTOPARK_VECHICLES_id) "
        "VALUES (?, ?, ?, ?, ?, ?, ?);";

    char employee_no[64];
    char last_name[64];
    char category[32];
    char address[128];
    int experience;
    int birth_year;
    int vehicle_id;

    read_line("employee_no: ", employee_no, sizeof(employee_no));
    read_line("last_name: ", last_name, sizeof(last_name));
    read_line("category: ", category, sizeof(category));
    experience = read_int("experience: ");
    read_line("address: ", address, sizeof(address));
    birth_year = read_int("birth_year: ");
    vehicle_id = read_int("vehicle_id: ");

    if (sqlite3_prepare_v2(ctx->db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(ctx->db));
        return;
    }

    sqlite3_bind_text(stmt, 1, employee_no, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, last_name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, category, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, experience);
    sqlite3_bind_text(stmt, 5, address, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 6, birth_year);
    sqlite3_bind_int(stmt, 7, vehicle_id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Insert driver failed: %s\n", sqlite3_errmsg(ctx->db));
    } else {
        printf("Driver added.\n");
    }

    sqlite3_finalize(stmt);
}

void drivers_update(AppContext *ctx) {
    sqlite3_stmt *stmt = NULL;
    const char *sql =
        "UPDATE AUTOPARK_DRIVERS "
        "SET employee_no = ?, last_name = ?, category = ?, experience = ?, address = ?, birth_year = ?, AUTOPARK_VECHICLES_id = ? "
        "WHERE id = ?;";

    int id = read_int("driver id: ");
    char employee_no[64];
    char last_name[64];
    char category[32];
    char address[128];
    int experience;
    int birth_year;
    int vehicle_id;

    read_line("employee_no: ", employee_no, sizeof(employee_no));
    read_line("last_name: ", last_name, sizeof(last_name));
    read_line("category: ", category, sizeof(category));
    experience = read_int("experience: ");
    read_line("address: ", address, sizeof(address));
    birth_year = read_int("birth_year: ");
    vehicle_id = read_int("vehicle_id: ");

    if (sqlite3_prepare_v2(ctx->db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(ctx->db));
        return;
    }

    sqlite3_bind_text(stmt, 1, employee_no, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, last_name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, category, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, experience);
    sqlite3_bind_text(stmt, 5, address, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 6, birth_year);
    sqlite3_bind_int(stmt, 7, vehicle_id);
    sqlite3_bind_int(stmt, 8, id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Update driver failed: %s\n", sqlite3_errmsg(ctx->db));
    } else {
        printf("Driver updated.\n");
    }

    sqlite3_finalize(stmt);
}

void drivers_delete(AppContext *ctx) {
    sqlite3_stmt *stmt = NULL;
    const char *sql = "DELETE FROM AUTOPARK_DRIVERS WHERE id = ?;";
    int id = read_int("driver id: ");

    if (sqlite3_prepare_v2(ctx->db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(ctx->db));
        return;
    }

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Delete driver failed: %s\n", sqlite3_errmsg(ctx->db));
    } else {
        printf("Driver deleted.\n");
    }

    sqlite3_finalize(stmt);
}

void driver_show_own_data(AppContext *ctx) {
    sqlite3_stmt *stmt = NULL;
    const char *sql =
        "SELECT id, employee_no, last_name, category, experience, address, birth_year, AUTOPARK_VECHICLES_id "
        "FROM AUTOPARK_DRIVERS "
        "WHERE id = ?;";

    if (sqlite3_prepare_v2(ctx->db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(ctx->db));
        return;
    }

    sqlite3_bind_int(stmt, 1, ctx->driver_id);
    db_print_stmt(stmt);
    sqlite3_finalize(stmt);
}