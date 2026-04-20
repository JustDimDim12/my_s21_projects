all: strlen_tests strcmp_tests strcpy_tests strcat_tests strchr_tests strstr_tests strtok_tests

strlen_tests: s21_string_test.c s21_string.c
	gcc -Wall -Werror -Wextra -std=c11 -D TEST_STRLEN s21_string_test.c s21_string.c -o ../build/Quest_1 -lm

strcmp_tests: s21_string_test.c s21_string.c
	gcc -Wall -Werror -Wextra -std=c11 -D TEST_STRCMP s21_string_test.c s21_string.c -o ../build/Quest_2 -lm

strcpy_tests: s21_string_test.c s21_string.c
	gcc -Wall -Werror -Wextra -std=c11 -D TEST_STRCPY s21_string_test.c s21_string.c -o ../build/Quest_3 -lm

strcat_tests: s21_string_test.c s21_string.c
	gcc -Wall -Werror -Wextra -std=c11 -D TEST_STRCAT s21_string_test.c s21_string.c -o ../build/Quest_4 -lm

strchr_tests: s21_string_test.c s21_string.c
	gcc -Wall -Werror -Wextra -std=c11 -D TEST_STRCHR s21_string_test.c s21_string.c -o ../build/Quest_5 -lm

strstr_tests: s21_string_test.c s21_string.c
	gcc -Wall -Werror -Wextra -std=c11 -D TEST_STRSTR s21_string_test.c s21_string.c -o ../build/Quest_6 -lm

strtok_tests: s21_string_test.c s21_string.c
	gcc -Wall -Werror -Wextra -std=c11 -D TEST_STRTOK s21_string_test.c s21_string.c -o ../build/Quest_7 -lm

clean_1:
	rm -rf ../build/Quest_1

clean_2:
	rm -rf ../build/Quest_2

clean_3:
	rm -rf ../build/Quest_3

clean_4:
	rm -rf ../build/Quest_4

clean_5:
	rm -rf ../build/Quest_5

clean_6:
	rm -rf ../build/Quest_6

clean_7:
	rm -rf ../build/Quest_7

clean:
	rm -rf ../build/*Quest_*

rebuild: clean all