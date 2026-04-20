#include "s21_sprintf.h"

static void s21_reverse(char *str, int len) {
  for (int i = 0, j = len - 1; i < j; i++, j--) {
    char tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
  }
}

static int s21_put_single_char(buf_state *buf, char c) {
  int result = 0;
  if (buf && buf->current < buf->end) {
    *buf->current++ = c;
    result = 1;
  }
  return result;
}

static int s21_put_string(buf_state *buf, char *str) {
  int i = 0;
  if (buf && str) {
    while (str[i] && s21_put_single_char(buf, str[i])) i++;
  }

  return str[i] == '\0';
}

static void s21_parse_spec(const char **format, format_params **params) {
  switch (**format) {
    case 'c':
      (*params)->spec = s21_SPEC_CHAR;
      break;
    case 'd':
      (*params)->spec = s21_SPEC_DEC_INT;
      break;
    case 'i':
      (*params)->spec = s21_SPEC_INT;
      break;
    case 'e':
      (*params)->spec = s21_SPEC_EXP_LOW;
      break;
    case 'E':
      (*params)->spec = s21_SPEC_EXP_UP;
      break;
    case 'f':
      (*params)->spec = s21_SPEC_FLOAT;
      break;
    case 'g':
      (*params)->spec = s21_SPEC_GENERAL_LOW;
      break;
    case 'G':
      (*params)->spec = s21_SPEC_GENERAL_UP;
      break;
    case 'o':
      (*params)->spec = s21_SPEC_OCTAL;
      break;
    case 's':
      (*params)->spec = s21_SPEC_STRING;
      break;
    case 'u':
      (*params)->spec = s21_SPEC_UNSIGNED;
      break;
    case 'x':
      (*params)->spec = s21_SPEC_HEX_LOW;
      break;
    case 'X':
      (*params)->spec = s21_SPEC_HEX_UP;
      break;
    case 'p':
      (*params)->spec = s21_SPEC_POINTER;
      break;
    case 'n':
      (*params)->spec = s21_SPEC_LEN;
      break;
    case '%':
      (*params)->spec = s21_SPEC_PERCENT;
      break;
    default:
      break;
  }
  (*format)++;
}

static void s21_parse_length(const char **format, format_params **params) {
  switch (**format) {
    case 'h':
      (*params)->length = sizeof(short);
      (*format)++;
      break;
    case 'l':
      (*params)->length = sizeof(s21_size_t);
      (*format)++;
      break;
    case 'L':
      (*params)->length = sizeof(long double);
      (*format)++;
      break;
    default:
      break;
  }
}

static void s21_parse_precision(const char **format, format_params **params,
                                va_list *argc) {
  if (**format == '.') {
    (*format)++;
    (*params)->precision = 0;
    if (**format == '*') {
      (*params)->precision = va_arg(*argc, int);
      (*format)++;
    } else {
      while (**format >= '0' && **format <= '9') {
        (*params)->precision =
            (*params)->precision * 10 + (int)(**format - '0');
        (*format)++;
      }
    }
  }
}

static void s21_parse_width(const char **format, format_params **params,
                            va_list *argc) {
  if (**format == '*') {
    (*params)->width = va_arg(*argc, int);
    (*format)++;
  } else {
    while (**format >= '0' && **format <= '9') {
      (*params)->width = (*params)->width * 10 + (int)(**format - '0');
      (*format)++;
    }
  }
}

static void s21_parse_flags(const char **format, format_params **params) {
  while (**format == ' ' || **format == '+' || **format == '-' ||
         **format == '#' || **format == '0') {
    switch (**format) {
      case ' ':
        (*params)->flags |= s21_FLAG_SPACE;
        break;
      case '+':
        (*params)->flags |= s21_FLAG_PLUS;
        break;
      case '-':
        (*params)->flags |= s21_FLAG_MINUS;
        break;
      case '0':
        (*params)->flags |= s21_FLAG_ZERO;
        break;
      case '#':
        (*params)->flags |= s21_FLAG_HASH;
        break;
      default:
        break;
    }
    (*format)++;
  }
}

static format_params *s21_parse_format(const char **format, va_list *argc) {
  format_params *params = malloc(sizeof(format_params));
  params->flags = 0;
  params->width = 0;
  params->precision = -1;
  params->length = 0;
  s21_parse_flags(format, &params);
  s21_parse_width(format, &params, argc);
  s21_parse_precision(format, &params, argc);
  s21_parse_length(format, &params);
  s21_parse_spec(format, &params);
  return params;
}

static void s21_safe_padding(buf_state *buf, const char c, const int count) {
  for (int i = 0; i < count; i++) {
    if (!s21_put_single_char(buf, c)) break;
  }
}

