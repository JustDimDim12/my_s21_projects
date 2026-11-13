CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=gnu11 -Iinclude

OBJDIR = obj
BINDIR = bin
GCOVDIR = gcov
REPORTDIR = report

STRTESTDIR = tests/string
SPRTTESTDIR = tests/sprintf
CSHTESTDIR = tests/sharp

STROBJDIR = $(STRTESTDIR)/obj
SPROBJDIR = $(SPRTTESTDIR)/obj
CSHOBJDIR = $(CSHTESTDIR)/obj

SRC = $(wildcard *.c)
STRTSRC = $(wildcard $(STRTESTDIR)/*.c)
SPRTSRC = $(wildcard $(SPRTTESTDIR)/*.c)
CSHTSRC = $(wildcard $(CSHTESTDIR)/*.c)

OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))
STROBJ = $(patsubst $(STRTESTDIR)/%.c, $(STROBJDIR)/%.o, $(STRTSRC))
SPROBJ = $(patsubst $(SPRTTESTDIR)/%.c, $(SPROBJDIR)/%.o, $(SPRTSRC))
CSHOBJ = $(patsubst $(CSHTESTDIR)/%.c, $(CSHOBJDIR)/%.o, $(CSHTSRC))

TARGET = s21_string.a
STRING_TEST_BIN = $(BINDIR)/string_tests_run
SPRINTF_TEST_BIN = $(BINDIR)/sprintf_tests_run
CSHARP_TEST_BIN = $(BINDIR)/csharp_tests_run

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BINDIR)
	@ar rcs $@ $^

$(OBJDIR) $(STROBJDIR) $(SPROBJDIR) $(CSHOBJDIR) $(BINDIR) $(GCOVDIR) $(REPORTDIR):
	@mkdir -p $@

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(STROBJDIR)/%.o: $(STRTESTDIR)/%.c | $(STROBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(SPROBJDIR)/%.o: $(SPRTTESTDIR)/%.c | $(SPROBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(CSHOBJDIR)/%.o: $(CSHTESTDIR)/%.c | $(CSHOBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

string_test: $(TARGET) $(STROBJ) | $(BINDIR)
	@echo "🔧 Компиляция тестов string..."
	$(CC) $(CFLAGS) $(STROBJ) $(OBJ) -o $(STRING_TEST_BIN) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🚀 Запуск тестов string..."
	@chmod +x $(STRING_TEST_BIN)
	./$(STRING_TEST_BIN) > tests/string_test_results.txt 2>&1
	@echo "✅ Результаты string → tests/string_test_results.txt"

sprintf_test: $(TARGET) $(SPROBJ) | $(BINDIR)
	@echo "🔧 Компиляция тестов sprintf..."
	$(CC) $(CFLAGS) $(SPROBJ) $(OBJ) -o $(SPRINTF_TEST_BIN) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🚀 Запуск тестов sprintf..."
	@chmod +x $(SPRINTF_TEST_BIN)
	./$(SPRINTF_TEST_BIN) > tests/sprintf_test_results.txt 2>&1
	@echo "✅ Результаты sprintf → tests/sprintf_test_results.txt"

csharp_test: $(TARGET) $(CSHOBJ) | $(BINDIR)
	@echo "🔧 Компиляция тестов csharp..."
	$(CC) $(CFLAGS) $(CSHOBJ) $(OBJ) -o $(CSHARP_TEST_BIN) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🚀 Запуск тестов csharp..."
	@chmod +x $(CSHARP_TEST_BIN)
	./$(CSHARP_TEST_BIN) > tests/csharp_test_results.txt 2>&1
	@echo "✅ Результаты csharp → tests/csharp_test_results.txt"

test: string_test sprintf_test csharp_test
	@echo "🧩 Объединение результатов..."
	@cat tests/string_test_results.txt tests/sprintf_test_results.txt tests/csharp_test_results.txt > tests/test_results.txt
	@echo "📄 Все результаты → tests/test_results.txt"

gcov_report: clean | $(GCOVDIR) $(REPORTDIR)
	@echo "🔍 Создание coverage-версий и запуск тестов для сбора покрытия..."

	$(MAKE) -s gcov_build_string
	$(MAKE) -s gcov_build_sprintf
	$(MAKE) -s gcov_build_csharp

	cd $(GCOVDIR) && ./string_cov >/dev/null 2>&1 || true
	cd $(GCOVDIR) && ./sprintf_cov >/dev/null 2>&1 || true
	cd $(GCOVDIR) && ./csharp_cov >/dev/null 2>&1 || true

	cd $(GCOVDIR) && lcov -t "s21_string" -o s21_string.info -c -d .
	cd $(GCOVDIR) && genhtml -o report s21_string.info

	@cp -r $(GCOVDIR)/report/* $(REPORTDIR)/
	@echo "📊 Отчёт создан: $(REPORTDIR)/index.html"
	@xdg-open $(REPORTDIR)/index.html 2>/dev/null || true

gcov_build_string:
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage $(SRC) $(STRTSRC) -o $(GCOVDIR)/string_cov -lcheck -lm -lpthread -lrt -lsubunit

gcov_build_sprintf:
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage $(SRC) $(SPRTSRC) -o $(GCOVDIR)/sprintf_cov -lcheck -lm -lpthread -lrt -lsubunit

gcov_build_csharp:
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage $(SRC) $(CSHTSRC) -o $(GCOVDIR)/csharp_cov -lcheck -lm -lpthread -lrt -lsubunit

clang_all:
	clang-format -i *.c $(STRTESTDIR)/*.c $(SPRTTESTDIR)/*.c $(CSHTESTDIR)/*.c *.h
	clang-format -n *.c $(STRTESTDIR)/*.c $(SPRTTESTDIR)/*.c $(CSHTESTDIR)/*.c *.h

clean:
	rm -rf $(OBJDIR) $(STROBJDIR) $(SPROBJDIR) $(CSHOBJDIR) $(BINDIR) $(GCOVDIR) $(REPORTDIR) *.a \
	tests/*_test_results.txt tests/test_results.txt

rebuild: clean all