#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  uint64_t bits[7];
  short scale;
} s21_decimal_extended;

#define MINUS 0x80000000
#define SCALE 0x00ff0000
#define MAXBITS 0xffffffff
#define MAXBITSEXT 0xffffffffffffffff

#define S21_NUM_WORDS 4
#define CONVERT_ERROR 1
#define CONVERSION_SUCCESS 0
#define CONVERSION_OVERFLOW 1
#define CONVERSION_UNDERFLOW 2

#define DEC_MIN 1e-28
#define DEC_MAX 79228162514264337593543950335.0f

enum state { FALSE = 0, TRUE = 1 };
enum errors { OK = 0, ERROR = 1 };
enum arithmetic_errors { S21_INF = 1, S21_NEG_INF = 2, S21_NAN = 3 };

// Арифметические функции
int s21_add(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // +
int s21_sub(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // -
int s21_mul(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // *
int s21_div(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // /

// Операторы сравнения
int s21_is_less(s21_decimal value_1, s21_decimal value_2);              // <
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);     // <=
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);           // >
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);  // >=
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);             // ==
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);         // !=
// -------------------

// конвертация
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
// -------------------

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// Функции-хелперы
int s21_init_decimal(s21_decimal *dst);
int s21_init_decimal_extended(s21_decimal_extended *dst);
void s21_set_bit(s21_decimal *value, int position, int bit);
void s21_set_bit_ext(s21_decimal_extended *value, int position, int bit);
int s21_get_sign(s21_decimal *value);
void s21_set_sign(s21_decimal *value, int sign);
int s21_get_bit(s21_decimal *value, int position);
int s21_get_bit_ext(s21_decimal_extended *value, int position);
int s21_is_zero(s21_decimal value);
int s21_get_scale(s21_decimal *value);
void s21_set_scale(s21_decimal *value, int scale);
s21_decimal_extended s21_convert_to_extended(s21_decimal value);
int s21_convert_from_extended(s21_decimal_extended value, s21_decimal *dst);
void s21_bring_to_a_common_denominator(s21_decimal_extended *value1,
                                       s21_decimal_extended *value2);
int s21_comma_shift_left(s21_decimal_extended *value);
int s21_comma_shift_right(s21_decimal_extended *value);
int s21_get_overflow(s21_decimal_extended *value);
int s21_normalization(s21_decimal_extended *value);
int s21_round_string(char str[14]);
void s21_copy_decimal(s21_decimal *destination, s21_decimal value);
void s21_simple_div(s21_decimal a, s21_decimal b, s21_decimal *result);
int s21_simple_less_or_equal(s21_decimal val1, s21_decimal val2);
int s21_getQ(s21_decimal a, s21_decimal b);
void s21_left_shift(s21_decimal *dst, int shift);
void s21_simple_sub(s21_decimal a, s21_decimal b, s21_decimal *result);
int s21_simple_sum(s21_decimal val1, s21_decimal val2, s21_decimal *result);
int s21_getFirstNumAfterComma(s21_decimal value);
void s21_simple_mul(s21_decimal a, s21_decimal b, s21_decimal *c);
int s21_is_null(s21_decimal dec);
void s21_mul_10(s21_decimal *value);
int s21_first_unzero_bit(s21_decimal value);
// -----------------------------------
#endif
