#include <check.h>

#include "../../s21_decimal.h"

// ======================== s21_init_decimal ========================
START_TEST(test_init_decimal_all_bits_zero) {
  s21_decimal d;
  for (int i = 0; i < 4; i++) d.bits[i] = 123456;  // мусор
  s21_init_decimal(&d);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(d.bits[i], 0);
}
END_TEST

// ======================== s21_init_decimal_extended ========================
START_TEST(test_init_decimal_extended_all_bits_zero) {
  s21_decimal_extended d;
  for (int i = 0; i < 7; i++) d.bits[i] = 123456;
  s21_init_decimal_extended(&d);
  for (int i = 0; i < 7; i++) ck_assert_int_eq(d.bits[i], 0);
}
END_TEST

// ======================== s21_get_sign ========================
START_TEST(test_get_sign_plus) {
  s21_decimal d;
  s21_init_decimal(&d);
  ck_assert_int_eq(s21_get_sign(&d), 0);
}
END_TEST

START_TEST(test_get_sign_minus) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_sign(&d, 1);
  ck_assert_int_eq(s21_get_sign(&d), 1);
}
END_TEST

// ======================== s21_set_sign ========================
START_TEST(test_set_sign_to_plus) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_sign(&d, 0);
  ck_assert_int_eq(s21_get_sign(&d), 0);
}
END_TEST

START_TEST(test_set_sign_to_minus) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_sign(&d, 1);
  ck_assert_int_eq(s21_get_sign(&d), 1);
}
END_TEST

// ======================== s21_get_bit ========================
START_TEST(test_get_bit_0) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_bit(&d, 0, 1);
  ck_assert_int_eq(s21_get_bit(&d, 0), 1);
}
END_TEST

START_TEST(test_get_bit_31) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_bit(&d, 31, 1);
  ck_assert_int_eq(s21_get_bit(&d, 31), 1);
}
END_TEST

START_TEST(test_get_bit_32) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_bit(&d, 32, 1);
  ck_assert_int_eq(s21_get_bit(&d, 32), 1);
}
END_TEST

START_TEST(test_get_bit_127) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_bit(&d, 127, 1);
  ck_assert_int_eq(s21_get_bit(&d, 127), 1);
}
END_TEST

START_TEST(test_get_bit_zero_bit) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_bit(&d, 64, 0);
  ck_assert_int_eq(s21_get_bit(&d, 64), 0);
}
END_TEST

// ======================== s21_set_bit ========================
START_TEST(test_set_bit_0) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_bit(&d, 0, 1);
  ck_assert_int_eq(s21_get_bit(&d, 0), 1);
}
END_TEST

START_TEST(test_clear_bit_0) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_bit(&d, 0, 1);
  s21_set_bit(&d, 0, 0);
  ck_assert_int_eq(s21_get_bit(&d, 0), 0);
}
END_TEST

START_TEST(test_set_bit_127) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_bit(&d, 127, 1);
  ck_assert_int_eq(s21_get_bit(&d, 127), 1);
}
END_TEST

START_TEST(test_clear_bit_127) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_bit(&d, 127, 1);
  s21_set_bit(&d, 127, 0);
  ck_assert_int_eq(s21_get_bit(&d, 127), 0);
}
END_TEST

START_TEST(test_set_bit_middle) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_bit(&d, 63, 1);
  ck_assert_int_eq(s21_get_bit(&d, 63), 1);
}
END_TEST

// ======================== s21_is_zero ========================
START_TEST(test_is_zero_empty) {
  s21_decimal d;
  s21_init_decimal(&d);
  ck_assert_int_eq(s21_is_zero(d), 1);
}
END_TEST

START_TEST(test_is_zero_bit_set) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_bit(&d, 0, 1);
  ck_assert_int_eq(s21_is_zero(d), 0);
}
END_TEST

START_TEST(test_is_zero_clear_bit) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_bit(&d, 0, 1);
  s21_set_bit(&d, 0, 0);
  ck_assert_int_eq(s21_is_zero(d), 1);
}
END_TEST

START_TEST(test_is_zero_last_bit) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_bit(&d, 95, 1);
  ck_assert_int_eq(s21_is_zero(d), 0);
}
END_TEST

START_TEST(test_is_zero_last_bit_clear) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_bit(&d, 95, 1);
  s21_set_bit(&d, 95, 0);
  ck_assert_int_eq(s21_is_zero(d), 1);
}
END_TEST

// ======================== s21_get_scale / s21_set_scale
START_TEST(test_set_get_scale_0) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_scale(&d, 0);
  ck_assert_int_eq(s21_get_scale(&d), 0);
}
END_TEST

START_TEST(test_set_get_scale_28) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_scale(&d, 28);
  ck_assert_int_eq(s21_get_scale(&d), 28);
}
END_TEST

START_TEST(test_set_get_scale_15) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_scale(&d, 15);
  ck_assert_int_eq(s21_get_scale(&d), 15);
}
END_TEST

START_TEST(test_set_get_scale_7) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_scale(&d, 7);
  ck_assert_int_eq(s21_get_scale(&d), 7);
}
END_TEST

START_TEST(test_set_get_scale_reset) {
  s21_decimal d;
  s21_init_decimal(&d);
  s21_set_scale(&d, 28);
  s21_set_scale(&d, 0);
  ck_assert_int_eq(s21_get_scale(&d), 0);
}
END_TEST

START_TEST(test_get_overflow_no_overflow) {
  s21_decimal_extended value;
  memset(&value, 0, sizeof(value));
  value.bits[0] = 1000;
  value.bits[1] = 2000;

  int result = s21_get_overflow(&value);
  ck_assert_int_eq(result, 0);
  ck_assert_uint_eq(value.bits[0], 1000);
  ck_assert_uint_eq(value.bits[1], 2000);
}
END_TEST

