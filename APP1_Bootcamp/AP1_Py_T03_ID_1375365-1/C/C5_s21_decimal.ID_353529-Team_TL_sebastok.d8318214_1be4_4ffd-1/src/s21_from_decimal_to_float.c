#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result = OK;
  if (dst && s21_get_scale(&src) < 29) {
    double temp = 0.0;
    for (int i = 0; i < 96; ++i) {
      if (s21_get_bit(&src, i)) temp += pow(2.0, i);
    }
    int scale = s21_get_scale(&src);
    temp *= pow(10.0, -scale);
    if (s21_get_sign(&src)) temp *= -1.0;
    *dst = (float)temp;
  } else
    result = ERROR;
  return result;
}
