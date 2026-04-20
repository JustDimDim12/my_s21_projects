#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_decimal truncated_value, abs_value, one;
  int fnac = s21_getFirstNumAfterComma(value);
  int sign = s21_get_sign(&value);

  s21_init_decimal(result);
  s21_init_decimal(&truncated_value);
  s21_init_decimal(&abs_value);
  s21_init_decimal(&one);

  one.bits[0] = 1;

  s21_copy_decimal(&abs_value, value);
  s21_set_sign(&abs_value, 0);

  s21_truncate(abs_value, &truncated_value);

  if (fnac >= 5) {
    s21_simple_sum(truncated_value, one, result);
  } else {
    s21_copy_decimal(result, truncated_value);
  }

  s21_set_sign(result, sign);

  return 0;
}