static int s21_handle_special_f(long double num, char **str, int upper) {
  int result = 0;
  if (isnan(num)) {
    s21_strncpy(*str, upper ? "NAN\0" : "nan\0", 4);
    result = 1;
  } else if (isinf(num)) {
    if (num < 0)
      s21_strncpy(*str, upper ? "-INF\0" : "-inf\0", 5);
    else
      s21_strncpy(*str, upper ? "INF\0" : "inf\0", 4);
    result = 2;
  }
  return result;
}
static char *s21_itoa(long long num, int size, unsigned short base,
                      unsigned short precision) {
  if (size <= 0) return s21_NULL;
  char *buf = malloc(size + 1);
  if (!buf) return s21_NULL;
  int i = 0;
  unsigned long long n;
  if (num < 0 && base == 10) {
    n = (unsigned long long)(-num);
  } else {
    n = (unsigned long long)num;
  }
  do {
    if (i >= size) break;
    int digit = n % base;
    buf[i++] = (digit < 10) ? '0' + digit : 'a' + (digit - 10);
    n /= base;
  } while (n > 0);
  while (i < precision && i < size) {
    buf[i++] = '0';
  }
  buf[i < size ? i : size - 1] = '\0';
  s21_reverse(buf, i);
  return buf;
}

static char *s21_ftoa(long double num, int size, unsigned short base,
                      unsigned short precision) {
  if (size <= 0) return s21_NULL;
  char *buf = malloc(size + 1);
  if (!buf) return s21_NULL;
  int spec = s21_handle_special_f(num, &buf, 0);
  if (spec) return buf;
  int i = 0;
  if (num < 0.0 && base == 10) {
    num = -num;
  }
  long long int_part = (long long)num;
  long double frac_part = num - (long double)int_part;
  char *int_str = s21_itoa(int_part, size, base, 0);
  if (int_str) {
    for (int j = 0; int_str[j] != '\0' && i < size; j++) {
      buf[i++] = int_str[j];
    }
    free(int_str);
    if (precision > 0 && i < size) {
      buf[i++] = '.';
      unsigned short p = 0;
      while (p < precision && i < size) {
        frac_part *= 10.0L;
        int digit = (int)frac_part;
        buf[i++] = '0' + digit;
        frac_part -= digit;
        p++;
      }

      int idx = i - 1;
      int carry = (frac_part >= 0.5L) ? 1 : 0;
      while (idx >= 0 && carry) {
        if (buf[idx] == '.') {
          idx--;
          continue;
        }
        if (buf[idx] < '9') {
          buf[idx] += carry;
          carry = 0;
        } else {
          buf[idx] = '0';
          idx--;
        }
      }
      if (carry && i < size) {
        for (int shift = i; shift > 0; shift--) buf[shift] = buf[shift - 1];
        buf[0] = '1';
        i++;
      }
    }
    buf[i < size ? i : size - 1] = '\0';
  } else {
    free(buf);
    buf = s21_NULL;
  }
  return buf;
}

static char *s21_etoa(long double num, int size, unsigned short base,
                      unsigned short precision, int apper) {
  if (size <= 0) return s21_NULL;
  char *buf = malloc(size + 16);
  if (!buf) return s21_NULL;

  int exponent = 0;
  int negative = (num < 0);
  if (negative) num = -num;

  if (num != 0.0) {
    while (num >= 10.0) {
      num /= 10.0;
      exponent++;
    }
    while (num < 1.0) {
      num *= 10.0;
      exponent--;
    }
  }
  char *mantissa = s21_ftoa(num, size, base, precision);
  if (mantissa) {
    int pos = 0;
    for (; mantissa[pos] != '\0'; pos++) {
      buf[pos] = mantissa[pos];
    }
    if (apper)
      buf[pos++] = 'E';
    else
      buf[pos++] = 'e';
    buf[pos++] = (exponent >= 0) ? '+' : '-';
    if (exponent < 0) exponent = -exponent;
    buf[pos++] = '0' + (exponent / 10) % 10;
    buf[pos++] = '0' + exponent % 10;
    buf[pos] = '\0';
    free(mantissa);
  } else {
    free(buf);
    buf = s21_NULL;
  }

  return buf;
}

