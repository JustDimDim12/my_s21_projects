#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *dest_unsigned_char = (unsigned char *)dest;
  const unsigned char *src_const_unsigned_char = (const unsigned char *)src;
  for (s21_size_t i = 0; i < n; i++) {
    *dest_unsigned_char++ = *src_const_unsigned_char++;
  }
  return dest;
}