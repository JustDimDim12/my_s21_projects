#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

void *s21_to_upper(const char *str) {
  char *result = s21_NULL;
  if (str != s21_NULL) {
    s21_size_t len = s21_strlen(str);
    char *new_str = (char *)malloc(len + 1);

    if (new_str != s21_NULL) {
      for (s21_size_t i = 0; i <= len; i++) {
        char c = str[i];
        if (c >= 'a' && c <= 'z') {
          new_str[i] = c - 32;
        } else {
          new_str[i] = c;
        }
      }
      result = new_str;
    }
  }
  return result;
}