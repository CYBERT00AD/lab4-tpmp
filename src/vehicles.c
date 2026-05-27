#include <stdio.h>
#include "vehicles.h"
#include "db.h"
#include "utils.h"

void vehicles_list(AppContext *ctx) {
    const char *sql =
        "SELECT id, plate_no, brand, mileage_at_purchase, capacity_kg "
        "FROM AUTOPARK_VEHICLES "
        "ORDER BY id;";
    db_print_query(ctx->db, sql);
}

void vehicles_add(AppContext *ctx) {
    sqlite3_stmt *stmt = NULL;
    const char *sql =
        "INSERT INTO AUTOPARK_VEHICLES "
        "(plate_no, brand, mileage_at_purchase, capacity_kg) "
        "VALUES (?, ?, ?, ?);";

    char plate_no[64];
    char brand[64];
    int mileage;
    double capacity;

    read_line("plate_no: ", plate_no, sizeof(plate_no));
    read_line("brand: ", brand, sizeof(brand));
    mileage = read_int("mileage_at_purchase: ");
    capacity = read_double("capacity_kg: ");

    if (sqlite3_prepare_v2(ctx->db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(ctx->db));
        return;
    }

    sqlite3_bind_text(stmt, 1, plate_no, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, brand, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, mileage);
    sqlite3_bind_double(stmt, 4, capacity);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Insert vehicle failed: %s\n", sqlite3_errmsg(ctx->db));
    } else {
        printf("Vehicle added.\n");
    }

    sqlite3_finalize(stmt);
}

void vehicles_update(AppContext *ctx) {
    sqlite3_stmt *stmt = NULL;
    const char *sql =
        "UPDATE AUTOPARK_VEHICLES "
        "SET plate_no = ?, brand = ?, mileage_at_purchase = ?, capacity_kg = ? "
        "WHERE id = ?;";

    int id = read_int("vehicle id: ");
    char plate_no[64];
    char brand[64];
    int mileage;
    double capacity;

    read_line("plate_no: ", plate_no, sizeof(plate_no));
    read_line("brand: ", brand, sizeof(brand));
    mileage = read_int("mileage_at_purchase: ");
    capacity = read_double("capacity_kg: ");

    if (sqlite3_prepare_v2(ctx->db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(ctx->db));
        return;
    }

    sqlite3_bind_text(stmt, 1, plate_no, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, brand, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, mileage);
    sqlite3_bind_double(stmt, 4, capacity);
    sqlite3_bind_int(stmt, 5, id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Update vehicle failed: %s\n", sqlite3_errmsg(ctx->db));
    } else {
        printf("Vehicle updated.\n");
    }

    sqlite3_finalize(stmt);
}

void vehicles_delete(AppContext *ctx) {
    sqlite3_stmt *stmt = NULL;
    const char *sql = "DELETE FROM AUTOPARK_VEHICLES WHERE id = ?;";
    int id = read_int("vehicle id: ");

    if (sqlite3_prepare_v2(ctx->db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(ctx->db));
        return;
    }

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Delete vehicle failed: %s\n", sqlite3_errmsg(ctx->db));
    } else {
        printf("Vehicle deleted.\n");
    }

    sqlite3_finalize(stmt);
}

void vehicle_show_own(AppContext *ctx) {
    sqlite3_stmt *stmt = NULL;
    const char *sql =
        "SELECT v.id, v.plate_no, v.brand, v.mileage_at_purchase, v.capacity_kg "
        "FROM AUTOPARK_VEHICLES v "
        "JOIN AUTOPARK_DRIVERS d ON d.AUTOPARK_VECHICLES_id = v.id "
        "WHERE d.id = ?;";

    if (sqlite3_prepare_v2(ctx->db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(ctx->db));
        return;
    }

    sqlite3_bind_int(stmt, 1, ctx->driver_id);
    db_print_stmt(stmt);
    sqlite3_finalize(stmt);
}