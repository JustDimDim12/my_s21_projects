#include <check.h>

Suite *helpers_suite(void);

int main(void) {
  SRunner *sr = srunner_create(helpers_suite());  // вызов сьюта внутри раннера

  srunner_run_all(sr, CK_VERBOSE);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return 0;
}