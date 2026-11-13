#include <check.h>

Suite *create_suite(void);
Suite *remove_suite(void);

int main() {
  SRunner *sr = srunner_create(create_suite());
  srunner_add_suite(sr, remove_suite());

  srunner_run_all(sr, CK_VERBOSE);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return 0;
}