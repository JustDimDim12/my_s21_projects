#include "s21_string.h"

#include <stdio.h>

int s21_strlen(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int s21_strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}

char *s21_strcpy(char *des, const char *str) {
    char *or_des = des;
    while ((*des++ = *str++) != '\0');
    return or_des;
}

char *s21_strcat(char *des, const char *str) {
    char *or_des = des;
    while (*des) des++;
    while ((*des++ = *str++) != '\0');
    return or_des;
}

char *s21_strchr(const char *str, int c) {
    while (*str != '\0') {
        if (*str == (char)c) {
            return (char *)str;
        }
        str++;
    }
    return (*str == (char)c) ? (char *)str : NULL;
}

char *s21_strstr(const char *hays, const char *need) {
    if (*need == '\0') {
        return (char *)hays;
    }

    for (; *hays != '\0'; hays++) {
        const char *h = hays;
        const char *n = need;

        while (*h && *n && (*h == *n)) {
            h++;
            n++;
        }

        if (*n == '\0') {
            return (char *)hays;
        }
    }

    return NULL;
}

char *s21_strtok(char *str, const char *del) {
    static char *s21_strtok_save = NULL;
    char *token = NULL;

    if (str != NULL) {
        s21_strtok_save = str;
    }

    if (s21_strtok_save == NULL || *s21_strtok_save == '\0') {
        return NULL;
    }

    while (*s21_strtok_save != '\0' && s21_strchr(del, *s21_strtok_save) != NULL) {
        s21_strtok_save++;
    }

    if (*s21_strtok_save == '\0') {
        s21_strtok_save = NULL;
        return NULL;
    }

    token = s21_strtok_save;

    while (*s21_strtok_save != '\0' && s21_strchr(del, *s21_strtok_save) == NULL) {
        s21_strtok_save++;
    }

    if (*s21_strtok_save != '\0') {
        *s21_strtok_save = '\0';
        s21_strtok_save++;
    } else {
        s21_strtok_save = NULL;
    }

    return token;
}