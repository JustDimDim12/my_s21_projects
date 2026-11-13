#include "s21_decimal.h"

int s21_is_equal(s21_decimal value1, s21_decimal value2) {
  int sign1 = s21_get_sign(&value1), sign2 = s21_get_sign(&value2);  // +
  int flag = 1;
  if (s21_is_zero(value1) && s21_is_zero(value2))  // +
    ;
  else if (sign1 != sign2)
    flag = 0;
  else {
    s21_decimal_extended ext1 = s21_convert_to_extended(value1);  // +
    s21_decimal_extended ext2 = s21_convert_to_extended(value2);  // +
    s21_bring_to_a_common_denominator(&ext1, &ext2);              // +
    for (int i = 6; i >= 0; i--)
      if (ext1.bits[i] != ext2.bits[i]) {
        flag = 0;
        break;
      }
  }
  return flag;
}
