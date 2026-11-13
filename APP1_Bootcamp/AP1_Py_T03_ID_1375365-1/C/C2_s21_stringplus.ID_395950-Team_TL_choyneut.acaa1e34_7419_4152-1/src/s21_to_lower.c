#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *result = s21_NULL;
  if (str != s21_NULL) {
    s21_size_t len = s21_strlen(str);
    result = (char *)malloc(len + 1);

    if (result != s21_NULL) {
      for (s21_size_t i = 0; i <= len; ++i) {
        char c = str[i];
        if (c >= 'A' && c <= 'Z') {
          c = c + ('a' - 'A');
        }
        result[i] = c;
      }
    }
  }
  return result;
}