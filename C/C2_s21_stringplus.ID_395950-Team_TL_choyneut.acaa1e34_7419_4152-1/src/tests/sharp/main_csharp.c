#include <check.h>
#include <stdlib.h>

#include "../../s21_string.h"

Suite *to_upper_suite(void);
Suite *to_lower_suite(void);
Suite *insert_suite(void);
Suite *trim_suite(void);

int main() {
  SRunner *sr = srunner_create(to_upper_suite());
  srunner_add_suite(sr, to_lower_suite());
  srunner_add_suite(sr, insert_suite());
  srunner_add_suite(sr, trim_suite());

  srunner_run_all(sr, CK_VERBOSE);

  srunner_ntests_failed(sr);
  srunner_free(sr);

  return 0;
}
