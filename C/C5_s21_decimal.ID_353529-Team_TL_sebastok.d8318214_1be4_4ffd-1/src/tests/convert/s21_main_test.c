#include <check.h>

Suite *from_int_suite(void);  // название сьюта
Suite *from_float_suite(void);
Suite *from_decimal_to_float_suite(void);
Suite *test_convert_decimal_to_int(void);

int main() {
  SRunner *sr = srunner_create(from_int_suite());  // вызов сьюта внутри раннера
  srunner_add_suite(sr, from_float_suite());
  srunner_add_suite(sr, from_decimal_to_float_suite());
  srunner_add_suite(sr, test_convert_decimal_to_int());

  srunner_run_all(sr, CK_VERBOSE);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return 0;
}