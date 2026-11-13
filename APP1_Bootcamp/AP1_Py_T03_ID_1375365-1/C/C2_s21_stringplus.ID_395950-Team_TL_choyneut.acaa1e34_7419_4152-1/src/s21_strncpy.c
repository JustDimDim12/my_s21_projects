#include "s21_string.h"
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *result = dest;

  if (dest != s21_NULL && src != s21_NULL) {
    s21_size_t i = 0;

    while (i < n && src[i] != '\0') {
      dest[i] = src[i];
      i++;
    }

    while (i < n) {
      dest[i] = '\0';
      i++;
    }
  }

  return result;
}