#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../src/matrix.h"
#include "../src/basic_functions.h"

START_TEST(test_matrix_create) {
  Matrix* m;
  m = create_matrix(5, 10);
  ck_assert_int_eq(m->width, 10);
  ck_assert_int_eq(m->height, 5);
  free_matrix(m);
} END_TEST

START_TEST(test_matrix_insert) {
  Matrix* m;
  m = create_matrix(5, 5);
  set_value(m, 0, 0, 5);
  ck_assert_int_eq(get_value(m, 0, 0), 5);
  free_matrix(m);
} END_TEST

Suite *matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Matrix");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_matrix_create);
  tcase_add_test(tc_core, test_matrix_insert);
  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  s = matrix_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
