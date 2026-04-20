#include "s21_decimal.h"

// обнуляет decimal
int s21_init_decimal(s21_decimal *dst) {
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = 0;
  }
  return 0;
}

int s21_init_decimal_extended(s21_decimal_extended *dst) {
  for (int i = 0; i < 7; i++) {
    dst->bits[i] = 0;
  }
  return 0;
}

// чекает знак +/- числа в структуре decimal (0 "+", 1 "-")
int s21_get_sign(s21_decimal *value) { return s21_get_bit(value, 127); }

// установить знак числа sign (0 плюс, 1 минус) в структуре decimal
void s21_set_sign(s21_decimal *value, int sign) {
  if (sign == 0)
    value->bits[3] = value->bits[3] & ~(1U << 31);
  else
    value->bits[3] = value->bits[3] | (1U << 31);
}

// чекает значение бита в структуре decimal (0 или 1) на position (от 0 до 127)
int s21_get_bit(s21_decimal *value, int position) {
  return ((value->bits[position / 32] & ((1U << (position % 32)))) != 0);
}

// чекает значение бита в структуре расшренного decimal (0 или 1) на position
// (от 0 до 127)
int s21_get_bit_ext(s21_decimal_extended *value, int position) {
  return ((value->bits[position / 32] & ((1U << (position % 32)))) != 0);
}

// установить значение бита в структуре decimal на позицию от 0 до 127
void s21_set_bit(s21_decimal *value, int position, int bit) {
  if (bit == 0)
    value->bits[position / 32] =
        value->bits[position / 32] & ~(1U << (position % 32));
  else
    value->bits[position / 32] =
        value->bits[position / 32] | (1U << (position % 32));
}

void s21_set_bit_ext(s21_decimal_extended *value, int position, int bit) {
  if (bit == 0)
    value->bits[position / 32] =
        value->bits[position / 32] & ~(1U << (position % 32));
  else
    value->bits[position / 32] =
        value->bits[position / 32] | (1U << (position % 32));
}

// чекает равняется ли число decimal нулю?
int s21_is_zero(s21_decimal value) {
  int flag = 1;
  for (int i = 0; i < 96; i++)  // проходит по всем битам мантиссы
    if (s21_get_bit(&value, i) != 0) flag = 0;  //+
  return flag;
}

// проверить значение коэффициента масштабирования
int s21_get_scale(s21_decimal *value) {
  int mask = 0b11111111;
  return (mask << 16 & value->bits[3]) >> 16;
}

// установить значение коэффициента масштабирования
void s21_set_scale(s21_decimal *value, int scale) {
  value->bits[3] =
      ((unsigned int)s21_get_bit(value, 127) << 31) | (scale << 16);
}

// преобразует стандартный decimal в расширенный
s21_decimal_extended s21_convert_to_extended(s21_decimal value) {
  s21_decimal_extended extended;
  for (int i = 0; i < 3; i++) {
    extended.bits[i] = value.bits[i] & MAXBITS;
  }
  for (int i = 3; i < 7; i++) {
    extended.bits[i] = 0;
  }
  extended.scale = s21_get_scale(&value);
  return extended;
}

// преобразует расширенный decimal в стандартный
int s21_convert_from_extended(s21_decimal_extended value, s21_decimal *dst) {
  for (int i = 0; i < 3; i++) dst->bits[i] = value.bits[i] & MAXBITS;
  s21_set_scale(dst, value.scale);
  return 1;
}

// обработка переполнения в decimal формате
int s21_get_overflow(s21_decimal_extended *value) {
  uint64_t overflow = 0;
  for (int i = 0; i < 7; i++) {
    value->bits[i] += overflow;
    overflow = value->bits[i] >> 32;
    value->bits[i] &= MAXBITS;
  }
  if (overflow != 0) overflow = 1;
  return overflow;
}

// умножение всех битовых полей на 10 (сдвиг влево)
int s21_comma_shift_left(s21_decimal_extended *value) {
  int flag = 0;
  s21_decimal_extended tmp = *value;
  for (int i = 0; i < 7; i++) tmp.bits[i] *= 10;
  if (s21_get_overflow(&tmp)) {
    flag = 1;
  }
  tmp.scale++;
  if (flag)
    ;
  else
    *value = tmp;
  return flag;
}

