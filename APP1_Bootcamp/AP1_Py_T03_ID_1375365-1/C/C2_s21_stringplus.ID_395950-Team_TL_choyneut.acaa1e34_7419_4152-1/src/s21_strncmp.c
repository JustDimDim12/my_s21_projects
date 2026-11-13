#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  s21_size_t i = 0;
  int finished = 0;

  while (i < n && !finished) {
    unsigned char c1 = (unsigned char)str1[i];
    unsigned char c2 = (unsigned char)str2[i];

    if (c1 != c2) {
      result = (int)c1 - (int)c2;
      finished = 1;
    } else if (c1 == '\0') {
      finished = 1;
    } else {
      i++;
    }
  }
  return result;
}
