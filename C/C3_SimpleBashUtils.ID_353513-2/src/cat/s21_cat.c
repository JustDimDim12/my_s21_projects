#include <stdio.h>
#include <string.h>

void bflag(char *name, int *error);
void eflag(char *name, int *error);
void evflag(char *name, int *error);
void nflag(char *name, int *error);
void sflag(char *name, int *error);
void tflag(char *name, int *error);
void tvflag(char *name, int *error);

void file_check(FILE *file, int *error) {
  if (file == NULL) {
    *error = 1;
    return;
  }
}

void no_flag(char *name, int *error) {
  FILE *file = fopen(name, "rt");

  file_check(file, error);
  if (*error == 1) {
    printf("cat: %s: No such file or directory\n", name);
    *error = 0;
    return;
  }

  int c = fgetc(file);
  while (c != EOF) {
    putc(c, stdout);
    c = fgetc(file);
  }
  fclose(file);
}

void check_flag(int argc, char **argv, int *error) {
  if (strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "--number-nonblank") == 0) {
    for (int i = 2; i < argc; i++) bflag(argv[i], error);
  } else if (strcmp(argv[1], "-e") == 0) {
    for (int i = 2; i < argc; i++) evflag(argv[i], error);
  } else if (strcmp(argv[1], "-E") == 0) {
    for (int i = 2; i < argc; i++) eflag(argv[i], error);
  } else if (strcmp(argv[1], "-n") == 0 || strcmp(argv[1], "--number") == 0) {
    for (int i = 2; i < argc; i++) nflag(argv[i], error);
  } else if (strcmp(argv[1], "-s") == 0 ||
             strcmp(argv[1], "--squeeze-blank") == 0) {
    for (int i = 2; i < argc; i++) sflag(argv[i], error);
  } else if (strcmp(argv[1], "-T") == 0) {
    for (int i = 2; i < argc; i++) tvflag(argv[i], error);
  } else if (strcmp(argv[1], "-t") == 0) {
    for (int i = 2; i < argc; i++) tflag(argv[i], error);
  } else {
    printf("cat: Wrong flag\n");
  }
}

int main(int argc, char **argv) {
  int error = 0;

  if (argc == 1) {
    printf("cat: Empty input\n");
    return 0;
  }

  if (argv[1][0] == '-') {
    check_flag(argc, argv, &error);
  } else {
    for (int i = 1; i < argc; i++) {
      no_flag(argv[i], &error);
    }
  }

  return 0;
}

void bflag(char *name, int *error) {
  FILE *file = fopen(name, "rt");
  file_check(file, error);
  if (*error == 1) {
    printf("cat: %s: No such file or directory\n", name);
    *error = 0;
    return;
  }
  int count = 1;
  int c;
  int temp = '\n';
  while ((c = fgetc(file)) != EOF) {
    if (temp == '\n' && c != '\n') {
      printf("%6d\t", count++);
    }
    putc(c, stdout);
    temp = c;
  }
  fclose(file);
}

void eflag(char *name, int *error) {
  FILE *file = fopen(name, "rt");
  file_check(file, error);
  if (*error == 1) {
    printf("cat: %s: No such file or directory\n", name);
    *error = 0;
    return;
  }

  int c;
  while ((c = fgetc(file)) != EOF) {
    if (c == '\n') {
      putc('$', stdout);
    }
    putc(c, stdout);
  }
  fclose(file);
}

void evflag(char *name, int *error) {
  FILE *file = fopen(name, "rt");
  file_check(file, error);
  if (*error == 1) {
    printf("cat: %s: No such file or directory\n", name);
    *error = 0;
    return;
  }

  int c;
  while ((c = fgetc(file)) != EOF) {
    if (c < 32 && c != 9 && c != 10) {
      printf("^%c", c + 64);
    } else if (c == 127) {
      printf("^?");
    } else if (c > 127 && c < 160) {
      printf("M-^%c", c - 64);
    } else if (c >= 160) {
      printf("M-%c", c - 128);
    } else {
      if (c == '\n') {
        printf("$\n");
      } else {
        putc(c, stdout);
      }
    }
  }
  fclose(file);
}

void nflag(char *name, int *error) {
  FILE *file = fopen(name, "rt");
  file_check(file, error);
  if (*error == 1) {
    printf("cat: %s: No such file or directory\n", name);
    *error = 0;
    return;
  }

  int count = 1;
  int c;
  int temp = '\n';
  while ((c = fgetc(file)) != EOF) {
    if (temp == '\n') {
      printf("%6d\t", count++);
    }
    putc(c, stdout);
    temp = c;
  }
  fclose(file);
}

void sflag(char *name, int *error) {
  FILE *file = fopen(name, "rt");
  file_check(file, error);
  if (*error == 1) {
    printf("cat: %s: No such file or directory\n", name);
    return;
  }

  int c, temp = ' ', count = 0;
  while ((c = fgetc(file)) != EOF) {
    if (c == '\n' && temp == '\n' && count == 0)
      count = 1;
    else if (c == '\n' && temp == '\n' && count == 1)
      continue;
    else if (c != '\n' && temp == '\n' && count == 1)
      count = 0;
    putc(c, stdout);
    temp = c;
  }
  fclose(file);
}

void tflag(char *name, int *error) {
  FILE *file = fopen(name, "rt");
  file_check(file, error);
  if (*error == 1) {
    printf("cat: %s: No such file or directory\n", name);
    return;
  }

  int c;
  while ((c = fgetc(file)) != EOF) {
    if (c == '\t')
      printf("^I");
    else
      putc(c, stdout);
  }
  fclose(file);
}

void tvflag(char *name, int *error) {
  FILE *file = fopen(name, "rt");
  file_check(file, error);
  if (*error == 1) {
    printf("cat: %s: No such file or directory\n", name);
    return;
  }

  int c;
  while ((c = fgetc(file)) != EOF) {
    if (c < 32 && c != 9 && c != 10) {
      printf("^%c", c + 64);
    } else if (c == 127) {
      printf("^?");
    } else if (c > 127 && c < 160) {
      printf("M-^%c", c - 64);
    } else if (c >= 160) {
      printf("M-%c", c - 128);
    } else {
      if (c == '\t') {
        printf("^I");
      } else {
        putc(c, stdout);
      }
    }
  }
  fclose(file);
}
