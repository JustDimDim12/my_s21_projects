all: door_struct list_test stack_test

door_struct: dmanager_module.c
	gcc -Wall -Werror -Wextra -std=c11 dmanager_module.c -o ../build/Quest_1 -lm

list_test: list_test.c list.c
	gcc -Wall -Werror -Wextra -std=c11 list_test.c list.c -o ../build/Quest_2 -lm

stack_test: stack_test.c stack.c
	gcc -Wall -Werror -Wextra -std=c11 stack_test.c stack.c -o ../build/Quest_3 -lm

clean_1:
	rm -rf ../build/Quest_1

clean_2:
	rm -rf ../build/Quest_2

clean_3:
	rm -rf ../build/Quest_3

clean:
	rm -rf ../build/*Quest_*

rebuild: clean all