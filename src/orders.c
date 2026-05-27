#include <stdio.h>
#include "orders.h"
#include "db.h"
#include "utils.h"

static int get_vehicle_capacity(AppContext *ctx, int vehicle_id, double *capacity) {
    sqlite3_stmt *stmt = NULL;
    const char *sql = "SELECT capacity_kg FROM AUTOPARK_VEHICLES WHERE id = ?;";

    if (sqlite3_prepare_v2(ctx->db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(ctx->db));
        return 0;
    }

    sqlite3_bind_int(stmt, 1, vehicle_id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *capacity = sqlite3_column_double(stmt, 0);
        sqlite3_finalize(stmt);
        return 1;
    }

    sqlite3_finalize(stmt);
    return 0;
}

void orders_list(AppContext *ctx) {
    const char *sql =
        "SELECT o.id, o.order_date, d.last_name, v.plate_no, o.distance_km, o.cargo_mass_kg, o.price "
        "FROM AUTOPARK_ORDERS o "
        "JOIN AUTOPARK_DRIVERS d ON d.id = o.AUTOPARK_DRIVERS_id "
        "JOIN AUTOPARK_VEHICLES v ON v.id = o.AUTOPARK_VECHICLES_id "
        "ORDER BY o.id;";
    db_print_query(ctx->db, sql);
}

void orders_add(AppContext *ctx) {
    sqlite3_stmt *stmt = NULL;
    const char *sql =
        "INSERT INTO AUTOPARK_ORDERS "
        "(order_date, distance_km, cargo_mass_kg, price, AUTOPARK_DRIVERS_id, AUTOPARK_VECHICLES_id) "
        "VALUES (?, ?, ?, ?, ?, ?);";

    int order_date;
    double distance_km;
    double cargo_mass_kg;
    double price;
    int driver_id;
    int vehicle_id;
    double capacity = 0.0;

    order_date = read_int("order_date (YYYYMMDD): ");
    distance_km = read_double("distance_km: ");
    cargo_mass_kg = read_double("cargo_mass_kg: ");
    price = read_double("price: ");
    driver_id = read_int("driver_id: ");
    vehicle_id = read_int("vehicle_id: ");

    if (!get_vehicle_capacity(ctx, vehicle_id, &capacity)) {
        printf("Vehicle not found.\n");
        return;
    }

    if (cargo_mass_kg > capacity) {
        printf("Error: cargo mass is greater than vehicle capacity.\n");
        return;
    }

    if (sqlite3_prepare_v2(ctx->db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(ctx->db));
        return;
    }

    sqlite3_bind_int(stmt, 1, order_date);
    sqlite3_bind_double(stmt, 2, distance_km);
    sqlite3_bind_double(stmt, 3, cargo_mass_kg);
    sqlite3_bind_double(stmt, 4, price);
    sqlite3_bind_int(stmt, 5, driver_id);
    sqlite3_bind_int(stmt, 6, vehicle_id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Insert order failed: %s\n", sqlite3_errmsg(ctx->db));
    } else {
        printf("Order added.\n");
    }

    sqlite3_finalize(stmt);
}

