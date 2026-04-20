#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) return 1;

  s21_init_decimal(result);

  if (s21_is_zero(value_2)) return S21_NAN;
  if (s21_is_zero(value_1)) return 0;

  int sign1 = s21_get_sign(&value_1);
  int sign2 = s21_get_sign(&value_2);

  s21_set_sign(&value_1, 0);
  s21_set_sign(&value_2, 0);

  int scale1 = s21_get_scale(&value_1);
  int scale2 = s21_get_scale(&value_2);

  while (s21_first_unzero_bit(value_1) < 92 && scale1 < 28) {
    s21_mul_10(&value_1);
    scale1++;
  }

  s21_set_scale(&value_1, 0);
  s21_set_scale(&value_2, 0);

  s21_simple_div(value_1, value_2, result);

  s21_decimal_extended ext_res = s21_convert_to_extended(*result);
  if (s21_get_overflow(&ext_res)) {
    return (sign1 == sign2) ? S21_INF : S21_NEG_INF;
  }

  int final_scale = scale1 - scale2;
  if (final_scale < 0) final_scale = 0;
  s21_set_scale(result, final_scale);

  if (sign1 != sign2) s21_set_sign(result, 1);

  return 0;
}