// деление всех битовых полей на 10 (сдвиг вправо)
int s21_comma_shift_right(s21_decimal_extended *value) {
  long int rest = 0;
  for (int i = 6; i >= 0; i--) {
    value->bits[i] += rest << 32;
    rest = value->bits[i] % 10;
    value->bits[i] /= 10;
  }
  value->scale--;
  return rest;
}

// нормализует расширенный decimal (обрабатывает переполнение и округление)
int s21_normalization(s21_decimal_extended *value) {
  int code_error = 0, last_rest = 0, existanceOfRest = 0;
  for (int i = 3; i < 7; i++) {
    while (value->bits[i] != 0 && value->scale > 0) {
      if ((last_rest = s21_comma_shift_right(value))) existanceOfRest++;
    }
  }
  if (value->scale > 28) {
    while (value->scale != 28) {
      if ((last_rest = s21_comma_shift_right(value))) existanceOfRest++;
    }
  }
  if (last_rest > 5) {
    value->bits[0] += 1;
    s21_get_overflow(value);
  } else if (last_rest < 5 && last_rest != 0)
    ;
  else if (last_rest == 5 && existanceOfRest > 1) {
    value->bits[0] += 1;
    s21_get_overflow(value);
  } else if (last_rest == 5 && existanceOfRest == 1) {
    if ((value->bits[0] % 10) % 2 != 0) {
      value->bits[0] += 1;
      s21_get_overflow(value);
    }
  }
  if (value->scale == 0 && value->bits[3] != 0)
    code_error = 1;
  else if (value->scale == 28 && value->bits[0] == 0 && value->bits[1] == 0 &&
           value->bits[2] == 0)
    code_error = 2;
  return code_error;
}

// приводит к общему знаменателю два decimal extended
void s21_bring_to_a_common_denominator(s21_decimal_extended *value1,
                                       s21_decimal_extended *value2) {
  int flag = 0;
  int cnt = 0;
  if (value1->scale < value2->scale) {
    for (int i = 0; value1->scale != value2->scale; i++, cnt++)
      if ((flag = s21_comma_shift_left(value1))) break;  // +
  } else if (value1->scale > value2->scale) {
    for (int i = 0; value2->scale != value1->scale; i++, cnt++)
      if ((flag = s21_comma_shift_left(value2))) break;  // +
  }
  s21_get_overflow(value1);  // +
  s21_get_overflow(value2);  // +
}

int s21_round_string(char str[14]) {
  int pos_of_dot = -1;
  int str_len = strlen(str);
  for (int i = 0; i < str_len; i++) {
    if (str[i] == '.') pos_of_dot = i;
    if (pos_of_dot != -1) str[i] = str[i + 1];
  }
  return pos_of_dot != -1 ? str_len - pos_of_dot - 1 : -1;
}

// побитовое копирование структуры value по адресу dest
void s21_copy_decimal(s21_decimal *destination, s21_decimal value) {
  for (int i = 127; i >= 0; i--) {
    s21_set_bit(destination, i, s21_get_bit(&value, i));
  }
}

// хелперы для четвёртого задания

void s21_simple_mul(s21_decimal a, s21_decimal b, s21_decimal *c) {
  s21_init_decimal(c);
  for (int i = 0; i < 96; i++) {
    if (s21_get_bit(&a, i) == 1) {
      s21_decimal tmp_c;
      s21_init_decimal(&tmp_c);
      s21_copy_decimal(&tmp_c, *c);
      s21_decimal tmp_b;
      s21_init_decimal(&tmp_b);
      s21_copy_decimal(&tmp_b, b);
      s21_left_shift(&tmp_b, i);
      s21_simple_sum(tmp_c, tmp_b, c);
    }
  }
}

