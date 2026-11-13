#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int code_error = OK;
  if (fabsf(src) == INFINITY || fabsf(src) > DEC_MAX || fabsf(src) < 1e-28 ||
      fabsf(src) == 0.0 || isnan(src)) {
    code_error = ERROR;
  } else {
    s21_init_decimal(dst);
    char str[14] = {0};
    if (src < 0) {
      src = fabsf(src);
      s21_set_sign(dst, 1);
    }
    sprintf(str, "%.7g", src);

    int i = s21_round_string(str);
    int int_src = 0;
    sscanf(str, "%d", &int_src);
    if (abs(int_src)) dst->bits[0] = int_src;
    if (i != -1) s21_set_scale(dst, i);
  }
  return code_error;
}
