#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../src/matrix.h"
#include "../src/basic_functions.h"
#include "../src/file_io.h"

START_TEST(test_get_dimensions) {
  FILE* file;
  int* dim;

  file = fopen("data/kernel.txt", "r+");
  dim = get_dimensions(file);
  ck_assert_int_eq(dim[0], 3);
  ck_assert_int_eq(dim[1], 4);
  fclose(file);
} END_TEST

Suite *io_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("IO");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_get_dimensions);
  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  s = io_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
