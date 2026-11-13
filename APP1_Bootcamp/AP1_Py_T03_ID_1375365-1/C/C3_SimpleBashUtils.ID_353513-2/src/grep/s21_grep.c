#include "s21_grep.h"

int main(int argc, char *argv[]) {
  grep_flags flags = {0};

  parse_flags(argc, argv, &flags);

  if (flags.pattern_count == 0 && flags.file_count > 0) {
    add_pattern(&flags, flags.files[0]);
    for (int i = 1; i < flags.file_count; i++) {
      strcpy(flags.files[i - 1], flags.files[i]);
    }
    flags.file_count--;
  }

  process_files(&flags);

  return 0;
}

void parse_flags(int argc, char *argv[], grep_flags *flags) {
  int opt;

  while ((opt = getopt(argc, argv, "e:ivcln")) != -1) {
    switch (opt) {
      case 'e':
        flags->e = 1;
        add_pattern(flags, optarg);
        break;
      case 'i':
        flags->i = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'c':
        flags->c = 1;
        break;
      case 'l':
        flags->l = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      default:
        continue;
    }
  }

  for (int i = optind; i < argc; i++) {
    if (flags->file_count < MAX_FILES) {
      add_file(flags, argv[i]);
    } else {
      printf("grep: Too many files. Maximum is %d\n", MAX_FILES);
    }
  }
}

void add_pattern(grep_flags *flags, const char *pattern) {
  strncpy(flags->patterns[flags->pattern_count], pattern, MAX_LINE_LENGTH - 1);
  flags->patterns[flags->pattern_count][MAX_LINE_LENGTH - 1] = '\0';
  flags->pattern_count++;
}

void add_file(grep_flags *flags, const char *filename) {
  strncpy(flags->files[flags->file_count], filename, MAX_LINE_LENGTH - 1);
  flags->files[flags->file_count][MAX_LINE_LENGTH - 1] = '\0';
  flags->file_count++;
}

void process_files(grep_flags *flags) {
  for (int i = 0; i < flags->file_count; i++) {
    FILE *file = fopen(flags->files[i], "r");
    if (file == NULL) {
      printf("grep: %s: No such file or directory\n", flags->files[i]);
      continue;
    }

    grep_file(file, flags->files[i], flags);
    fclose(file);
  }
}

void grep_file(FILE *file, const char *filename, grep_flags *flags) {
  char line[MAX_LINE_LENGTH];
  int line_number = 0;
  int match_count = 0;
  int multiple_files = flags->file_count > 1;
  int file_printed = 0;

  regex_t regexes[MAX_PATTERNS];
  int cflags = REG_EXTENDED;
  if (flags->i) cflags |= REG_ICASE;

  for (int i = 0; i < flags->pattern_count; i++) {
    if (regcomp(&regexes[i], flags->patterns[i], cflags) != 0) {
      printf("grep: %s: Invalid regular expression: %s\n", filename,
             flags->patterns[i]);
      continue;
    }
  }

  while (fgets(line, sizeof(line), file) != NULL) {
    line_number++;
    int match_found = 0;

    for (int i = 0; i < flags->pattern_count; i++) {
      if (regexec(&regexes[i], line, 0, NULL, 0) == 0) {
        match_found = 1;
        break;
      }
    }

    if (flags->v) match_found = !match_found;

    if (match_found) {
      match_count++;

      if (flags->l) {
        file_printed = 1;
        continue;
      }

      if (!flags->c) {
        if (multiple_files) printf("%s:", filename);
        if (flags->n) printf("%d:", line_number);
        printf("%s", line);
        if (line[strlen(line) - 1] != '\n') printf("\n");
      }
    }
  }

  if (flags->l && file_printed) {
    printf("%s\n", filename);
  }

  if (flags->c) {
    if (multiple_files && !flags->l) printf("%s:", filename);
    printf("%d\n", match_count);
  }

  for (int i = 0; i < flags->pattern_count; i++) {
    regfree(&regexes[i]);
  }
}
