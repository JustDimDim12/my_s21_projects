#include <stdlib.h>

#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = s21_NULL;

  if (src != s21_NULL) {
    if (trim_chars == s21_NULL) {
      trim_chars = " \t\n\r\f\v";
    }

    s21_size_t len = s21_strlen(src);
    s21_size_t start = 0;
    s21_size_t end = len;

    while (start < len && s21_strchr(trim_chars, src[start]) != s21_NULL) {
      ++start;
    }

    while (end > start && s21_strchr(trim_chars, src[end - 1]) != s21_NULL) {
      --end;
    }

    s21_size_t result_len = end - start;
    result = (char *)malloc(result_len + 1);

    if (result != s21_NULL) {
      s21_memcpy(result, src + start, result_len);
      result[result_len] = '\0';
    }
  }

  return result;
}