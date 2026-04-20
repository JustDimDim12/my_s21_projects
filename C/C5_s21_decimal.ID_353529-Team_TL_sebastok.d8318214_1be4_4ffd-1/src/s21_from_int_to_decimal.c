#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int conversion_status = 0;
  if (!dst) {
    return 1;
  }
  for (int i = 0; i < S21_NUM_WORDS; i++) {
    dst->bits[i] = 0;
  }
  if (src < 0) {
    unsigned int signBit = 0x80000000;
    dst->bits[S21_NUM_WORDS - 1] = signBit;
    dst->bits[0] = (unsigned int)(-src);
  } else {
    dst->bits[0] = (unsigned int)src;
  }
  return conversion_status;
}
