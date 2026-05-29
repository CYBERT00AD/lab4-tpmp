// tests/test_drivers.c
#include <CUnit/Basic.h>
#include "drivers.h"
#include "app.h"


static void test_drivers_list_does_not_crash_on_null_db(void) {
    AppContext ctx = {0};
    ctx.db = NULL;
    drivers_list(&ctx);
    CU_PASS("drivers_list executed (minimal smoke test)");
}

void add_drivers_tests(CU_pSuite suite) {
    CU_add_test(suite, "drivers_list minimal smoke test", test_drivers_list_does_not_crash_on_null_db);
}