#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) return 1;  // null pointer
  s21_init_decimal(result);

  int sign1 = s21_get_sign(&value_1);
  int sign2 = s21_get_sign(&value_2);

  // Сбрасываем знаки для работы с модулем
  s21_set_sign(&value_1, 0);
  s21_set_sign(&value_2, 0);

  // Приводим к общему масштабу
  s21_decimal_extended ext1 = s21_convert_to_extended(value_1);
  s21_decimal_extended ext2 = s21_convert_to_extended(value_2);
  s21_bring_to_a_common_denominator(&ext1, &ext2);

  s21_decimal_extended res_ext;
  s21_init_decimal_extended(&res_ext);

  int code_error = 0;

  if (sign1 == sign2) {
    // одинаковые знаки → простое сложение
    int carry = 0;
    for (int i = 0; i < 224; i++) {
      int bit1 = s21_get_bit_ext(&ext1, i);
      int bit2 = s21_get_bit_ext(&ext2, i);
      int sum = bit1 + bit2 + carry;
      s21_set_bit_ext(&res_ext, i, sum % 2);
      carry = sum / 2;
    }
    res_ext.scale = ext1.scale;
    code_error = s21_normalization(&res_ext);

    if (sign1) s21_set_sign(result, 1);  // сохраняем знак
    s21_convert_from_extended(res_ext, result);

  } else {
    // разные знаки → фактически вычитание
    // определяем, какое число больше по модулю
    int cmp = s21_simple_less_or_equal(value_1, value_2);
    if (cmp) {
      // |value_1| <= |value_2| → value_2 - value_1
      code_error = s21_sub(value_2, value_1, result);
      if (sign2) s21_set_sign(result, 1);
    } else {
      // |value_1| > |value_2| → value_1 - value_2
      code_error = s21_sub(value_1, value_2, result);
      if (sign1) s21_set_sign(result, 1);
    }
  }

  return code_error;
}
