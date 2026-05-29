// tests/test_vehicles.c
#include <CUnit/Basic.h>
#include "vehicles.h"
#include "app.h"

static void test_vehicles_list_does_not_crash_on_null_db(void) {
    AppContext ctx = {0};
    ctx.db = NULL;
    vehicles_list(&ctx);
    CU_PASS("vehicles_list executed (minimal smoke test)");
}

void add_vehicles_tests(CU_pSuite suite) {
    CU_add_test(suite, "vehicles_list minimal smoke test", test_vehicles_list_does_not_crash_on_null_db);
}