int s21_getFirstNumAfterComma(s21_decimal value) {
  s21_decimal result, devider, tmp_result, multiplied_result;
  s21_init_decimal(&devider);
  s21_init_decimal(&tmp_result);
  s21_init_decimal(&result);
  s21_init_decimal(&multiplied_result);
  devider.bits[0] = 10;
  int fnac = 0;
  if (s21_get_scale(&value) == 0) {
    fnac = 0;
  } else if (s21_get_scale(&value) == 1) {
    s21_simple_div(value, devider, &tmp_result);
    s21_simple_mul(tmp_result, devider, &result);
    s21_simple_sub(value, result, &tmp_result);
    fnac = tmp_result.bits[0];
  } else {
    s21_copy_decimal(&result, value);

    for (int i = 0; i < s21_get_scale(&value); i++) {
      s21_simple_div(result, devider, &tmp_result);
      s21_copy_decimal(&result, tmp_result);
    }

    for (int i = 0; i < s21_get_scale(&value); i++) {
      s21_simple_mul(tmp_result, devider, &multiplied_result);
      s21_copy_decimal(&tmp_result, multiplied_result);
    }

    s21_simple_sub(value, multiplied_result, &tmp_result);

    for (int i = 0; i < s21_get_scale(&value) - 1; i++) {
      s21_simple_div(tmp_result, devider, &result);
      s21_copy_decimal(&tmp_result, result);
    }
    fnac = result.bits[0];
  }
  return fnac;
}

/*
Функция s21_simple_sum корректно складывает 2 целых, неотрициательных децимала.
Нет проверки на переполнение числа, предполагается, что сумма чисел заведомо
меньше 96 бит. Все тесты проходит успешно - релиз Основа для более сложных
конструкций
*/
int s21_simple_sum(s21_decimal val1, s21_decimal val2, s21_decimal *result) {
  int overbit = 0;
  for (int i = 0; i < 96; i++) {
    if (s21_get_bit(&val1, i) == 1 && s21_get_bit(&val2, i) == 1 &&
        overbit == 0) {
      s21_set_bit(result, i, 0);
      overbit = 1;
    } else if (s21_get_bit(&val1, i) == 1 && s21_get_bit(&val2, i) == 1 &&
               overbit == 1) {
      s21_set_bit(result, i, 1);
      overbit = 1;
    } else if (((s21_get_bit(&val1, i) == 1 && s21_get_bit(&val2, i) == 0) ||
                (s21_get_bit(&val1, i) == 0 && s21_get_bit(&val2, i) == 1)) &&
               overbit == 0) {
      s21_set_bit(result, i, 1);
      overbit = 0;
    } else if (((s21_get_bit(&val1, i) == 1 && s21_get_bit(&val2, i) == 0) ||
                (s21_get_bit(&val1, i) == 0 && s21_get_bit(&val2, i) == 1)) &&
               overbit == 1) {
      s21_set_bit(result, i, 0);
      overbit = 1;
    } else if (s21_get_bit(&val1, i) == 0 && s21_get_bit(&val2, i) == 0 &&
               overbit == 1) {
      s21_set_bit(result, i, 1);
      overbit = 0;
    } else if (s21_get_bit(&val1, i) == 0 && s21_get_bit(&val2, i) == 0 &&
               overbit == 0) {
      s21_set_bit(result, i, 0);
      overbit = 0;
    }
  }
  return 0;
}

/*
Функция s21_simple_sub корректно вычитает из числа a, число b, резльтат
записывает в число с. Принимает на вход неотрициательные децималы. Нет проверки
на переполнение числа, предполагается, что сумма чисел заведомо меньше 96 бит.
Все тесты проходит успешно - релиз
Основа для более сложных конструкций
*/
void s21_simple_sub(s21_decimal a, s21_decimal b, s21_decimal *result) {
  int overbit_counter = 0;
  int this_bit_must_be_zero = 0;

  for (int i = 0; i < 96; i++) {
    int b_a = s21_get_bit(&a, i);
    int b_b = s21_get_bit(&b, i);

    if (i != 0 && this_bit_must_be_zero == i) b_a = 0;

    if (b_a == 1 && b_b == 1) {
      s21_set_bit(result, i, 0);
    } else if (b_a == 1 && b_b == 0) {
      s21_set_bit(result, i, 1);
    } else if (b_a == 0 &&
               b_b == 1) {  // если из 0 вычитаем 1, то двигаем влево, ищем 1
      if (overbit_counter == 0) {
        while (s21_get_bit(&a, ++overbit_counter + i) != 1);
        this_bit_must_be_zero =
            i + overbit_counter--;  // номер бита у которого мы заняли единицу,
                                    // теперь он 0
        s21_set_bit(result, i, 1);
      } else {
        overbit_counter--;
        s21_set_bit(result, i, 0);
      }
    } else if (b_a == 0 && b_b == 0 && overbit_counter != 0) {
      overbit_counter--;
      s21_set_bit(result, i, 1);
    }
  }
}

