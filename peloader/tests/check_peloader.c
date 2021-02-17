#include <check.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "../winnt_types.h"
#include "../pe_linker.h"

Suite *s;
TCase *tc;
SRunner *runner;

START_TEST(test_check_nt_hdr) {
        unsigned char nt_hdr[252] = {
                0x50, 0x45, 0x00, 0x00, 0x64, 0x86, 0x06, 0x00, 0x33, 0xCB, 0x08, 0x60, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x22, 0x20, 0x0B, 0x02, 0x0E, 0x1C, 0x00, 0xC0, 0xA4, 0x00,
                0x00, 0xD0, 0x4D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x9C, 0x40, 0x00, 0x00, 0x10, 0x00, 0x00,
                0x00, 0x00, 0x10, 0x5A, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
                0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0xA0, 0xF2, 0x00, 0x00, 0x10, 0x00, 0x00, 0xD3, 0x0F, 0xF4, 0x00, 0x03, 0x00, 0x60, 0x41,
                0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xB0, 0xA7, 0xDE, 0x00, 0xFC, 0x01, 0x00, 0x00,
                0xAC, 0xA9, 0xDE, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0xB0, 0xEA, 0x00, 0xE0, 0x59, 0x06, 0x00,
                0x00, 0x40, 0xE4, 0x00, 0xA4, 0x6A, 0x06, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0x90, 0x3F, 0x02, 0x00,
                0x00, 0x10, 0xF1, 0x00, 0xF8, 0x81, 0x01, 0x00, 0xFC, 0x3A, 0xCF, 0x00, 0x54, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0xE8, 0x75, 0xAC, 0x00, 0x28, 0x00, 0x00, 0x00, 0xB0, 0x74, 0xAC, 0x00, 0x38, 0x01, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x76, 0xAC, 0x00, 0xC0, 0x0C, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };
        int result = check_nt_hdr((IMAGE_NT_HEADERS *)nt_hdr);
        ck_assert_int_eq(result, IMAGE_FILE_EXECUTABLE_IMAGE);
} END_TEST

Suite *peloader_suite(void) {
    TCase *tc_core;

    s = suite_create("peloader");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_check_nt_hdr);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int no_failed = 0;

    s = peloader_suite();
    runner = srunner_create(s);

    //srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}