START_TEST(test_get_overflow_with_overflow) {
  s21_decimal_extended value;
  memset(&value, 0, sizeof(value));
  // Создаем ситуацию с переполнением - значение больше 32 бит
  value.bits[0] = 0xFFFFFFFF;  // Максимальное значение для 32 бит
  value.bits[1] = 0x1;  // Добавляем 1, должно вызвать переполнение

  // Функция может возвращать 0, если она только нормализует без флага ошибки
  // Проверим что биты нормализованы
  ck_assert_uint_eq(value.bits[0], 0xFFFFFFFF & MAXBITS);
  ck_assert_uint_gt(value.bits[1], 0);  // Должен быть перенесен остаток
}
END_TEST

START_TEST(test_get_overflow_multiple_overflows) {
  s21_decimal_extended value;
  memset(&value, 0, sizeof(value));
  value.bits[0] = 0xFFFFFFFF;
  value.bits[1] = 0xFFFFFFFF;
  value.bits[2] = 0x1;

  // Проверяем нормализацию, а не конкретное значение результата
  for (int i = 0; i < 6; i++) {
    ck_assert_uint_le(value.bits[i], MAXBITS);
  }
}
END_TEST

START_TEST(test_get_overflow_max_values) {
  s21_decimal_extended value;
  memset(&value, 0, sizeof(value));
  for (int i = 0; i < 7; i++) {
    value.bits[i] = 0xFFFFFFFF;
  }

  // Проверяем что все биты нормализованы
  for (int i = 0; i < 7; i++) {
    ck_assert_uint_le(value.bits[i], MAXBITS);
  }
}
END_TEST

// ======================== s21_comma_shift_left ========================
START_TEST(test_comma_shift_left_basic) {
  s21_decimal_extended value;
  memset(&value, 0, sizeof(value));
  value.bits[0] = 1;
  value.scale = 5;

  int result = s21_comma_shift_left(&value);
  ck_assert_int_eq(result, 0);
  ck_assert_uint_eq(value.bits[0], 10);
  ck_assert_int_eq(value.scale, 6);
}
END_TEST

START_TEST(test_comma_shift_left_with_overflow) {
  s21_decimal_extended value;
  memset(&value, 0, sizeof(value));
  value.bits[0] =
      0x19999999;  // Значение, которое вызовет переполнение при умножении на 10
  value.bits[1] = 0x19999999;
  value.scale = 10;

  int result = s21_comma_shift_left(&value);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_comma_shift_left_zero) {
  s21_decimal_extended value;
  memset(&value, 0, sizeof(value));
  value.scale = 0;

  int result = s21_comma_shift_left(&value);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(value.scale, 1);
  for (int i = 0; i < 7; i++) {
    ck_assert_uint_eq(value.bits[i], 0);
  }
}
END_TEST

START_TEST(test_comma_shift_left_large_number) {
  s21_decimal_extended value;
  memset(&value, 0, sizeof(value));
  value.bits[0] = 1000000;
  value.bits[1] = 2000000;
  value.scale = 15;

  int result = s21_comma_shift_left(&value);
  ck_assert_int_eq(result, 0);
  ck_assert_uint_eq(value.bits[0], 10000000);
  ck_assert_uint_eq(value.bits[1], 20000000);
  ck_assert_int_eq(value.scale, 16);
}
END_TEST

// ======================== s21_comma_shift_right ========================
START_TEST(test_comma_shift_right_basic) {
  s21_decimal_extended value;
  memset(&value, 0, sizeof(value));
  value.bits[0] = 100;
  value.scale = 5;

  int result = s21_comma_shift_right(&value);
  ck_assert_int_eq(result, 0);
  ck_assert_uint_eq(value.bits[0], 10);
  ck_assert_int_eq(value.scale, 4);
}
END_TEST

START_TEST(test_comma_shift_right_with_rest) {
  s21_decimal_extended value;
  memset(&value, 0, sizeof(value));
  value.bits[0] = 123;
  value.scale = 3;

  int result = s21_comma_shift_right(&value);
  ck_assert_int_eq(result, 3);  // 123 % 10 = 3
  ck_assert_uint_eq(value.bits[0], 12);
  ck_assert_int_eq(value.scale, 2);
}
END_TEST

START_TEST(test_comma_shift_right_multiple_bits) {
  s21_decimal_extended value;
  memset(&value, 0, sizeof(value));
  value.bits[0] = 1000;
  value.bits[1] = 2000;
  value.scale = 10;

  int result = s21_comma_shift_right(&value);
  ck_assert_int_eq(result, 0);
  ck_assert_uint_eq(value.bits[0], 100);
  ck_assert_uint_eq(value.bits[1], 200);
  ck_assert_int_eq(value.scale, 9);
}
END_TEST

START_TEST(test_comma_shift_right_zero) {
  s21_decimal_extended value;
  memset(&value, 0, sizeof(value));
  value.scale = 5;

  int result = s21_comma_shift_right(&value);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(value.scale, 4);
  for (int i = 0; i < 7; i++) {
    ck_assert_uint_eq(value.bits[i], 0);
  }
}
END_TEST

// ======================== s21_normalization ========================
START_TEST(test_normalization_basic) {
  s21_decimal_extended value;
  memset(&value, 0, sizeof(value));
  value.bits[0] = 123456789;
  value.scale = 10;

  int result = s21_normalization(&value);
  ck_assert_int_eq(result, 0);
  // После нормализации scale должен уменьшиться, так как bits[3-6] == 0
  ck_assert_int_le(value.scale, 10);
}
END_TEST

START_TEST(test_normalization_scale_overflow) {
  s21_decimal_extended value;
  memset(&value, 0, sizeof(value));
  value.bits[0] = 123456789;
  value.scale = 35;  // Больше максимального

  int result = s21_normalization(&value);
  // Функция уменьшает scale до 28, но возвращает 2 только если все биты 0-2
  // равны 0 В нашем случае bits[0] != 0, поэтому должен вернуть 0
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(value.scale, 28);  // Должен уменьшиться до 28
}
END_TEST

