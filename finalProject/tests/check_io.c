#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../src/matrix.h"
#include "../src/basic_functions.h"
#include "../src/file_io.h"

START_TEST(test_get_dimensions) {
  char* file = "data/kernel.txt";
  int* dim;

  dim = get_dimensions(file);
  ck_assert_int_eq(dim[0], 3);
  ck_assert_int_eq(dim[1], 4);
} END_TEST

START_TEST(test_get_matrix){
  char* file_name = "data/kernel.txt";
  Matrix* kernel;

  kernel = get_matrix_from_file(file_name);
  ck_assert_int_eq(get_value(kernel, 0, 3), 6);
  ck_assert_int_eq(get_value(kernel, 1, 1), 1);
  ck_assert_int_eq(get_value(kernel, 2, 2), 3);
  ck_assert_int_eq(get_value(kernel, 0, 0), 0);
  free_matrix(kernel);
}END_TEST

START_TEST(test_file_writer){
  char* file_name = "data/test.txt";
  Matrix* m_test = create_matrix(2, 2);
  for(int i=0; i<2; i++)
    for(int j=0; j<2; j++)
      set_value(m_test, i, j, 2*i+j);

  write_matrix_to_file(file_name, m_test);
  free_matrix(m_test);
  Matrix* m_in = get_matrix_from_file(file_name);
  ck_assert_int_eq(get_value(m_in, 0, 0), 0);
  ck_assert_int_eq(get_value(m_in, 0, 1), 1);
  ck_assert_int_eq(get_value(m_in, 1, 0), 2);
  ck_assert_int_eq(get_value(m_in, 1, 1), 3);
  free_matrix(m_in);
}

Suite *io_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("IO");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_get_dimensions);
  tcase_add_test(tc_core, test_get_matrix);
  tcase_add_test(tc_core, test_file_writer);
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