void orders_update(AppContext *ctx) {
    sqlite3_stmt *stmt = NULL;
    const char *sql =
        "UPDATE AUTOPARK_ORDERS "
        "SET order_date = ?, distance_km = ?, cargo_mass_kg = ?, price = ?, AUTOPARK_DRIVERS_id = ?, AUTOPARK_VECHICLES_id = ? "
        "WHERE id = ?;";

    int id;
    int order_date;
    double distance_km;
    double cargo_mass_kg;
    double price;
    int driver_id;
    int vehicle_id;
    double capacity = 0.0;

    id = read_int("order id: ");
    order_date = read_int("order_date (YYYYMMDD): ");
    distance_km = read_double("distance_km: ");
    cargo_mass_kg = read_double("cargo_mass_kg: ");
    price = read_double("price: ");
    driver_id = read_int("driver_id: ");
    vehicle_id = read_int("vehicle_id: ");

    if (!get_vehicle_capacity(ctx, vehicle_id, &capacity)) {
        printf("Vehicle not found.\n");
        return;
    }

    if (cargo_mass_kg > capacity) {
        printf("Error: cargo mass is greater than vehicle capacity.\n");
        return;
    }

    if (sqlite3_prepare_v2(ctx->db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(ctx->db));
        return;
    }

    sqlite3_bind_int(stmt, 1, order_date);
    sqlite3_bind_double(stmt, 2, distance_km);
    sqlite3_bind_double(stmt, 3, cargo_mass_kg);
    sqlite3_bind_double(stmt, 4, price);
    sqlite3_bind_int(stmt, 5, driver_id);
    sqlite3_bind_int(stmt, 6, vehicle_id);
    sqlite3_bind_int(stmt, 7, id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Update order failed: %s\n", sqlite3_errmsg(ctx->db));
    } else {
        printf("Order updated.\n");
    }

    sqlite3_finalize(stmt);
}

void orders_delete(AppContext *ctx) {
    sqlite3_stmt *stmt = NULL;
    const char *sql = "DELETE FROM AUTOPARK_ORDERS WHERE id = ?;";
    int id = read_int("order id: ");

    if (sqlite3_prepare_v2(ctx->db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(ctx->db));
        return;
    }

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Delete order failed: %s\n", sqlite3_errmsg(ctx->db));
    } else {
        printf("Order deleted.\n");
    }

    sqlite3_finalize(stmt);
}

void report_orders_by_driver_period(AppContext *ctx) {
    sqlite3_stmt *stmt = NULL;
    const char *sql =
        "SELECT o.order_date, d.last_name, v.plate_no, o.distance_km, o.cargo_mass_kg, o.price "
        "FROM AUTOPARK_ORDERS o "
        "JOIN AUTOPARK_DRIVERS d ON d.id = o.AUTOPARK_DRIVERS_id "
        "JOIN AUTOPARK_VEHICLES v ON v.id = o.AUTOPARK_VECHICLES_id "
        "WHERE d.id = ? AND o.order_date BETWEEN ? AND ? "
        "ORDER BY o.order_date;";

    int driver_id = read_int("driver_id: ");
    int start_date = read_int("start_date (YYYYMMDD): ");
    int end_date = read_int("end_date (YYYYMMDD): ");

    if (sqlite3_prepare_v2(ctx->db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(ctx->db));
        return;
    }

    sqlite3_bind_int(stmt, 1, driver_id);
    sqlite3_bind_int(stmt, 2, start_date);
    sqlite3_bind_int(stmt, 3, end_date);

    db_print_stmt(stmt);
    sqlite3_finalize(stmt);
}

void report_vehicle_stats(AppContext *ctx) {
    sqlite3_stmt *stmt = NULL;
    const char *sql =
        "SELECT v.id, v.plate_no, v.brand, "
        "COALESCE(v.mileage_at_purchase + SUM(o.distance_km), v.mileage_at_purchase) AS total_mileage, "
        "COALESCE(SUM(o.cargo_mass_kg), 0) AS total_cargo "
        "FROM AUTOPARK_VEHICLES v "
        "LEFT JOIN AUTOPARK_ORDERS o ON o.AUTOPARK_VECHICLES_id = v.id "
        "WHERE v.id = ? "
        "GROUP BY v.id, v.plate_no, v.brand, v.mileage_at_purchase;";

    int vehicle_id = read_int("vehicle_id: ");

    if (sqlite3_prepare_v2(ctx->db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(ctx->db));
        return;
    }

    sqlite3_bind_int(stmt, 1, vehicle_id);
    db_print_stmt(stmt);
    sqlite3_finalize(stmt);
}