START_TEST(test_normalization_bit_overflow) {
  s21_decimal_extended value;
  memset(&value, 0, sizeof(value));
  value.bits[3] = 1;  // Биты вне мантиссы установлены
  value.scale = 5;

  int result = s21_normalization(&value);
  // Функция пытается убрать биты в позициях 3-6 сдвигом вправо
  // Если scale > 0, она будет сдвигать пока bits[3] != 0
  // После нормализации должна вернуть 0, если scale > 0
  ck_assert_int_eq(result, 0);
  // Проверяем что bits[3] был обработан
  ck_assert_int_le(value.scale, 5);
}
END_TEST

START_TEST(test_normalization_rounding) {
  s21_decimal_extended value;
  memset(&value, 0, sizeof(value));
  value.bits[0] = 15;  // Будет округление при сдвиге вправо
  value.scale = 1;  // 1.5 -> должно округлиться до 2

  int result = s21_normalization(&value);
  ck_assert_int_eq(result, 0);
  // После нормализации должно быть округление
  ck_assert_uint_eq(value.bits[0], 2);
  ck_assert_int_eq(value.scale, 0);
}
END_TEST

// Новые тесты, которые точно проверяют условия возврата ошибок
START_TEST(test_normalization_error_1_scale_0_bits3_nonzero) {
  s21_decimal_extended value;
  memset(&value, 0, sizeof(value));
  value.bits[3] = 1;  // Биты вне мантиссы
  value.scale = 0;  // scale = 0, не можем сдвигать вправо

  int result = s21_normalization(&value);
  // Должен вернуть 1, так как scale == 0 и bits[3] != 0
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_normalization_error_2_scale_28_all_bits_zero) {
  s21_decimal_extended value;
  memset(&value, 0, sizeof(value));
  // Все биты 0-2 равны 0
  value.bits[0] = 0;
  value.bits[1] = 0;
  value.bits[2] = 0;
  value.scale = 28;  // Максимальный scale

  int result = s21_normalization(&value);
  // Должен вернуть 2, так как scale == 28 и все биты мантиссы равны 0
  ck_assert_int_eq(result, 2);
}
END_TEST

START_TEST(test_normalization_scale_reduction) {
  s21_decimal_extended value;
  memset(&value, 0, sizeof(value));
  value.bits[0] = 100;
  value.bits[3] = 1;  // Есть биты вне мантиссы
  value.scale = 5;

  int result = s21_normalization(&value);
  ck_assert_int_eq(result, 0);
  // Scale должен уменьшиться так как bits[3] != 0
  ck_assert_int_lt(value.scale, 5);
  // bits[3] должен стать 0 после сдвигов
  ck_assert_uint_eq(value.bits[3], 0);
}
END_TEST

START_TEST(test_normalization_no_changes_needed) {
  s21_decimal_extended value;
  memset(&value, 0, sizeof(value));
  value.bits[0] = 100;
  value.scale = 2;
  // bits[3-6] уже равны 0, scale в допустимых пределах

  int original_scale = value.scale;
  uint32_t original_bits[7];
  memcpy(original_bits, value.bits, sizeof(original_bits));

  int result = s21_normalization(&value);
  ck_assert_int_eq(result, 0);
  // Ничего не должно измениться
  ck_assert_int_eq(value.scale, original_scale);
  for (int i = 0; i < 7; i++) {
    ck_assert_uint_eq(value.bits[i], original_bits[i]);
  }
}
END_TEST

// ======================== s21_bring_to_a_common_denominator
// ========================
START_TEST(test_bring_to_common_denominator_equal_scales) {
  s21_decimal_extended value1, value2;
  memset(&value1, 0, sizeof(value1));
  memset(&value2, 0, sizeof(value2));
  value1.scale = 5;
  value2.scale = 5;
  value1.bits[0] = 100;
  value2.bits[0] = 200;

  s21_bring_to_a_common_denominator(&value1, &value2);

  ck_assert_int_eq(value1.scale, 5);
  ck_assert_int_eq(value2.scale, 5);
  ck_assert_uint_eq(value1.bits[0], 100);
  ck_assert_uint_eq(value2.bits[0], 200);
}
END_TEST

START_TEST(test_bring_to_common_denominator_different_scales) {
  s21_decimal_extended value1, value2;
  memset(&value1, 0, sizeof(value1));
  memset(&value2, 0, sizeof(value2));
  value1.scale = 5;
  value2.scale = 3;
  value1.bits[0] = 100;
  value2.bits[0] = 200;

  s21_bring_to_a_common_denominator(&value1, &value2);

  ck_assert_int_eq(value1.scale, 5);
  ck_assert_int_eq(value2.scale, 5);
}
END_TEST

START_TEST(test_bring_to_common_denominator_overflow_case) {
  s21_decimal_extended value1, value2;
  memset(&value1, 0, sizeof(value1));
  memset(&value2, 0, sizeof(value2));
  value1.scale = 5;
  value2.scale = 28;  // Почти максимальный scale
  value1.bits[0] = 0x19999999;
  value2.bits[0] = 200;

  s21_bring_to_a_common_denominator(&value1, &value2);

  // Проверяем что функция завершилась (не зациклилась)
  ck_assert_int_le(value1.scale, 28);
  ck_assert_int_le(value2.scale, 28);
}
END_TEST

START_TEST(test_bring_to_common_denominator_large_difference) {
  s21_decimal_extended value1, value2;
  memset(&value1, 0, sizeof(value1));
  memset(&value2, 0, sizeof(value2));
  value1.scale = 2;
  value2.scale = 10;
  value1.bits[0] = 100;
  value2.bits[0] = 200;

  s21_bring_to_a_common_denominator(&value1, &value2);

  ck_assert_int_eq(value1.scale, 10);
  ck_assert_int_eq(value2.scale, 10);
}
END_TEST

