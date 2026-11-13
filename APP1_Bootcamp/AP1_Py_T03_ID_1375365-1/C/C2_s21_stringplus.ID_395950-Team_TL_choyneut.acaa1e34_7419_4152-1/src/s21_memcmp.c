#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *first_buffer = (const unsigned char *)str1;
  const unsigned char *second_buffer = (const unsigned char *)str2;
  int result = 0;

  for (s21_size_t i = 0; i < n && result == 0; i++) {
    if (first_buffer[i] != second_buffer[i]) {
      result = (int)(first_buffer[i] - second_buffer[i]);
    }
  }
  return result;
}