#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  const char *result = s21_NULL;

  if (*needle == '\0') {
    result = haystack;
  } else {
    const char *h = (const char *)haystack;
    const char *n = (const char *)needle;
    int found = 0;

    while (*h != '\0' && !found) {
      const char *h_temp = h;
      const char *n_temp = n;

      while (*n_temp != '\0' && *h_temp == *n_temp) {
        h_temp++;
        n_temp++;
      }

      if (*n_temp == '\0') {
        result = h;
        found = 1;
      }

      h++;
    }
  }
  return (char *)result;
}