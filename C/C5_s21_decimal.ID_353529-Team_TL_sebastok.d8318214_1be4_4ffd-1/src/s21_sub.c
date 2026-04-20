#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) return 1;

  s21_init_decimal(result);

  int sign1 = s21_get_sign(&value_1);
  int sign2 = s21_get_sign(&value_2);

  // Если числа имеют разные знаки, вычитание превращается в сложение
  if (sign1 != sign2) {
    s21_set_sign(&value_2, sign1);  // меняем знак второго числа
    return s21_add(value_1, value_2, result);
  }

  // Приводим к общему масштабу
  s21_decimal_extended ext1 = s21_convert_to_extended(value_1);
  s21_decimal_extended ext2 = s21_convert_to_extended(value_2);
  s21_bring_to_a_common_denominator(&ext1, &ext2);

  s21_decimal_extended res_ext = {0};
  int borrow = 0;

  // Выполняем побитовое вычитание
  for (int i = 0; i < 224; i++) {
    int b1 = s21_get_bit_ext(&ext1, i);
    int b2 = s21_get_bit_ext(&ext2, i);
    int bit_res = b1 - b2 - borrow;
    if (bit_res < 0) {
      bit_res += 2;
      borrow = 1;
    } else {
      borrow = 0;
    }
    s21_set_bit_ext(&res_ext, i, bit_res);
  }

  res_ext.scale = ext1.scale;

  int code = s21_normalization(&res_ext);
  if (code == 1) code = 2;  // переполнение

  s21_convert_from_extended(res_ext, result);

  // Устанавливаем знак результата, если оба числа были отрицательные
  if (sign1 == 1 && sign2 == 1) {
    s21_set_sign(result, 1);
  }

  return code;
}
