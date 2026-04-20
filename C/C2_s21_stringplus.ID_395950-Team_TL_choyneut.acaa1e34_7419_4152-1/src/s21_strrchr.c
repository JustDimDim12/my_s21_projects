#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *result = s21_NULL;
  if (str != s21_NULL) {
    unsigned char ch = (unsigned char)c;
    s21_size_t i = 0;

    while (str[i] != '\0') {
      if (str[i] == ch) {
        result = (char *)(str + i);
      }
      i++;
    }

    if (ch == '\0') {
      result = (char *)(str + i);
    }
  }
  return result;
}