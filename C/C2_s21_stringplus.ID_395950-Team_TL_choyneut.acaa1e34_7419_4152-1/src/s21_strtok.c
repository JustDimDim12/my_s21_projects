#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *save_ptr = s21_NULL;
  char *result = s21_NULL;
  char *ptr = (str != s21_NULL) ? str : save_ptr;

  if (ptr != s21_NULL && *ptr != '\0') {
    char *token_start = s21_NULL;

    while (*ptr != '\0') {
      const char *d = delim;
      int is_delim = 0;

      while (*d != '\0') {
        if (*ptr == *d) {
          is_delim = 1;
          break;
        }
        d++;
      }

      if (!is_delim) {
        token_start = ptr;
        break;
      }
      ptr++;
    }

    if (token_start != s21_NULL) {
      char *token_end = token_start;

      while (*token_end != '\0') {
        const char *d = delim;
        int is_delim = 0;

        while (*d != '\0') {
          if (*token_end == *d) {
            is_delim = 1;
            break;
          }
          d++;
        }

        if (is_delim) {
          *token_end = '\0';
          save_ptr = token_end + 1;
          result = token_start;
          break;
        }
        token_end++;
      }

      if (result == s21_NULL) {
        result = token_start;
        save_ptr = token_end;
      }
    } else {
      save_ptr = s21_NULL;
    }
  } else {
    save_ptr = s21_NULL;
  }

  return result;
}