static void s21_handle_string(buf_state *buf, format_params *params,
                              va_list *argc) {
  char *str = va_arg(*argc, char *);
  if (!str) str = "(null)";
  int len = s21_strlen(str);
  if (params->precision >= 0 && len > params->precision)
    len = params->precision;
  int padding = params->width - len;
  if (padding < 0) padding = 0;

  if (!(params->flags & s21_FLAG_MINUS) && padding > 0) {
    s21_safe_padding(buf, ' ', padding);
  }
  for (int i = 0; i < len && str[i]; i++) {
    s21_put_single_char(buf, str[i]);
  }

  if ((params->flags & s21_FLAG_MINUS) && padding > 0) {
    s21_safe_padding(buf, ' ', padding);
  }
}
static void s21_handle_float(buf_state *buf, format_params *params,
                             va_list *argc, int base, int apper, int exp_stat) {
  long double num = 0.0;
  switch (params->length) {
    case sizeof(double):
      num = (long double)va_arg(*argc, double);
      break;
    case sizeof(long double):
      num = (long double)va_arg(*argc, long double);
      break;
    default:
      num = (long double)va_arg(*argc, double);
      break;
  }
  int buf_size = params->precision > 0 ? params->precision + params->length + 64
                                       : params->length + 64;
  unsigned short precision = params->precision > 0 ? params->precision : 6;
  if (params->precision < 0) params->precision = 6;
  char *buffer;
  if (exp_stat == 0)
    buffer = s21_ftoa(num, buf_size, base, precision);
  else
    buffer = s21_etoa(num, buf_size + 16, base, precision, apper);
  if (buffer) {
    char sign_char = 0;
    if (num < 0.0) {
      sign_char = '-';
    } else if (params->flags & s21_FLAG_PLUS) {
      sign_char = '+';
    } else if (params->flags & s21_FLAG_SPACE) {
      sign_char = ' ';
    }
    char pad_char = ' ';
    if ((params->flags & s21_FLAG_ZERO) && !(params->flags & s21_FLAG_MINUS) &&
        params->precision < 0) {
      pad_char = '0';
    }
    int len = s21_strlen(buffer);
    int total_len = len + (sign_char ? 1 : 0);

    if ((params->flags & s21_FLAG_ZERO) && !(params->flags & s21_FLAG_MINUS) &&
        params->width > total_len) {
      if (sign_char) s21_put_single_char(buf, sign_char);
      s21_safe_padding(buf, pad_char, params->width - total_len);
    } else {
      if (!(params->flags & s21_FLAG_MINUS) && params->width > total_len) {
        s21_safe_padding(buf, pad_char, params->width - total_len);
      }
      if (sign_char) s21_put_single_char(buf, sign_char);
    }

    s21_put_string(buf, buffer);

    if ((params->flags & s21_FLAG_MINUS) && params->width > total_len) {
      s21_safe_padding(buf, ' ', params->width - total_len);
    }
    free(buffer);
  }
}

static void s21_handle_unsigned(buf_state *buf, format_params *params,
                                va_list *argc, int base) {
  unsigned long long num;
  switch (params->length) {
    case sizeof(short):
      num = (unsigned short)va_arg(*argc, unsigned int);
      break;
    case sizeof(long):
      num = va_arg(*argc, unsigned long);
      break;
    default:
      num = va_arg(*argc, unsigned int);
      break;
  }
  int buf_size = params->precision > 0 ? params->precision + params->length + 64
                                       : params->length + 64;
  unsigned short precision = params->precision > 0 ? params->precision : 0;
  char *buffer = s21_itoa(num, buf_size, base, precision);
  if (buffer) {
    char pad_char = ' ';
    if ((params->flags & s21_FLAG_ZERO) && !(params->flags & s21_FLAG_MINUS) &&
        params->precision < 0) {
      pad_char = '0';
    }
    int len = s21_strlen(buffer);
    if (!(params->flags & s21_FLAG_MINUS) && params->width > len) {
      s21_safe_padding(buf, pad_char, params->width - len);
    }
    s21_put_string(buf, buffer);
    if ((params->flags & s21_FLAG_MINUS) && params->width > len) {
      s21_safe_padding(buf, ' ', params->width - len);
    }
    free(buffer);
  }
}

static void s21_handle_int(buf_state *buf, format_params *params, va_list *argc,
                           int base, int apper) {
  long long num;
  switch (params->length) {
    case sizeof(short):
      num = (short)va_arg(*argc, int);
      break;
    case sizeof(long):
      num = va_arg(*argc, long);
      break;
    default:
      num = va_arg(*argc, int);
      break;
  }

  int buf_size = params->precision > 0 ? params->precision + params->length + 64
                                       : params->length + 64;
  unsigned short precision = params->precision > 0 ? params->precision : 0;
  char *buffer = s21_itoa(num, buf_size, base, precision);

  if (buffer) {
    char sign_char = 0;
    if (num < 0) {
      sign_char = '-';
    } else if (params->flags & s21_FLAG_PLUS) {
      sign_char = '+';
    } else if (params->flags & s21_FLAG_SPACE) {
      sign_char = ' ';
    }

    if (apper) {
      for (int i = 0; buffer[i]; i++) {
        if (buffer[i] >= 'a' && buffer[i] <= 'f') {
          buffer[i] = buffer[i] - 'a' + 'A';
        }
      }
    }

    char pad_char = ' ';
    if ((params->flags & s21_FLAG_ZERO) && !(params->flags & s21_FLAG_MINUS) &&
        params->precision < 0) {
      pad_char = '0';
    }

    int len = s21_strlen(buffer);
    int total_len = len + (sign_char ? 1 : 0);

    if (sign_char) s21_put_single_char(buf, sign_char);

    if (!(params->flags & s21_FLAG_MINUS) && params->width > total_len) {
      s21_safe_padding(buf, pad_char, params->width - total_len);
    }

    s21_put_string(buf, buffer);

    if ((params->flags & s21_FLAG_MINUS) && params->width > total_len) {
      s21_safe_padding(buf, ' ', params->width - total_len);
    }

    free(buffer);
  }
}

