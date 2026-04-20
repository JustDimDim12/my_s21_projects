#include "s21_string.h"

char *s21_strerror(int errnum) {
  char *result = s21_NULL;
  static char error_buffer[64];

  if (errnum >= 0 && errnum <= 133) {
    result = (char *)ERRORS[errnum];
  } else {
    s21_sprintf(error_buffer, "Unknown error %d", errnum);
    result = error_buffer;
  }
  return result;
}