void report_driver_stats(AppContext *ctx) {
    const char *sql =
        "SELECT d.id, d.last_name, "
        "COUNT(o.id) AS total_trips, "
        "COALESCE(SUM(o.cargo_mass_kg), 0) AS total_cargo, "
        "COALESCE(SUM(o.price * COALESCE((SELECT driver_percent FROM AUTOPARK_CONFIG LIMIT 1), 20) / 100.0), 0) AS earnings "
        "FROM AUTOPARK_DRIVERS d "
        "LEFT JOIN AUTOPARK_ORDERS o ON o.AUTOPARK_DRIVERS_id = d.id "
        "GROUP BY d.id, d.last_name "
        "ORDER BY d.id;";
    db_print_query(ctx->db, sql);
}

void report_least_active_driver(AppContext *ctx) {
    const char *sql =
        "SELECT d.id, d.last_name, COUNT(o.id) AS total_trips, "
        "COALESCE(SUM(o.price * COALESCE((SELECT driver_percent FROM AUTOPARK_CONFIG LIMIT 1), 20) / 100.0), 0) AS earnings "
        "FROM AUTOPARK_DRIVERS d "
        "LEFT JOIN AUTOPARK_ORDERS o ON o.AUTOPARK_DRIVERS_id = d.id "
        "GROUP BY d.id, d.last_name "
        "ORDER BY total_trips ASC, d.id ASC "
        "LIMIT 1;";
    db_print_query(ctx->db, sql);
}

void report_max_mileage_vehicle(AppContext *ctx) {
    const char *sql =
        "SELECT v.id, v.plate_no, v.brand, "
        "COALESCE(v.mileage_at_purchase + SUM(o.distance_km), v.mileage_at_purchase) AS total_mileage "
        "FROM AUTOPARK_VEHICLES v "
        "LEFT JOIN AUTOPARK_ORDERS o ON o.AUTOPARK_VECHICLES_id = v.id "
        "GROUP BY v.id, v.plate_no, v.brand, v.mileage_at_purchase "
        "ORDER BY total_mileage DESC "
        "LIMIT 1;";
    db_print_query(ctx->db, sql);
}

void driver_show_own_orders_by_period(AppContext *ctx) {
    sqlite3_stmt *stmt = NULL;
    const char *sql =
        "SELECT o.order_date, v.plate_no, o.distance_km, o.cargo_mass_kg, o.price "
        "FROM AUTOPARK_ORDERS o "
        "JOIN AUTOPARK_VEHICLES v ON v.id = o.AUTOPARK_VECHICLES_id "
        "WHERE o.AUTOPARK_DRIVERS_id = ? AND o.order_date BETWEEN ? AND ? "
        "ORDER BY o.order_date;";

    int start_date = read_int("start_date (YYYYMMDD): ");
    int end_date = read_int("end_date (YYYYMMDD): ");

    if (sqlite3_prepare_v2(ctx->db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(ctx->db));
        return;
    }

    sqlite3_bind_int(stmt, 1, ctx->driver_id);
    sqlite3_bind_int(stmt, 2, start_date);
    sqlite3_bind_int(stmt, 3, end_date);

    db_print_stmt(stmt);
    sqlite3_finalize(stmt);
}

void driver_show_own_vehicle_stats(AppContext *ctx) {
    sqlite3_stmt *stmt = NULL;
    const char *sql =
        "SELECT v.id, v.plate_no, v.brand, "
        "COALESCE(v.mileage_at_purchase + SUM(o.distance_km), v.mileage_at_purchase) AS total_mileage, "
        "COALESCE(SUM(o.cargo_mass_kg), 0) AS total_cargo "
        "FROM AUTOPARK_DRIVERS d "
        "JOIN AUTOPARK_VEHICLES v ON v.id = d.AUTOPARK_VECHICLES_id "
        "LEFT JOIN AUTOPARK_ORDERS o ON o.AUTOPARK_VECHICLES_id = v.id "
        "WHERE d.id = ? "
        "GROUP BY v.id, v.plate_no, v.brand, v.mileage_at_purchase;";

    if (sqlite3_prepare_v2(ctx->db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(ctx->db));
        return;
    }

    sqlite3_bind_int(stmt, 1, ctx->driver_id);
    db_print_stmt(stmt);
    sqlite3_finalize(stmt);
}