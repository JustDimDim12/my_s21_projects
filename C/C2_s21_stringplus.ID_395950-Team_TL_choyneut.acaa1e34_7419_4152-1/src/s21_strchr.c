#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *result = s21_NULL;
  if (str != s21_NULL) {
    unsigned char ch = (unsigned char)c;

    for (s21_size_t i = 0;; i++) {
      if (str[i] == ch) {
        result = (char *)(str + i);
        break;
      }
      if (str[i] == '\0') {
        break;
      }
    }
  }
  return result;
}