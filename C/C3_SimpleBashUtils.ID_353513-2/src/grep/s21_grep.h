#ifndef S21_GREP_H
#define S21_GREP_H

#define MAX_FILES 20
#define MAX_PATTERNS 100
#define MAX_LINE_LENGTH 4096

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int pattern_count;
  char patterns[MAX_PATTERNS][MAX_LINE_LENGTH];
  int file_count;
  char files[MAX_FILES][MAX_LINE_LENGTH];
} grep_flags;

void parse_flags(int argc, char *argv[], grep_flags *flags);
void add_pattern(grep_flags *flags, const char *pattern);
void add_file(grep_flags *flags, const char *filename);
void process_files(grep_flags *flags);
void grep_file(FILE *file, const char *filename, grep_flags *flags);

#endif