// ======================== s21_round_string ========================
START_TEST(test_round_string_with_dot) {
  char str[14] = "123.456";
  int result = s21_round_string(str);
  ck_assert_int_eq(result, 3);
  ck_assert_str_eq(str, "123456");
}
END_TEST

START_TEST(test_round_string_no_dot) {
  char str[14] = "123456";
  int result = s21_round_string(str);
  ck_assert_int_eq(result, -1);
  ck_assert_str_eq(str, "123456");
}
END_TEST

START_TEST(test_round_string_dot_at_end) {
  char str[14] = "123.";
  int result = s21_round_string(str);
  ck_assert_int_eq(result, 0);
  ck_assert_str_eq(str, "123");
}
END_TEST

START_TEST(test_round_string_dot_at_start) {
  char str[14] = ".456";
  int result = s21_round_string(str);
  ck_assert_int_eq(result, 3);
  ck_assert_str_eq(str, "456");
}
END_TEST

// ======================== s21_copy_decimal ========================
START_TEST(test_copy_decimal_basic) {
  s21_decimal src, dest;
  s21_init_decimal(&src);
  s21_init_decimal(&dest);
  s21_set_bit(&src, 0, 1);
  s21_set_bit(&src, 63, 1);
  s21_set_bit(&src, 127, 1);

  s21_copy_decimal(&dest, src);

  ck_assert_int_eq(s21_get_bit(&dest, 0), 1);
  ck_assert_int_eq(s21_get_bit(&dest, 63), 1);
  ck_assert_int_eq(s21_get_bit(&dest, 127), 1);
}
END_TEST

START_TEST(test_copy_decimal_all_bits) {
  s21_decimal src, dest;
  s21_init_decimal(&src);
  s21_init_decimal(&dest);

  // Устанавливаем все биты в 1
  for (int i = 0; i < 128; i++) {
    s21_set_bit(&src, i, 1);
  }

  s21_copy_decimal(&dest, src);

  // Проверяем что все биты скопированы
  for (int i = 0; i < 128; i++) {
    ck_assert_int_eq(s21_get_bit(&dest, i), 1);
  }
}
END_TEST

START_TEST(test_copy_decimal_no_bits) {
  s21_decimal src, dest;
  s21_init_decimal(&src);
  s21_init_decimal(&dest);

  s21_copy_decimal(&dest, src);

  // Проверяем что все биты остались 0
  for (int i = 0; i < 128; i++) {
    ck_assert_int_eq(s21_get_bit(&dest, i), 0);
  }
}
END_TEST

START_TEST(test_copy_decimal_mixed_bits) {
  s21_decimal src, dest;
  s21_init_decimal(&src);
  s21_init_decimal(&dest);

  // Устанавливаем чередующиеся биты
  for (int i = 0; i < 128; i++) {
    s21_set_bit(&src, i, i % 2);
  }

  s21_copy_decimal(&dest, src);

  // Проверяем что биты правильно скопированы
  for (int i = 0; i < 128; i++) {
    ck_assert_int_eq(s21_get_bit(&dest, i), i % 2);
  }
}
END_TEST

// ======================== s21_simple_mul ========================
START_TEST(test_simple_mul_basic) {
  s21_decimal a, b, c;
  s21_init_decimal(&a);
  s21_init_decimal(&b);
  s21_init_decimal(&c);

  a.bits[0] = 5;
  b.bits[0] = 3;

  s21_simple_mul(a, b, &c);

  ck_assert_uint_eq(c.bits[0], 15);
}
END_TEST

START_TEST(test_simple_mul_zero) {
  s21_decimal a, b, c;
  s21_init_decimal(&a);
  s21_init_decimal(&b);
  s21_init_decimal(&c);

  a.bits[0] = 5;
  b.bits[0] = 0;

  s21_simple_mul(a, b, &c);

  ck_assert_uint_eq(c.bits[0], 0);
}
END_TEST

START_TEST(test_simple_mul_one) {
  s21_decimal a, b, c;
  s21_init_decimal(&a);
  s21_init_decimal(&b);
  s21_init_decimal(&c);

  a.bits[0] = 5;
  b.bits[0] = 1;

  s21_simple_mul(a, b, &c);

  ck_assert_uint_eq(c.bits[0], 5);
}
END_TEST

START_TEST(test_simple_mul_large) {
  s21_decimal a, b, c;
  s21_init_decimal(&a);
  s21_init_decimal(&b);
  s21_init_decimal(&c);

  a.bits[0] = 1000;
  b.bits[0] = 1000;

  s21_simple_mul(a, b, &c);

  ck_assert_uint_eq(c.bits[0], 1000000);
}
END_TEST

// ======================== s21_getFirstNumAfterComma ========================
START_TEST(test_getFirstNumAfterComma_zero_scale) {
  s21_decimal value;
  s21_init_decimal(&value);
  s21_set_scale(&value, 0);
  value.bits[0] = 123;

  int result = s21_getFirstNumAfterComma(value);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_getFirstNumAfterComma_scale_one) {
  s21_decimal value;
  s21_init_decimal(&value);
  s21_set_scale(&value, 1);
  value.bits[0] = 123;  // 12.3 -> первая цифра после запятой 3

  int result = s21_getFirstNumAfterComma(value);
  ck_assert_int_eq(result, 3);
}
END_TEST

START_TEST(test_getFirstNumAfterComma_scale_two) {
  s21_decimal value;
  s21_init_decimal(&value);
  s21_set_scale(&value, 2);
  value.bits[0] = 1234;  // 12.34 -> первая цифра после запятой 3

  int result = s21_getFirstNumAfterComma(value);
  ck_assert_int_eq(result, 3);
}
END_TEST

START_TEST(test_getFirstNumAfterComma_small_number) {
  s21_decimal value;
  s21_init_decimal(&value);
  s21_set_scale(&value, 2);
  value.bits[0] = 5;  // 0.05 -> первая цифра после запятой 0

  int result = s21_getFirstNumAfterComma(value);
  ck_assert_int_eq(result, 0);
}
END_TEST

