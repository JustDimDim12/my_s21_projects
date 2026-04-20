all: build build_with_macro build_with_static build_with_dynamic

build: main_executable_module.o sorting.o data_io.o data_stat.o data_process.o decision.o
	gcc -Wall -Wextra -Werror -std=c11 main_executable_module.o sorting.o data_io.o data_stat.o data_process.o decision.o -o ../../build/Quest_3 -lm

build_with_macro: main_executable_module_macro.o sorting.o data_stat.o data_process.o decision.o
	gcc -Wall -Wextra -Werror -std=c11 main_executable_module_macro.o sorting.o data_stat.o data_process.o decision.o -o ../../build/Quest_4 -lm

build_with_static: main_executable_module.o sorting.o data_io.o data_process.o decision.o data_stat.a
	gcc -Wall -Wextra -Werror -std=c11 main_executable_module.o sorting.o data_io.o data_process.o decision.o data_stat.a -o ../../build/Quest_5 -lm

build_with_dynamic: main_executable_module.o sorting.o data_io.o decision.o data_process.so
	gcc -Wall -Wextra -Werror -std=c11 main_executable_module.o sorting.o data_io.o decision.o data_process.so -o ../../build/Quest_6 -lm -Wl,-rpath,'$$ORIGIN'

data_process.so: data_process_dynamic.o data_stat.a
	gcc -shared data_process_dynamic.o data_stat.a -o data_process.so
	gcc -shared data_process_dynamic.o data_stat.a -o ../../build/data_process.so
	rm -f data_process_dynamic.o data_process.o

data_stat.a: data_stat.o
	ar rcs data_stat.a data_stat.o
	rm -f data_stat.o

main_executable_module.o: main_executable_module.c
	gcc -Wall -Wextra -Werror -std=c11 -c main_executable_module.c

main_executable_module_macro.o: main_executable_module.c
	gcc -Wall -Wextra -Werror -std=c11 -DUSE_IO_MACRO=1 -c main_executable_module.c -o main_executable_module_macro.o

sorting.o: sorting.c
	gcc -Wall -Wextra -Werror -std=c11 -c sorting.c

data_io.o: ../data_libs/data_io.c
	gcc -Wall -Wextra -Werror -std=c11 -c ../data_libs/data_io.c

data_stat.o: ../data_libs/data_stat.c
	gcc -Wall -Wextra -Werror -std=c11 -c ../data_libs/data_stat.c

data_process.o: ../data_module/data_process.c 
	gcc -Wall -Wextra -Werror -std=c11 -c ../data_module/data_process.c

data_process_dynamic.o: ../data_module/data_process.c
	gcc -Wall -Wextra -Werror -std=c11 -DDYNAMIC_LIBRARY -c ../data_module/data_process.c -o data_process_dynamic.o

decision.o: ../yet_another_decision_module/decision.c
	gcc -Wall -Wextra -Werror -std=c11 -c ../yet_another_decision_module/decision.c

clean_o:
	rm -rf *.o *.a *.so ../../build/*.so

clean_q:
	rm -rf ../../build/*Quest_*

clean_3:
	rm -rf ../../build/Quest_3

clean_4:
	rm -rf ../../build/Quest_4

clean_5:
	rm -rf ../../build/Quest_5

clean_6:
	rm -rf ../../build/Quest_6

clean:
	rm -rf *.o *.a *.so ../../build/*.so ../../build/*Quest_*

rebuild: clean all