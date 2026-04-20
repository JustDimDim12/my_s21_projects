#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *ptr = (const unsigned char *)str;
  unsigned char ch = (unsigned char)c;
  int flag = 0;
  void *result = s21_NULL;

  for (s21_size_t i = 0; i < n && !flag; i++, ptr++) {
    if (*ptr == ch) {
      result = (void *)ptr;
      flag = 1;
    }
  }

  return result;
}