#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (!dst) {
    return CONVERT_ERROR;
  }

  int scale = s21_get_scale(&src);
  double num = 0;
  for (int i = 0; i < 96; i++) {
    if (s21_get_bit(&src, i)) {
      num += pow(2, i);
    }
  }

  num /= pow(10, scale);
  if (s21_get_sign(&src)) {
    num = -num;
  }

  int conversion_status = (num > INT_MAX || num < INT_MIN) ? CONVERSION_OVERFLOW
                                                           : CONVERSION_SUCCESS;
  *dst = (conversion_status == CONVERSION_SUCCESS) ? (int)num : 0;

  return conversion_status;
}