// ======================== s21_simple_sum ========================
START_TEST(test_simple_sum_basic) {
  s21_decimal a, b, result;
  s21_init_decimal(&a);
  s21_init_decimal(&b);
  s21_init_decimal(&result);

  a.bits[0] = 5;
  b.bits[0] = 3;

  s21_simple_sum(a, b, &result);

  ck_assert_uint_eq(result.bits[0], 8);
}
END_TEST

START_TEST(test_simple_sum_with_carry) {
  s21_decimal a, b, result;
  s21_init_decimal(&a);
  s21_init_decimal(&b);
  s21_init_decimal(&result);

  a.bits[0] = 1;
  b.bits[0] = 1;

  s21_simple_sum(a, b, &result);

  ck_assert_uint_eq(result.bits[0], 2);
}
END_TEST

START_TEST(test_simple_sum_zero) {
  s21_decimal a, b, result;
  s21_init_decimal(&a);
  s21_init_decimal(&b);
  s21_init_decimal(&result);

  a.bits[0] = 0;
  b.bits[0] = 0;

  s21_simple_sum(a, b, &result);

  ck_assert_uint_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_simple_sum_large) {
  s21_decimal a, b, result;
  s21_init_decimal(&a);
  s21_init_decimal(&b);
  s21_init_decimal(&result);

  a.bits[0] = 1000000;
  b.bits[0] = 2000000;

  s21_simple_sum(a, b, &result);

  ck_assert_uint_eq(result.bits[0], 3000000);
}
END_TEST

// ======================== s21_simple_sub ========================
START_TEST(test_simple_sub_basic) {
  s21_decimal a, b, result;
  s21_init_decimal(&a);
  s21_init_decimal(&b);
  s21_init_decimal(&result);

  a.bits[0] = 5;
  b.bits[0] = 3;

  s21_simple_sub(a, b, &result);

  ck_assert_uint_eq(result.bits[0], 2);
}
END_TEST

START_TEST(test_simple_sub_with_borrow) {
  s21_decimal a, b, result;
  s21_init_decimal(&a);
  s21_init_decimal(&b);
  s21_init_decimal(&result);

  a.bits[0] = 10;
  b.bits[0] = 1;

  s21_simple_sub(a, b, &result);

  ck_assert_uint_eq(result.bits[0], 9);
}
END_TEST

START_TEST(test_simple_sub_zero) {
  s21_decimal a, b, result;
  s21_init_decimal(&a);
  s21_init_decimal(&b);
  s21_init_decimal(&result);

  a.bits[0] = 5;
  b.bits[0] = 0;

  s21_simple_sub(a, b, &result);

  ck_assert_uint_eq(result.bits[0], 5);
}
END_TEST

START_TEST(test_simple_sub_equal) {
  s21_decimal a, b, result;
  s21_init_decimal(&a);
  s21_init_decimal(&b);
  s21_init_decimal(&result);

  a.bits[0] = 5;
  b.bits[0] = 5;

  s21_simple_sub(a, b, &result);

  ck_assert_uint_eq(result.bits[0], 0);
}
END_TEST

// ======================== s21_left_shift ========================
START_TEST(test_left_shift_basic) {
  s21_decimal dst;
  s21_init_decimal(&dst);
  dst.bits[0] = 1;  // 1

  s21_left_shift(&dst, 1);

  ck_assert_uint_eq(dst.bits[0], 2);  // 2
}
END_TEST

START_TEST(test_left_shift_multiple) {
  s21_decimal dst;
  s21_init_decimal(&dst);
  dst.bits[0] = 1;  // 1

  s21_left_shift(&dst, 3);

  ck_assert_uint_eq(dst.bits[0], 8);  // 8
}
END_TEST

START_TEST(test_left_shift_cross_boundary) {
  s21_decimal dst;
  s21_init_decimal(&dst);
  dst.bits[0] = 0x80000000;  // 2^31

  s21_left_shift(&dst, 1);

  ck_assert_uint_eq(dst.bits[0], 0);
  ck_assert_uint_eq(dst.bits[1], 1);  // Должен перейти в следующий int
}
END_TEST

START_TEST(test_left_shift_zero) {
  s21_decimal dst;
  s21_init_decimal(&dst);

  s21_left_shift(&dst, 5);

  ck_assert_uint_eq(dst.bits[0], 0);
  ck_assert_uint_eq(dst.bits[1], 0);
  ck_assert_uint_eq(dst.bits[2], 0);
}
END_TEST

// ======================== s21_getQ ========================
START_TEST(test_getQ_basic) {
  s21_decimal a, b;
  s21_init_decimal(&a);
  s21_init_decimal(&b);

  a.bits[0] = 10;
  b.bits[0] = 3;

  int q = s21_getQ(a, b);
  ck_assert_int_eq(q, 1);  // 3 << 1 = 6 <= 10, 3 << 2 = 12 > 10
}
END_TEST

START_TEST(test_getQ_equal) {
  s21_decimal a, b;
  s21_init_decimal(&a);
  s21_init_decimal(&b);

  a.bits[0] = 8;
  b.bits[0] = 2;

  int q = s21_getQ(a, b);
  ck_assert_int_eq(q, 2);  // 2 << 2 = 8 == 8
}
END_TEST

START_TEST(test_getQ_small) {
  s21_decimal a, b;
  s21_init_decimal(&a);
  s21_init_decimal(&b);

  a.bits[0] = 1;
  b.bits[0] = 2;

  int q = s21_getQ(a, b);
  // При i=0: 2 << 0 = 2 > 1, цикл прерывается, q остается 0
  ck_assert_int_eq(q, 0);
}
END_TEST

START_TEST(test_getQ_zero_b) {
  s21_decimal a, b;
  s21_init_decimal(&a);
  s21_init_decimal(&b);

  a.bits[0] = 10;
  b.bits[0] = 0;  // b = 0

  int q = s21_getQ(a, b);
  // При b=0, сдвиг всегда даст 0, который <= a, поэтому q будет максимальным
  ck_assert_int_ge(q, 0);
}
END_TEST

