#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *str_unsigned_char = (unsigned char *)str;
  unsigned char ch = (unsigned char)c;
  for (s21_size_t i = 0; i < n; i++) {
    *str_unsigned_char++ = ch;
  }
  return str;
}