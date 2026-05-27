#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "auth.h"
#include "drivers.h"
#include "vehicles.h"
#include "orders.h"
#include "utils.h"

static void admin_menu(AppContext *ctx) {
    int choice;

    while (1) {
        printf("\n=== ADMIN MENU ===\n");
        printf("1. List drivers\n");
        printf("2. Add driver\n");
        printf("3. Update driver\n");
        printf("4. Delete driver\n");
        printf("5. List vehicles\n");
        printf("6. Add vehicle\n");
        printf("7. Update vehicle\n");
        printf("8. Delete vehicle\n");
        printf("9. List orders\n");
        printf("10. Add order\n");
        printf("11. Update order\n");
        printf("12. Delete order\n");
        printf("13. Orders by driver and period\n");
        printf("14. Vehicle stats\n");
        printf("15. Driver stats\n");
        printf("16. Least active driver\n");
        printf("17. Max mileage vehicle\n");
        printf("0. Logout\n");

        choice = read_int("Choose: ");

        switch (choice) {
            case 1: drivers_list(ctx); break;
            case 2: drivers_add(ctx); break;
            case 3: drivers_update(ctx); break;
            case 4: drivers_delete(ctx); break;
            case 5: vehicles_list(ctx); break;
            case 6: vehicles_add(ctx); break;
            case 7: vehicles_update(ctx); break;
            case 8: vehicles_delete(ctx); break;
            case 9: orders_list(ctx); break;
            case 10: orders_add(ctx); break;
            case 11: orders_update(ctx); break;
            case 12: orders_delete(ctx); break;
            case 13: report_orders_by_driver_period(ctx); break;
            case 14: report_vehicle_stats(ctx); break;
            case 15: report_driver_stats(ctx); break;
            case 16: report_least_active_driver(ctx); break;
            case 17: report_max_mileage_vehicle(ctx); break;
            case 0: return;
            default: printf("Unknown option.\n"); break;
        }

        pause_screen();
    }
}

static void driver_menu(AppContext *ctx) {
    int choice;

    while (1) {
        printf("\n=== DRIVER MENU ===\n");
        printf("1. My data\n");
        printf("2. My vehicle\n");
        printf("3. My orders by period\n");
        printf("4. My vehicle stats\n");
        printf("0. Logout\n");

        choice = read_int("Choose: ");

        switch (choice) {
            case 1: driver_show_own_data(ctx); break;
            case 2: vehicle_show_own(ctx); break;
            case 3: driver_show_own_orders_by_period(ctx); break;
            case 4: driver_show_own_vehicle_stats(ctx); break;
            case 0: return;
            default: printf("Unknown option.\n"); break;
        }

        pause_screen();
    }
}

void main_menu(AppContext *ctx) {
    if (strcmp(ctx->role, "admin") == 0) {
        admin_menu(ctx);
    } else {
        driver_menu(ctx);
    }
}