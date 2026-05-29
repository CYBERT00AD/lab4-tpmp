#include <string.h>
#include <CUnit/Basic.h>
#include "auth.h"
#include "utils.h"

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

int main(void) {
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    CU_pSuite suite = CU_add_suite("Auth Suite", NULL, NULL);
    if (suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (CU_add_test(suite, "auth_logout resets context", test_auth_logout_resets_context) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
