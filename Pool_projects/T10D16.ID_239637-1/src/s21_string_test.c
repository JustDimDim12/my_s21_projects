#include "s21_string.h"

#include <stdio.h>

void s21_strlen_test() {
    int res = s21_strlen("Hello, world!");
    printf("%s\n", "Hello, world!");
    printf("%d\n", 13);
    printf("%d\n", res);
    if (res == 13) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    printf("\n\n");

    res = s21_strlen("");
    printf("%s\n", "");
    printf("%d\n", 0);
    printf("%d\n", res);
    if (res == 0) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    printf("\n\n");
    res = s21_strlen("A");
    printf("%s\n", "A");
    printf("%d\n", 1);
    printf("%d\n", res);
    if (res == 1) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
}

void s21_strcmp_test() {
    int res = s21_strcmp("abc", "abc");
    printf("%s | %s\n", "abc", "abc");
    printf("%d\n", 0);
    printf("%d\n", res);
    if (res == 0) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    printf("\n\n");
    res = s21_strcmp("a", "");
    printf("%s | %s\n", "a", "");
    printf("%d\n", 'a');
    printf("%d\n", res);
    if (res == 'a') {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    printf("\n\n");
    res = s21_strcmp("long string a", "long string b");
    printf("%s | %s\n", "long string a", "long string b");
    printf("%d\n", -1);
    printf("%d\n", res);
    if (res == -1) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
}

void s21_strcpy_test() {
    char res[256] = {0};
    s21_strcpy(res, "Hello, world!");
    printf("%s\n", "Hello, world!");
    printf("%s\n", "Hello, world!");
    printf("%s\n", res);
    if (s21_strcmp(res, "Hello, world!") == 0) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    printf("\n\n");

    char res2[256] = {0};
    s21_strcpy(res2, "");
    printf("%s\n", "");
    printf("%s\n", "");
    printf("%s\n", res2);
    if (s21_strcmp(res2, "") == 0) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    printf("\n\n");
    char res3[256] = {0};
    s21_strcpy(res3, "A");
    printf("%s\n", "A");
    printf("%s\n", "A");
    printf("%s\n", res3);
    if (s21_strcmp(res3, "A") == 0) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
}

void s21_strcat_test() {
    char des[256] = {0};
    s21_strcpy(des, "Hello");
    s21_strcat(des, " world");
    printf("%s + %s\n", "Hello", " world");
    printf("%s\n", "Hello world");
    printf("%s\n", des);
    if (s21_strcmp(des, "Hello world") == 0) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    printf("\n\n");
    char des2[256] = {0};
    s21_strcpy(des2, "");
    s21_strcat(des2, "empty");
    printf("%s + %s\n", "", "empty");
    printf("%s\n", "empty");
    printf("%s\n", des2);
    if (s21_strcmp(des2, "empty") == 0) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    printf("\n\n");
    char des3[256] = {0};
    s21_strcpy(des3, "Long string");
    s21_strcat(des3, " with сertification");
    printf("%s + %s\n", "Long string", " with сertification");
    printf("%s\n", "Long string with сertification");
    printf("%s\n", des3);
    if (s21_strcmp(des3, "Long string with сertification") == 0) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
}

void s21_strchr_test() {
    const char *str = "Hello world";
    const char *exp = "world";
    char *res = s21_strchr(str, 'w');
    printf("%s | %c\n", str, 'w');
    printf("%p (%s)\n", (void *)exp, exp);
    printf("%p (%s)\n", (void *)res, res);
    if (res != NULL && *res == 'w') {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    printf("\n\n");

    res = s21_strchr("Hello", 'x');
    printf("%s | %c\n", "Hello", 'x');
    printf("%p (%p)\n", (void *)NULL, NULL);
    printf("%p (%s)\n", (void *)res, res);
    if (res == NULL) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    printf("\n\n");

    str = "Hello world";
    exp = "world";
    res = s21_strchr("Last char", 'r');
    printf("%s | %c\n", "Last char", 'r');
    printf("%p (%s)\n", (void *)exp, exp);
    printf("%p (%s)\n", (void *)res, res);
    if (res != NULL && *res == 'r') {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
}

void s21_strstr_test() {
    char *res = s21_strstr("Test string", "st s");
    printf("%s | %s\n", "Test string", "st s");
    printf("%s\n", "st string");
    printf("%s\n", res);
    if (res != NULL && s21_strcmp(res, "st string") == 0) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    printf("\n\n");

    res = s21_strstr("Hello", "xyz");
    printf("%s | %s\n", "Hello", "xyz");
    printf("%p\n", (void *)NULL);
    printf("%p\n", (void *)res);
    if (res == NULL) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    printf("\n\n");

    res = s21_strstr("Multiple word word", "word word");
    printf("%s | %s\n", "Multiple word word", "word word");
    printf("%s\n", "word word");
    printf("%s\n", res);
    if (res != NULL && s21_strcmp(res, "word word") == 0) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
}

void s21_strtok_test() {
    const char *exp1[] = {"Hello", "world", "test"};
    printf("%s | %s\n", "Hello,world,test", ",");
    for (int i = 0; i < 3; i++) {
        printf("[%d] %s\n", i, exp1[i]);
    }
    printf("\n");
    char copy1[256] = {0};
    s21_strcpy(copy1, "Hello,world,test");
    char *token = s21_strtok(copy1, ",");
    int success = 1;
    int i = 0;

    while (token != NULL && i < 3) {
        printf("[%d] %s\n", i, token);
        if (s21_strcmp(token, exp1[i]) != 0) {
            success = 0;
        }
        token = s21_strtok(NULL, ",");
        i++;
    }

    if (token != NULL || i != 3) {
        success = 0;
        while (token != NULL) {
            printf("[%d] %s\n", i, token);
            token = s21_strtok(NULL, ",");
            i++;
        }
    }

    if (success) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    printf("\n\n");

    const char *exp2[] = {"only", "one", "token"};
    printf("%s | %s\n", ",,,only,,one,token,", ",");
    for (int i = 0; i < 3; i++) {
        printf("[%d] %s\n", i, exp2[i]);
    }
    printf("\n");
    char copy2[256] = {0};
    s21_strcpy(copy2, ",,,only,,one,token,");
    token = s21_strtok(copy2, ",");
    success = 1;
    i = 0;

    while (token != NULL && i < 3) {
        printf("[%d] %s\n", i, token);
        if (s21_strcmp(token, exp2[i]) != 0) {
            success = 0;
        }
        token = s21_strtok(NULL, ",");
        i++;
    }

    if (token != NULL || i != 3) {
        success = 0;
        while (token != NULL) {
            printf("[%d] %s\n", i, token);
            token = s21_strtok(NULL, ",");
            i++;
        }
    }

    if (success) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    printf("\n\n");

    const char *exp3[] = {NULL};
    printf("%s | %s\n", "", ",");
    for (int i = 0; i < 0; i++) {
        printf("[%d] %s\n", i, exp3[i]);
    }
    printf("\n");
    char copy3[256] = {0};
    s21_strcpy(copy3, "");
    token = s21_strtok(copy3, ",");
    success = 1;
    i = 0;

    while (token != NULL && i < 0) {
        printf("[%d] %s\n", i, token);
        if (s21_strcmp(token, exp3[i]) != 0) {
            success = 0;
        }
        token = s21_strtok(NULL, ",");
        i++;
    }

    if (token != NULL || i != 0) {
        success = 0;
        while (token != NULL) {
            printf("[%d] %s\n", i, token);
            token = s21_strtok(NULL, ",");
            i++;
        }
    }

    if (success) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
}

int main(void) {
#ifdef TEST_STRLEN
    s21_strlen_test();
#endif

#ifdef TEST_STRCMP
    s21_strcmp_test();
#endif

#ifdef TEST_STRCPY
    s21_strcpy_test();
#endif

#ifdef TEST_STRCAT
    s21_strcat_test();
#endif

#ifdef TEST_STRCHR
    s21_strchr_test();
#endif

#ifdef TEST_STRSTR
    s21_strstr_test();
#endif

#ifdef TEST_STRTOK
    s21_strtok_test();
#endif

    return 0;
}