#include "s21_decimal.h"

// индийский способо умножения
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code_error = 0;
  s21_init_decimal(result);
  int sign_of_res = s21_get_sign(&value_1) ^ s21_get_sign(&value_2);
  if (!result) {
    code_error = 1;
  } else if (s21_get_scale(&value_1) > 28 || s21_get_scale(&value_2) > 28) {
    code_error = 1;
  } else {
    s21_decimal_extended res = {0};
    s21_decimal_extended val1 = s21_convert_to_extended(value_1);
    s21_decimal_extended val2 = s21_convert_to_extended(value_2);
    if (s21_is_null(value_1) || s21_is_null(value_2)) {
      sign_of_res = 0;
    } else {
      res.bits[0] = val1.bits[0] * val2.bits[0];
      s21_get_overflow(&res);
      res.bits[1] += val1.bits[0] * val2.bits[1];
      s21_get_overflow(&res);
      res.bits[1] += val1.bits[1] * val2.bits[0];
      s21_get_overflow(&res);

      res.bits[2] += val1.bits[0] * val2.bits[2];
      s21_get_overflow(&res);
      res.bits[2] += val1.bits[1] * val2.bits[1];
      s21_get_overflow(&res);
      res.bits[2] += val1.bits[2] * val2.bits[0];
      s21_get_overflow(&res);

      res.bits[3] += val1.bits[1] * val2.bits[2];
      s21_get_overflow(&res);
      res.bits[3] += val1.bits[2] * val2.bits[1];
      s21_get_overflow(&res);
      res.bits[4] += val1.bits[2] * val2.bits[2];
      res.scale = val1.scale + val2.scale;
      code_error = s21_get_overflow(&res);
    }
    if (!code_error) code_error = s21_normalization(&res);
    if (code_error) {
      if (sign_of_res) code_error = 2;
    } else {
      s21_convert_from_extended(res, result);
      s21_set_sign(result, sign_of_res);
    }
  }
  return code_error;
}