static void s21_handle_general(buf_state *buf, format_params *params,
                               va_list *argc, int base, int apper) {
  va_list copy;
  va_copy(copy, *argc);
  long double num = va_arg(copy, long double);
  if (fabsl(num) >= 1e-4 && fabsl(num) <= 1e6) {
    s21_handle_float(buf, params, argc, base, apper, 0);
  } else {
    s21_handle_float(buf, params, argc, base, 0, 1);
  }
  va_end(copy);
}

static void s21_handle_pointer(buf_state *buf, format_params *params,
                               va_list *argc) {
  void *ptr = va_arg(*argc, void *);
  unsigned long long addr = (unsigned long long)ptr;

  int buf_size = params->precision > 0 ? params->precision + 32 : 32;
  char *buffer = s21_itoa((long long)addr, buf_size, 16, 0);
  if (buffer) {
    s21_put_string(buf, "0x");
    s21_put_string(buf, buffer);
    free(buffer);
  }
}

static void s21_handle_char(buf_state *buf, format_params *params,
                            va_list *argc) {
  char c = (char)va_arg(*argc, int);
  int width = params->width > 1 ? params->width - 1 : 0;
  if (width > 0) {
    if (!(params->flags & s21_FLAG_MINUS)) s21_safe_padding(buf, ' ', width);
    s21_put_single_char(buf, c);
    if (params->flags & s21_FLAG_MINUS) s21_safe_padding(buf, ' ', width);
  } else
    s21_put_single_char(buf, c);
}

static void s21_specs_processor(buf_state *buf, const char **format,
                                va_list *argc) {
  (*format)++;
  format_params *params = s21_parse_format(format, argc);
  switch (params->spec) {
    case s21_SPEC_CHAR:
      s21_handle_char(buf, params, argc);
      break;
    case s21_SPEC_STRING:
      s21_handle_string(buf, params, argc);
      break;
    case s21_SPEC_DEC_INT:
      s21_handle_int(buf, params, argc, 10, 0);
      break;
    case s21_SPEC_INT:
      s21_handle_int(buf, params, argc, 10, 0);
      break;
    case s21_SPEC_EXP_LOW:
      s21_handle_float(buf, params, argc, 10, 0, 1);
      break;
    case s21_SPEC_EXP_UP:
      s21_handle_float(buf, params, argc, 10, 1, 1);
      break;
    case s21_SPEC_FLOAT:
      s21_handle_float(buf, params, argc, 10, 0, 0);
      break;
    case s21_SPEC_GENERAL_LOW:
      s21_handle_general(buf, params, argc, 10, 0);
      break;
    case s21_SPEC_GENERAL_UP:
      s21_handle_general(buf, params, argc, 10, 1);
      break;
    case s21_SPEC_OCTAL:
      s21_handle_int(buf, params, argc, 8, 0);
      break;
    case s21_SPEC_UNSIGNED:
      s21_handle_unsigned(buf, params, argc, 10);
      break;
    case 'x':
      s21_handle_int(buf, params, argc, 16, 0);
      break;
    case 'X':
      s21_handle_int(buf, params, argc, 16, 1);
      break;
    case s21_SPEC_POINTER:
      s21_handle_pointer(buf, params, argc);
      break;
    case s21_SPEC_PERCENT:
      s21_put_single_char(buf, '%');
      break;
    default:
      break;
  }
  free(params);
}

int s21_sprintf(char *str, const char *format, ...) {
  if (!str || !format) return -1;
  va_list argc;
  va_start(argc, format);
  buf_state buf = {str, str, str + 4096};
  while (*format) {
    if (*format == '%') {
      s21_specs_processor(&buf, &format, &argc);
    } else {
      s21_put_single_char(&buf, *format);
      format++;
    }
  }
  if (buf.current < buf.end) {
    *buf.current = '\0';
  } else if (buf.current > buf.begin) {
    *(buf.current - 1) = '\0';
  }
  va_end(argc);

  return (s21_size_t)(buf.current - buf.begin);
}