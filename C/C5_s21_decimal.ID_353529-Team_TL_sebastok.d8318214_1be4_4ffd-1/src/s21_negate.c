#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_init_decimal(result);
  s21_copy_decimal(result, value);
  unsigned int u = 1;

  result->bits[3] ^= u << 31;

  return s21_get_bit(&value, 127) == s21_get_bit(result, 127);
}
