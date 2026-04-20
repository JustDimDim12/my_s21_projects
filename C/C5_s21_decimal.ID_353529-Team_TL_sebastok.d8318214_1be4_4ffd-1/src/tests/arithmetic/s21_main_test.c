#include <check.h>

Suite *sub_suite(void);
Suite *add_suite(void);
Suite *suite_s21_div(void);
Suite *suite_s21_mul(void);

int main() {
  SRunner *sr = srunner_create(sub_suite());  // вызов сьюта внутри раннера
  srunner_add_suite(sr, add_suite());
  srunner_add_suite(sr, suite_s21_div());
  srunner_add_suite(sr, suite_s21_mul());

  srunner_run_all(sr, CK_VERBOSE);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return 0;
}