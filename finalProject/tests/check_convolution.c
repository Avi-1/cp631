#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../src/matrix.h"
#include "../src/basic_functions.h"
#include "../src/convolution.h"

START_TEST(test_apply_convolution) {
  Matrix* kernel = create_matrix(2, 2);
  Matrix* image = create_matrix(2, 2);
  for(int i=0; i<2; i++)
    for(int j=0; j<2; j++){
      set_value(kernel, i, j, i+j);
      set_value(image, i, j, 2*i+j);
    }
  int output = apply_convolution(kernel, image, 0, 0);
  ck_assert_int_eq(output, 9);
  free_matrix(kernel);
  free_matrix(image);
} END_TEST

START_TEST(test_process_image) {
  Matrix* kernel = create_matrix(2, 2);
  Matrix* image = create_matrix(8, 8);
  for(int i=0; i<8; i++)
    for(int j=0; j<8; j++){
      if(i<2 && j<2) set_value(kernel, i, j, i+j);
      set_value(image, i, j, 2*i+j);
    }
  Matrix* output = process_image(kernel, image);
  ck_assert_int_eq(output->width, 7);
  ck_assert_int_eq(output->height, 7);
  ck_assert_int_eq(get_value(output, 0, 0), 9);
  ck_assert_int_eq(get_value(output, 3, 1), 37);
  ck_assert_int_eq(get_value(output, 6, 6), 81);
  ck_assert_int_eq(get_value(output, 2, 5), 45);
  free_matrix(kernel);
  free_matrix(image);
  free_matrix(output);
} END_TEST

Suite *io_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Convolution");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_apply_convolution);
  tcase_add_test(tc_core, test_process_image);
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
