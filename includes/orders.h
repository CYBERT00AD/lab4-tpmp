#ifndef ORDERS_H
#define ORDERS_H

#include "app.h"

void orders_list(AppContext *ctx);
void orders_add(AppContext *ctx);
void orders_update(AppContext *ctx);
void orders_delete(AppContext *ctx);

void report_orders_by_driver_period(AppContext *ctx);
void report_vehicle_stats(AppContext *ctx);
void report_driver_stats(AppContext *ctx);
void report_least_active_driver(AppContext *ctx);
void report_max_mileage_vehicle(AppContext *ctx);

void driver_show_own_orders_by_period(AppContext *ctx);
void driver_show_own_vehicle_stats(AppContext *ctx);

#endif