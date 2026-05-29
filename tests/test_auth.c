#include <string.h>
#include <CUnit/Basic.h>
#include "auth.h"
#include "utils.h"
#include "drivers.h"
#include "vehicles.h"
#include "app.h"

static void test_auth_logout_resets_context(void) {
    AppContext ctx;

    ctx.user_id = 10;
    ctx.driver_id = 20;
    strcpy(ctx.role, "admin");
    strcpy(ctx.login, "testuser");

    auth_logout(&ctx);

    CU_ASSERT_EQUAL(ctx.user_id, 0);
    CU_ASSERT_EQUAL(ctx.driver_id, 0);
    CU_ASSERT_STRING_EQUAL(ctx.role, "");
    CU_ASSERT_STRING_EQUAL(ctx.login, "");
}

static void test_auth_logout_on_empty_context(void) {
    AppContext ctx;
    memset(&ctx, 0, sizeof(ctx));

    auth_logout(&ctx);

    CU_ASSERT_EQUAL(ctx.user_id, 0);
    CU_ASSERT_EQUAL(ctx.driver_id, 0);
    CU_ASSERT_STRING_EQUAL(ctx.role, "");
    CU_ASSERT_STRING_EQUAL(ctx.login, "");
}

void add_drivers_tests(CU_pSuite suite);
void add_vehicles_tests(CU_pSuite suite);

int main(void) {
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    CU_pSuite auth_suite = CU_add_suite("Auth Suite", NULL, NULL);
    if (auth_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((CU_add_test(auth_suite, "auth_logout resets context", test_auth_logout_resets_context) == NULL) ||
        (CU_add_test(auth_suite, "auth_logout on empty context", test_auth_logout_on_empty_context) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_pSuite drivers_suite = CU_add_suite("Drivers Suite", NULL, NULL);
    if (drivers_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    add_drivers_tests(drivers_suite);

    CU_pSuite vehicles_suite = CU_add_suite("Vehicles Suite", NULL, NULL);
    if (vehicles_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    add_vehicles_tests(vehicles_suite);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}