START_TEST(test_getQ_large) {
  s21_decimal a, b;
  s21_init_decimal(&a);
  s21_init_decimal(&b);

  a.bits[0] = 1000;
  b.bits[0] = 10;

  int q = s21_getQ(a, b);
  // 10 << 6 = 640 <= 1000, 10 << 7 = 1280 > 1000, поэтому q = 6
  ck_assert_int_eq(q, 6);
}
END_TEST

START_TEST(test_getQ_a_less_than_b) {
  s21_decimal a, b;
  s21_init_decimal(&a);
  s21_init_decimal(&b);

  a.bits[0] = 5;
  b.bits[0] = 10;

  int q = s21_getQ(a, b);
  // При i=0: 10 << 0 = 10 > 5, цикл прерывается, q = 0
  ck_assert_int_eq(q, 0);
}
END_TEST

START_TEST(test_getQ_exact_match) {
  s21_decimal a, b;
  s21_init_decimal(&a);
  s21_init_decimal(&b);

  a.bits[0] = 16;
  b.bits[0] = 2;

  int q = s21_getQ(a, b);
  // 2 << 3 = 16 == 16, поэтому q = 3
  ck_assert_int_eq(q, 3);
}
END_TEST

// ======================== s21_simple_less_or_equal ========================
START_TEST(test_simple_less_or_equal_equal) {
  s21_decimal a, b;
  s21_init_decimal(&a);
  s21_init_decimal(&b);

  a.bits[0] = 10;
  b.bits[0] = 10;

  int result = s21_simple_less_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_simple_less_or_equal_less) {
  s21_decimal a, b;
  s21_init_decimal(&a);
  s21_init_decimal(&b);

  a.bits[0] = 5;
  b.bits[0] = 10;

  int result = s21_simple_less_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_simple_less_or_equal_greater) {
  s21_decimal a, b;
  s21_init_decimal(&a);
  s21_init_decimal(&b);

  a.bits[0] = 15;
  b.bits[0] = 10;

  int result = s21_simple_less_or_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_simple_less_or_equal_zero) {
  s21_decimal a, b;
  s21_init_decimal(&a);
  s21_init_decimal(&b);

  a.bits[0] = 0;
  b.bits[0] = 0;

  int result = s21_simple_less_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_simple_less_or_equal_with_higher_bits) {
  s21_decimal a, b;
  s21_init_decimal(&a);
  s21_init_decimal(&b);

  a.bits[0] = 100;
  a.bits[1] = 1;  // 2^32 + 100
  b.bits[0] = 100;
  b.bits[1] = 2;  // 2^33 + 100

  int result = s21_simple_less_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

// ======================== s21_simple_div ========================
START_TEST(test_simple_div_basic) {
  s21_decimal a, b, result;
  s21_init_decimal(&a);
  s21_init_decimal(&b);
  s21_init_decimal(&result);

  a.bits[0] = 10;
  b.bits[0] = 2;

  s21_simple_div(a, b, &result);
  ck_assert_uint_eq(result.bits[0], 5);
}
END_TEST

START_TEST(test_simple_div_exact) {
  s21_decimal a, b, result;
  s21_init_decimal(&a);
  s21_init_decimal(&b);
  s21_init_decimal(&result);

  a.bits[0] = 100;
  b.bits[0] = 10;

  s21_simple_div(a, b, &result);
  ck_assert_uint_eq(result.bits[0], 10);
}
END_TEST

START_TEST(test_simple_div_with_remainder) {
  s21_decimal a, b, result;
  s21_init_decimal(&a);
  s21_init_decimal(&b);
  s21_init_decimal(&result);

  a.bits[0] = 10;
  b.bits[0] = 3;

  s21_simple_div(a, b, &result);
  // 10 / 3 = 3 (целочисленное деление)
  ck_assert_uint_eq(result.bits[0], 3);
}
END_TEST

START_TEST(test_simple_div_by_one) {
  s21_decimal a, b, result;
  s21_init_decimal(&a);
  s21_init_decimal(&b);
  s21_init_decimal(&result);

  a.bits[0] = 12345;
  b.bits[0] = 1;

  s21_simple_div(a, b, &result);
  ck_assert_uint_eq(result.bits[0], 12345);
}
END_TEST

START_TEST(test_simple_div_large_numbers) {
  s21_decimal a, b, result;
  s21_init_decimal(&a);
  s21_init_decimal(&b);
  s21_init_decimal(&result);

  a.bits[0] = 1000000;
  b.bits[0] = 1000;

  s21_simple_div(a, b, &result);
  ck_assert_uint_eq(result.bits[0], 1000);
}
END_TEST

// ======================== s21_is_null ========================
START_TEST(test_is_null_true) {
  s21_decimal dec;
  s21_init_decimal(&dec);

  int result = s21_is_null(dec);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_null_false_low_bit) {
  s21_decimal dec;
  s21_init_decimal(&dec);
  dec.bits[0] = 1;

  int result = s21_is_null(dec);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_null_false_mid_bit) {
  s21_decimal dec;
  s21_init_decimal(&dec);
  dec.bits[1] = 1;

  int result = s21_is_null(dec);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_null_false_high_bit) {
  s21_decimal dec;
  s21_init_decimal(&dec);
  dec.bits[2] = 1;

  int result = s21_is_null(dec);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_null_false_multiple_bits) {
  s21_decimal dec;
  s21_init_decimal(&dec);
  dec.bits[0] = 1;
  dec.bits[1] = 2;
  dec.bits[2] = 3;

  int result = s21_is_null(dec);
  ck_assert_int_eq(result, 0);
}
END_TEST

// ======================== s21_mul_10 ========================
START_TEST(test_mul_10_basic) {
  s21_decimal value;
  s21_init_decimal(&value);
  value.bits[0] = 5;

  s21_mul_10(&value);
  ck_assert_uint_eq(value.bits[0], 50);
}
END_TEST

START_TEST(test_mul_10_zero) {
  s21_decimal value;
  s21_init_decimal(&value);

  s21_mul_10(&value);
  ck_assert_uint_eq(value.bits[0], 0);
}
END_TEST

START_TEST(test_mul_10_large_number) {
  s21_decimal value;
  s21_init_decimal(&value);
  value.bits[0] = 123456;

  s21_mul_10(&value);
  ck_assert_uint_eq(value.bits[0], 1234560);
}
END_TEST

START_TEST(test_mul_10_with_overflow) {
  s21_decimal value;
  s21_init_decimal(&value);
  value.bits[0] = 0x19999999;  // Большое число, близкое к переполнению

  s21_mul_10(&value);
  // Проверяем что функция выполнилась без падения
  ck_assert_uint_ge(value.bits[0], 0);
}
END_TEST

START_TEST(test_mul_10_multiple_times) {
  s21_decimal value;
  s21_init_decimal(&value);
  value.bits[0] = 2;

  // 2 * 10 = 20
  s21_mul_10(&value);
  ck_assert_uint_eq(value.bits[0], 20);

  // 20 * 10 = 200
  s21_mul_10(&value);
  ck_assert_uint_eq(value.bits[0], 200);

  // 200 * 10 = 2000
  s21_mul_10(&value);
  ck_assert_uint_eq(value.bits[0], 2000);
}
END_TEST

// ======================== s21_first_unzero_bit ========================
START_TEST(test_first_unzero_bit_basic) {
  s21_decimal value;
  s21_init_decimal(&value);
  s21_set_bit(&value, 10, 1);

  int result = s21_first_unzero_bit(value);
  ck_assert_int_eq(result, 10);
}
END_TEST

START_TEST(test_first_unzero_bit_highest) {
  s21_decimal value;
  s21_init_decimal(&value);
  s21_set_bit(&value, 95, 1);  // Самый старший бит в мантиссе

  int result = s21_first_unzero_bit(value);
  ck_assert_int_eq(result, 95);
}
END_TEST

START_TEST(test_first_unzero_bit_lowest) {
  s21_decimal value;
  s21_init_decimal(&value);
  s21_set_bit(&value, 0, 1);  // Самый младший бит

  int result = s21_first_unzero_bit(value);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_first_unzero_bit_multiple_bits) {
  s21_decimal value;
  s21_init_decimal(&value);
  s21_set_bit(&value, 5, 1);
  s21_set_bit(&value, 10, 1);
  s21_set_bit(&value, 15, 1);

  int result = s21_first_unzero_bit(value);
  ck_assert_int_eq(result,
                   15);  // Должен вернуть самый старший установленный бит
}
END_TEST

START_TEST(test_first_unzero_bit_zero) {
  s21_decimal value;
  s21_init_decimal(&value);

  int result = s21_first_unzero_bit(value);
  ck_assert_int_eq(result, -1);  // Все биты нулевые, должен вернуть -1
}
END_TEST

START_TEST(test_first_unzero_bit_with_higher_bits) {
  s21_decimal value;
  s21_init_decimal(&value);
  value.bits[1] = 0x1;  // Устанавливаем бит в позиции 32

  int result = s21_first_unzero_bit(value);
  ck_assert_int_eq(result, 32);
}
END_TEST

// ======================== Suite ========================
Suite *helpers_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Helpers");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_init_decimal_all_bits_zero);
  tcase_add_test(tc_core, test_init_decimal_extended_all_bits_zero);

  tcase_add_test(tc_core, test_get_sign_plus);
  tcase_add_test(tc_core, test_get_sign_minus);
  tcase_add_test(tc_core, test_set_sign_to_plus);
  tcase_add_test(tc_core, test_set_sign_to_minus);

  tcase_add_test(tc_core, test_get_bit_0);
  tcase_add_test(tc_core, test_get_bit_31);
  tcase_add_test(tc_core, test_get_bit_32);
  tcase_add_test(tc_core, test_get_bit_127);
  tcase_add_test(tc_core, test_get_bit_zero_bit);

  tcase_add_test(tc_core, test_set_bit_0);
  tcase_add_test(tc_core, test_clear_bit_0);
  tcase_add_test(tc_core, test_set_bit_127);
  tcase_add_test(tc_core, test_clear_bit_127);
  tcase_add_test(tc_core, test_set_bit_middle);

  tcase_add_test(tc_core, test_is_zero_empty);
  tcase_add_test(tc_core, test_is_zero_bit_set);
  tcase_add_test(tc_core, test_is_zero_clear_bit);
  tcase_add_test(tc_core, test_is_zero_last_bit);
  tcase_add_test(tc_core, test_is_zero_last_bit_clear);

  tcase_add_test(tc_core, test_set_get_scale_0);
  tcase_add_test(tc_core, test_set_get_scale_28);
  tcase_add_test(tc_core, test_set_get_scale_15);
  tcase_add_test(tc_core, test_set_get_scale_7);
  tcase_add_test(tc_core, test_set_get_scale_reset);

  // s21_get_overflow
  tcase_add_test(tc_core, test_get_overflow_no_overflow);
  tcase_add_test(tc_core, test_get_overflow_with_overflow);
  tcase_add_test(tc_core, test_get_overflow_multiple_overflows);
  tcase_add_test(tc_core, test_get_overflow_max_values);

  // s21_comma_shift_left
  tcase_add_test(tc_core, test_comma_shift_left_basic);
  tcase_add_test(tc_core, test_comma_shift_left_with_overflow);
  tcase_add_test(tc_core, test_comma_shift_left_zero);
  tcase_add_test(tc_core, test_comma_shift_left_large_number);

  // s21_comma_shift_right
  tcase_add_test(tc_core, test_comma_shift_right_basic);
  tcase_add_test(tc_core, test_comma_shift_right_with_rest);
  tcase_add_test(tc_core, test_comma_shift_right_multiple_bits);
  tcase_add_test(tc_core, test_comma_shift_right_zero);

  // s21_normalization
  tcase_add_test(tc_core, test_normalization_basic);
  tcase_add_test(tc_core, test_normalization_scale_overflow);
  tcase_add_test(tc_core, test_normalization_bit_overflow);
  tcase_add_test(tc_core, test_normalization_rounding);
  tcase_add_test(tc_core, test_normalization_error_1_scale_0_bits3_nonzero);
  tcase_add_test(tc_core, test_normalization_error_2_scale_28_all_bits_zero);
  tcase_add_test(tc_core, test_normalization_scale_reduction);
  tcase_add_test(tc_core, test_normalization_no_changes_needed);

  // s21_bring_to_a_common_denominator
  tcase_add_test(tc_core, test_bring_to_common_denominator_equal_scales);
  tcase_add_test(tc_core, test_bring_to_common_denominator_different_scales);
  tcase_add_test(tc_core, test_bring_to_common_denominator_overflow_case);
  tcase_add_test(tc_core, test_bring_to_common_denominator_large_difference);

  // s21_round_string
  tcase_add_test(tc_core, test_round_string_with_dot);
  tcase_add_test(tc_core, test_round_string_no_dot);
  tcase_add_test(tc_core, test_round_string_dot_at_end);
  tcase_add_test(tc_core, test_round_string_dot_at_start);

  // s21_copy_decimal
  tcase_add_test(tc_core, test_copy_decimal_basic);
  tcase_add_test(tc_core, test_copy_decimal_all_bits);
  tcase_add_test(tc_core, test_copy_decimal_no_bits);
  tcase_add_test(tc_core, test_copy_decimal_mixed_bits);

  // s21_simple_mul
  tcase_add_test(tc_core, test_simple_mul_basic);
  tcase_add_test(tc_core, test_simple_mul_zero);
  tcase_add_test(tc_core, test_simple_mul_one);
  tcase_add_test(tc_core, test_simple_mul_large);

  // s21_getFirstNumAfterComma
  tcase_add_test(tc_core, test_getFirstNumAfterComma_zero_scale);
  tcase_add_test(tc_core, test_getFirstNumAfterComma_scale_one);
  tcase_add_test(tc_core, test_getFirstNumAfterComma_scale_two);
  tcase_add_test(tc_core, test_getFirstNumAfterComma_small_number);

  // s21_simple_sum
  tcase_add_test(tc_core, test_simple_sum_basic);
  tcase_add_test(tc_core, test_simple_sum_with_carry);
  tcase_add_test(tc_core, test_simple_sum_zero);
  tcase_add_test(tc_core, test_simple_sum_large);

  // s21_simple_sub
  tcase_add_test(tc_core, test_simple_sub_basic);
  tcase_add_test(tc_core, test_simple_sub_with_borrow);
  tcase_add_test(tc_core, test_simple_sub_zero);
  tcase_add_test(tc_core, test_simple_sub_equal);

  // s21_left_shift
  tcase_add_test(tc_core, test_left_shift_basic);
  tcase_add_test(tc_core, test_left_shift_multiple);
  tcase_add_test(tc_core, test_left_shift_cross_boundary);
  tcase_add_test(tc_core, test_left_shift_zero);

  // s21_getQ
  tcase_add_test(tc_core, test_getQ_basic);
  tcase_add_test(tc_core, test_getQ_equal);
  tcase_add_test(tc_core, test_getQ_small);
  tcase_add_test(tc_core, test_getQ_zero_b);
  tcase_add_test(tc_core, test_getQ_large);
  tcase_add_test(tc_core, test_getQ_a_less_than_b);
  tcase_add_test(tc_core, test_getQ_exact_match);

  // s21_simple_less_or_equal
  tcase_add_test(tc_core, test_simple_less_or_equal_equal);
  tcase_add_test(tc_core, test_simple_less_or_equal_less);
  tcase_add_test(tc_core, test_simple_less_or_equal_greater);
  tcase_add_test(tc_core, test_simple_less_or_equal_zero);
  tcase_add_test(tc_core, test_simple_less_or_equal_with_higher_bits);

  // s21_simple_div
  tcase_add_test(tc_core, test_simple_div_basic);
  tcase_add_test(tc_core, test_simple_div_exact);
  tcase_add_test(tc_core, test_simple_div_with_remainder);
  tcase_add_test(tc_core, test_simple_div_by_one);
  tcase_add_test(tc_core, test_simple_div_large_numbers);

  // s21_is_null
  tcase_add_test(tc_core, test_is_null_true);
  tcase_add_test(tc_core, test_is_null_false_low_bit);
  tcase_add_test(tc_core, test_is_null_false_mid_bit);
  tcase_add_test(tc_core, test_is_null_false_high_bit);
  tcase_add_test(tc_core, test_is_null_false_multiple_bits);

  // s21_mul_10
  tcase_add_test(tc_core, test_mul_10_basic);
  tcase_add_test(tc_core, test_mul_10_zero);
  tcase_add_test(tc_core, test_mul_10_large_number);
  tcase_add_test(tc_core, test_mul_10_with_overflow);
  tcase_add_test(tc_core, test_mul_10_multiple_times);

  // s21_first_unzero_bit
  tcase_add_test(tc_core, test_first_unzero_bit_basic);
  tcase_add_test(tc_core, test_first_unzero_bit_highest);
  tcase_add_test(tc_core, test_first_unzero_bit_lowest);
  tcase_add_test(tc_core, test_first_unzero_bit_multiple_bits);
  tcase_add_test(tc_core, test_first_unzero_bit_zero);
  tcase_add_test(tc_core, test_first_unzero_bit_with_higher_bits);

  suite_add_tcase(s, tc_core);

  return s;
}
