#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t result = 0;
  if (str != s21_NULL) {
    while (str[result] != '\0') {
      result++;
    }
  }
  return result;
}