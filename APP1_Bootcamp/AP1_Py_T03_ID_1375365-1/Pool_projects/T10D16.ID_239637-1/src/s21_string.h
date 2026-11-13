#ifndef S21_STRING_H
#define S21_STRING_H

int s21_strlen(const char *str);
int s21_strcmp(const char *str1, const char *str2);
char *s21_strcpy(char *des, const char *str);
char *s21_strcat(char *des, const char *str);
char *s21_strchr(const char *str, int c);
char *s21_strstr(const char *hays, const char *need);
char *s21_strtok(char *str, const char *del);

#endif