all: build

build: s21_cat s21_grep

s21_cat_clang: cat/s21_cat.c
	clang-format -i cat/s21_cat.c
	clang-format -n cat/s21_cat.c

s21_cat: cat/s21_cat.c
	gcc -Wall -Werror -Wextra -std=gnu11 cat/s21_cat.c -o cat/s21_cat -lm

s21_cat_make: s21_cat_clang s21_cat

s21_grep_clang: grep/s21_grep.c
	clang-format -i grep/s21_grep.c
	clang-format -n grep/s21_grep.c
	clang-format -i grep/s21_grep.h
	clang-format -n grep/s21_grep.h

s21_grep: grep/s21_grep.c
	gcc -Wall -Werror -Wextra -std=gnu11 grep/s21_grep.c -o grep/s21_grep -lm

s21_grep_make: s21_grep_clang s21_grep

clean_cat:
	rm -rf cat/s21_cat

clean_grep:
	rm -rf grep/s21_grep

clean: clean_cat clean_grep

rebuild: clean all
