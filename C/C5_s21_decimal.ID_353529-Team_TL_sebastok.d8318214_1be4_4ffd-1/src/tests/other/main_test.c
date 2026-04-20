#include <check.h>

Suite *test_truncate(void);  // название сьюта
Suite *test_floor(void);
Suite *test_negate(void);
Suite *test_round(void);

int main() {
  SRunner *sr = srunner_create(test_truncate());  // вызов сьюта внутри раннера
  srunner_add_suite(sr, test_floor());
  srunner_add_suite(sr, test_negate());
  srunner_add_suite(sr, test_round());

  srunner_run_all(sr, CK_VERBOSE);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return 0;
}