void s21_left_shift(s21_decimal *dst, int shift) {
  for (int i = 0; i < shift; i++) {
    int bits_32 = s21_get_bit(dst, 31);
    int bits_64 = s21_get_bit(dst, 63);
    int bits_95 = s21_get_bit(dst, 95);
    int bits_96 = s21_get_bit(dst, 96);
    dst->bits[0] <<= 1;
    dst->bits[1] <<= 1;
    dst->bits[2] <<= 1;
    if (bits_32) s21_set_bit(dst, 32, 1);
    if (bits_64) s21_set_bit(dst, 64, 1);
    if (bits_95) s21_set_bit(dst, 96, 1);
    if (bits_96) s21_set_bit(dst, 97, 1);
  }
}

int s21_getQ(s21_decimal a, s21_decimal b) {
  int q = 0;
  for (int i = 0; i < 97; i++) {
    s21_decimal tmp_b = b;
    s21_left_shift(&tmp_b, i);
    if (s21_simple_less_or_equal(tmp_b, a) == 0) break;
    q = i;
  }
  return q;
}

/*
Функция s21_simple_less_or_equal корректно сравнивает 2 целых, неотрицаиельных
децимала. Все тесты проходит успешно - релих Основа для более сложных
конструкций 0 - FALSE 1 - TRUE
*/
int s21_simple_less_or_equal(s21_decimal val1,
                             s21_decimal val2) {  // 0 - FALSE 1 - TRUE
  int result = 0;

  for (int i = 96; i >= 0; i--) {
    int bit1 = s21_get_bit(&val1, i);
    int bit2 = s21_get_bit(&val2, i);
    if (i == 0 && bit1 == bit2)
      result = 1;
    else if (bit1 != bit2) {
      result = bit1 < bit2;
      break;
    };
  }
  return result;
}

/*
Функция s21_simple_div корректно делит число a, на число b, резльтат записывает
в число с. Принимает на вход неотрициательные децималы. Нет проверки на
переполнение числа, предполагается, что сумма чисел заведомо меньше 96 бит. Все
тесты проходит успешно - релиз Основа для более сложных конструкций
*/
void s21_simple_div(s21_decimal a, s21_decimal b, s21_decimal *result) {
  s21_decimal intermediate_result, tmp_a, S;
  s21_init_decimal(&intermediate_result);
  s21_init_decimal(&tmp_a);
  s21_init_decimal(&S);
  s21_copy_decimal(&tmp_a, a);
  int counter_to_break = 0;

  while (s21_simple_less_or_equal(b, tmp_a) == 1) {
    s21_copy_decimal(&intermediate_result, b);
    int q = s21_getQ(tmp_a, b);
    s21_left_shift(&intermediate_result, q);

    s21_decimal tmp_tmp_a;
    s21_init_decimal(&tmp_tmp_a);                            // -
    s21_simple_sub(tmp_a, intermediate_result, &tmp_tmp_a);  // -
    s21_copy_decimal(&tmp_a, tmp_tmp_a);  // - вычитаем из А промежуточный
                                          // результат и сохраняем его в А

    s21_decimal digit_one;
    s21_init_decimal(&digit_one);
    digit_one.bits[0] = 1;
    s21_left_shift(&digit_one, q);
    s21_decimal tmp_S;
    s21_init_decimal(&tmp_S);
    s21_simple_sum(S, digit_one, &tmp_S);
    s21_copy_decimal(&S, tmp_S);
    if (counter_to_break > 500) break;
    counter_to_break++;
  }
  s21_copy_decimal(result, S);
}

int s21_is_null(s21_decimal dec) {
  int is_null = 0;
  if (dec.bits[0] == 0 && dec.bits[1] == 0 && dec.bits[2] == 0) {
    is_null = 1;
  }
  return is_null;
}

void s21_mul_10(s21_decimal *value) {
  s21_left_shift(value, 1);
  s21_decimal five;
  s21_from_int_to_decimal(5, &five);
  s21_simple_mul(*value, five, value);
}

int s21_first_unzero_bit(s21_decimal value) {
  int i = 95;
  for (; i >= 0; i--) {
    if (s21_get_bit(&value, i)) break;
  }
  return i;
}
