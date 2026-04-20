#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int flag = 1;

  if (s21_get_scale(&value) >= 0 && s21_get_scale(&value) <= 29) {
    s21_decimal devider, tmp_result;
    s21_init_decimal(&devider);
    s21_init_decimal(&tmp_result);
    s21_init_decimal(result);

    s21_copy_decimal(result, value);
    devider.bits[0] = 10;

    for (int i = 0; i < s21_get_scale(&value); i++) {
      s21_simple_div(*result, devider, &tmp_result);
      s21_copy_decimal(result, tmp_result);
    }
    result->bits[3] = value.bits[3];
    s21_set_scale(result, 0);
    flag = 0;
  }
  return flag;
}
