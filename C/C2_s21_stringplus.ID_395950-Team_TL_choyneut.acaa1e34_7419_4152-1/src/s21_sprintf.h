#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

#define s21_FLAG_MINUS 1
#define s21_FLAG_PLUS 2
#define s21_FLAG_SPACE 4
#define s21_FLAG_ZERO 8
#define s21_FLAG_HASH 16

#define s21_LEN_HH 1
#define s21_LEN_H 2
#define s21_LEN_L 3
#define s21_LEN_LL 4
#define s21_LEN_LF 5
#define s21_LEN_J 6
#define s21_LEN_Z 7
#define s21_LEN_T 8

#define s21_SPEC_CHAR 'c'
#define s21_SPEC_STRING 's'
#define s21_SPEC_POINTER 'p'
#define s21_SPEC_DEC_INT 'd'
#define s21_SPEC_INT 'i'
#define s21_SPEC_UNSIGNED 'u'
#define s21_SPEC_OCTAL 'o'
#define s21_SPEC_HEX_LOW 'x'
#define s21_SPEC_HEX_UP 'X'
#define s21_SPEC_FLOAT 'f'
#define s21_SPEC_EXP_LOW 'e'
#define s21_SPEC_EXP_UP 'E'
#define s21_SPEC_GENERAL_LOW 'g'
#define s21_SPEC_GENERAL_UP 'G'
#define s21_SPEC_PERCENT '%'
#define s21_SPEC_LEN 'n'

typedef struct {
  char *current;
  char *begin;
  char *end;
} buf_state;

typedef struct {
  int flags;
  int width;
  int precision;
  int length;
  int spec;
} format_params;

static void s21_reverse(char *str, int len);
static int s21_put_single_char(buf_state *buf, char c);
static int s21_put_string(buf_state *buf, char *str);
static void s21_parse_spec(const char **format, format_params **params);
static void s21_parse_length(const char **format, format_params **params);
static void s21_parse_precision(const char **format, format_params **params,
                                va_list *argc);
static void s21_parse_width(const char **format, format_params **params,
                            va_list *argc);
static void s21_parse_flags(const char **format, format_params **params);
static format_params *s21_parse_format(const char **format, va_list *argc);
static void s21_safe_padding(buf_state *buf, const char c, const int count);
static int s21_handle_special_f(long double num, char **str, int upper);
static char *s21_ftoa(long double num, int size, unsigned short base,
                      unsigned short precision);
static char *s21_itoa(long long num, int size, unsigned short base,
                      unsigned short precision);
static char *s21_etoa(long double num, int size, unsigned short base,
                      unsigned short precision, int apper);
static void s21_handle_float(buf_state *buf, format_params *params,
                             va_list *argc, int base, int apper, int exp_stat);
static void s21_handle_unsigned(buf_state *buf, format_params *params,
                                va_list *argc, int base);
static void s21_handle_int(buf_state *buf, format_params *params, va_list *argc,
                           int base, int apper);
static void s21_handle_general(buf_state *buf, format_params *params,
                               va_list *argc, int base, int apper);
static void s21_handle_char(buf_state *buf, format_params *params,
                            va_list *argc);
static void s21_specs_processor(buf_state *buf, const char **format,
                                va_list *argc);
int s21_sprintf(char *str, const char *format, ...);