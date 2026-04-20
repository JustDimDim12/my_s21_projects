#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_init_decimal(result);
  int flag = 1;

  if (s21_get_scale(&value) >= 0 && s21_get_scale(&value) <= 29) {
    if (s21_get_scale(&value) == 0) {
      s21_copy_decimal(result, value);
      result->bits[3] = value.bits[3];
      s21_set_scale(result, 0);
    } else {
      s21_decimal just_number_one;
      s21_init_decimal(&just_number_one);
      just_number_one.bits[0] = 1;
      s21_truncate(value, result);
      if (s21_get_bit(&value, 127) != 0)
        s21_simple_sum(*result, just_number_one, result);
    }
    flag = 0;
  }

  return flag;
}
