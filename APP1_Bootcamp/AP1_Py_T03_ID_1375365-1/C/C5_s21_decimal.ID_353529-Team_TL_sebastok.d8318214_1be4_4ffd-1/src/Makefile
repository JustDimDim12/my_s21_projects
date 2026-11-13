CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=gnu11 -Iinclude

# Флаги для sanitizers
SANITIZE_FLAGS = -fsanitize=address -fsanitize=leak -fsanitize=undefined
SANITIZE_LDFLAGS = -fsanitize=address -fsanitize=leak -fsanitize=undefined

OBJDIR = obj
BINDIR = bin
GCOVDIR = gcov
REPORTDIR = report
TESTDIR = tests

# Поддиректории тестов
ARITHDIR = $(TESTDIR)/arithmetic
CMPDIR = $(TESTDIR)/comparison
CONVDIR = $(TESTDIR)/convert
MISCDIR = $(TESTDIR)/other
HELPDIR = $(TESTDIR)/helpers

# Объектные директории
ARITHOBJDIR = $(ARITHDIR)/obj
CMPOBJDIR = $(CMPDIR)/obj
CONVOBJDIR = $(CONVDIR)/obj
MISCODIR = $(MISCDIR)/obj
HELPDIR_OBJ = $(HELPDIR)/obj

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))

# Источники тестов
ARITHSRC = $(wildcard $(ARITHDIR)/*.c)
CMPSRC = $(wildcard $(CMPDIR)/*.c)
CONVSRC = $(wildcard $(CONVDIR)/*.c)
MISCSRC = $(wildcard $(MISCDIR)/*.c)
HELPSRC = $(wildcard $(HELPDIR)/*.c)

# Объектники тестов
ARITHOBJ = $(patsubst $(ARITHDIR)/%.c, $(ARITHOBJDIR)/%.o, $(ARITHSRC))
CMPOBJ = $(patsubst $(CMPDIR)/%.c, $(CMPOBJDIR)/%.o, $(CMPSRC))
CONVOBJ = $(patsubst $(CONVDIR)/%.c, $(CONVOBJDIR)/%.o, $(CONVSRC))
MISCOBJ = $(patsubst $(MISCDIR)/%.c, $(MISCODIR)/%.o, $(MISCSRC))
HELPOBJ = $(patsubst $(HELPDIR)/%.c, $(HELPDIR_OBJ)/%.o, $(HELPSRC))

TARGET = s21_decimal.a

# Бинарники тестов
ARITH_TEST_BIN = $(BINDIR)/arithmetic_tests_run
CMP_TEST_BIN = $(BINDIR)/comparison_tests_run
CONV_TEST_BIN = $(BINDIR)/convert_tests_run
MISC_TEST_BIN = $(BINDIR)/other_tests_run
HELP_TEST_BIN = $(BINDIR)/helpers_tests_run

# Бинарники тестов с sanitizers
ARITH_TEST_BIN_SANITIZE = $(BINDIR)/arithmetic_tests_sanitize
CMP_TEST_BIN_SANITIZE = $(BINDIR)/comparison_tests_sanitize
CONV_TEST_BIN_SANITIZE = $(BINDIR)/convert_tests_sanitize
MISC_TEST_BIN_SANITIZE = $(BINDIR)/other_tests_sanitize
HELP_TEST_BIN_SANITIZE = $(BINDIR)/helpers_tests_sanitize

# --- Основные цели ---

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BINDIR)
	@ar rcs $@ $^

$(OBJDIR) $(ARITHOBJDIR) $(CMPOBJDIR) $(CONVOBJDIR) $(MISCODIR) $(HELPDIR_OBJ) $(BINDIR) $(GCOVDIR) $(REPORTDIR):
	@mkdir -p $@

# --- Правила компиляции ---
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ARITHOBJDIR)/%.o: $(ARITHDIR)/%.c | $(ARITHOBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(CMPOBJDIR)/%.o: $(CMPDIR)/%.c | $(CMPOBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(CONVOBJDIR)/%.o: $(CONVDIR)/%.c | $(CONVOBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(MISCODIR)/%.o: $(MISCDIR)/%.c | $(MISCODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(HELPDIR_OBJ)/%.o: $(HELPDIR)/%.c | $(HELPDIR_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Тестовые цели ---

arithmetic_test: $(TARGET) $(ARITHOBJ) $(OBJ) | $(BINDIR)
	@echo "🔧 Компиляция тестов arithmetic..."
	$(CC) $(CFLAGS) $(ARITHOBJ) $(OBJ) -o $(ARITH_TEST_BIN) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🚀 Запуск тестов arithmetic..."
	@chmod +x $(ARITH_TEST_BIN)
	./$(ARITH_TEST_BIN) > $(ARITHDIR)/arithmetic_test_results.txt 2>&1
	@echo "✅ Результаты arithmetic → $(ARITHDIR)/arithmetic_test_results.txt"

comparison_test: $(TARGET) $(CMPOBJ) $(OBJ) | $(BINDIR)
	@echo "🔧 Компиляция тестов comparison..."
	$(CC) $(CFLAGS) $(CMPOBJ) $(OBJ) -o $(CMP_TEST_BIN) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🚀 Запуск тестов comparison..."
	@chmod +x $(CMP_TEST_BIN)
	./$(CMP_TEST_BIN) > $(CMPDIR)/comparison_test_results.txt 2>&1
	@echo "✅ Результаты comparison → $(CMPDIR)/comparison_test_results.txt"

convert_test: $(TARGET) $(CONVOBJ) $(OBJ) | $(BINDIR)
	@echo "🔧 Компиляция тестов convert..."
	$(CC) $(CFLAGS) $(CONVOBJ) $(OBJ) -o $(CONV_TEST_BIN) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🚀 Запуск тестов convert..."
	@chmod +x $(CONV_TEST_BIN)
	./$(CONV_TEST_BIN) > $(CONVDIR)/convert_test_results.txt 2>&1
	@echo "✅ Результаты convert → $(CONVDIR)/convert_test_results.txt"

other_test: $(TARGET) $(MISCOBJ) $(OBJ) | $(BINDIR)
	@echo "🔧 Компиляция тестов other..."
	$(CC) $(CFLAGS) $(MISCOBJ) $(OBJ) -o $(MISC_TEST_BIN) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🚀 Запуск тестов other..."
	@chmod +x $(MISC_TEST_BIN)
	./$(MISC_TEST_BIN) > $(MISCDIR)/other_test_results.txt 2>&1
	@echo "✅ Результаты other → $(MISCDIR)/other_test_results.txt"

helpers_test: $(TARGET) $(HELPOBJ) $(OBJ) | $(BINDIR)
	@echo "🔧 Компиляция тестов helpers..."
	$(CC) $(CFLAGS) $(HELPOBJ) $(OBJ) -o $(HELP_TEST_BIN) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🚀 Запуск тестов helpers..."
	@chmod +x $(HELP_TEST_BIN)
	./$(HELP_TEST_BIN) > $(HELPDIR)/helpers_test_results.txt 2>&1
	@echo "✅ Результаты helpers → $(HELPDIR)/helpers_test_results.txt"

# --- Общий запуск всех тестов ---
test: arithmetic_test comparison_test convert_test other_test helpers_test
	@echo "🧩 Объединение результатов..."
	@cat \
		$(ARITHDIR)/arithmetic_test_results.txt \
		$(CMPDIR)/comparison_test_results.txt \
		$(CONVDIR)/convert_test_results.txt \
		$(MISCDIR)/other_test_results.txt \
		$(HELPDIR)/helpers_test_results.txt \
		> $(TESTDIR)/test_results.txt
	@echo "📄 Все результаты → $(TESTDIR)/test_results.txt"

# --- VALGRIND ПРОВЕРКИ ---

valgrind_arithmetic: $(TARGET) $(ARITHOBJ) $(OBJ) | $(BINDIR)
	@echo "🧠 Компиляция arithmetic тестов для valgrind..."
	$(CC) $(CFLAGS) -g $(ARITHOBJ) $(OBJ) -o $(ARITH_TEST_BIN) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🔍 Запуск valgrind для arithmetic..."
	@valgrind --tool=memcheck --leak-check=yes --track-origins=yes --log-file=$(ARITHDIR)/valgrind_arithmetic.txt ./$(ARITH_TEST_BIN) >/dev/null 2>&1 || true
	@echo "📊 Valgrind отчет → $(ARITHDIR)/valgrind_arithmetic.txt"

valgrind_comparison: $(TARGET) $(CMPOBJ) $(OBJ) | $(BINDIR)
	@echo "🧠 Компиляция comparison тестов для valgrind..."
	$(CC) $(CFLAGS) -g $(CMPOBJ) $(OBJ) -o $(CMP_TEST_BIN) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🔍 Запуск valgrind для comparison..."
	@valgrind --tool=memcheck --leak-check=yes --track-origins=yes --log-file=$(CMPDIR)/valgrind_comparison.txt ./$(CMP_TEST_BIN) >/dev/null 2>&1 || true
	@echo "📊 Valgrind отчет → $(CMPDIR)/valgrind_comparison.txt"

valgrind_convert: $(TARGET) $(CONVOBJ) $(OBJ) | $(BINDIR)
	@echo "🧠 Компиляция convert тестов для valgrind..."
	$(CC) $(CFLAGS) -g $(CONVOBJ) $(OBJ) -o $(CONV_TEST_BIN) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🔍 Запуск valgrind для convert..."
	@valgrind --tool=memcheck --leak-check=yes --track-origins=yes --log-file=$(CONVDIR)/valgrind_convert.txt ./$(CONV_TEST_BIN) >/dev/null 2>&1 || true
	@echo "📊 Valgrind отчет → $(CONVDIR)/valgrind_convert.txt"

valgrind_other: $(TARGET) $(MISCOBJ) $(OBJ) | $(BINDIR)
	@echo "🧠 Компиляция other тестов для valgrind..."
	$(CC) $(CFLAGS) -g $(MISCOBJ) $(OBJ) -o $(MISC_TEST_BIN) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🔍 Запуск valgrind для other..."
	@valgrind --tool=memcheck --leak-check=yes --track-origins=yes --log-file=$(MISCDIR)/valgrind_other.txt ./$(MISC_TEST_BIN) >/dev/null 2>&1 || true
	@echo "📊 Valgrind отчет → $(MISCDIR)/valgrind_other.txt"

valgrind_helpers: $(TARGET) $(HELPOBJ) $(OBJ) | $(BINDIR)
	@echo "🧠 Компиляция helpers тестов для valgrind..."
	$(CC) $(CFLAGS) -g $(HELPOBJ) $(OBJ) -o $(HELP_TEST_BIN) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🔍 Запуск valgrind для helpers..."
	@valgrind --tool=memcheck --leak-check=yes --track-origins=yes --log-file=$(HELPDIR)/valgrind_helpers.txt ./$(HELP_TEST_BIN) >/dev/null 2>&1 || true
	@echo "📊 Valgrind отчет → $(HELPDIR)/valgrind_helpers.txt"

# Общая проверка valgrind для всех тестов
valgrind: valgrind_arithmetic valgrind_comparison valgrind_convert valgrind_other valgrind_helpers
	@echo "🧩 Объединение valgrind отчетов..."
	@echo "=== VALGRIND REPORTS SUMMARY ===" > $(TESTDIR)/valgrind_summary.txt
	@echo "=== Arithmetic ===" >> $(TESTDIR)/valgrind_summary.txt
	@tail -n 10 $(ARITHDIR)/valgrind_arithmetic.txt >> $(TESTDIR)/valgrind_summary.txt 2>/dev/null || echo "No arithmetic valgrind report" >> $(TESTDIR)/valgrind_summary.txt
	@echo -e "\n=== Comparison ===" >> $(TESTDIR)/valgrind_summary.txt
	@tail -n 10 $(CMPDIR)/valgrind_comparison.txt >> $(TESTDIR)/valgrind_summary.txt 2>/dev/null || echo "No comparison valgrind report" >> $(TESTDIR)/valgrind_summary.txt
	@echo -e "\n=== Convert ===" >> $(TESTDIR)/valgrind_summary.txt
	@tail -n 10 $(CONVDIR)/valgrind_convert.txt >> $(TESTDIR)/valgrind_summary.txt 2>/dev/null || echo "No convert valgrind report" >> $(TESTDIR)/valgrind_summary.txt
	@echo -e "\n=== Other ===" >> $(TESTDIR)/valgrind_summary.txt
	@tail -n 10 $(MISCDIR)/valgrind_other.txt >> $(TESTDIR)/valgrind_summary.txt 2>/dev/null || echo "No other valgrind report" >> $(TESTDIR)/valgrind_summary.txt
	@echo -e "\n=== Helpers ===" >> $(TESTDIR)/valgrind_summary.txt
	@tail -n 10 $(HELPDIR)/valgrind_helpers.txt >> $(TESTDIR)/valgrind_summary.txt 2>/dev/null || echo "No helpers valgrind report" >> $(TESTDIR)/valgrind_summary.txt
	@echo "📄 Valgrind summary → $(TESTDIR)/valgrind_summary.txt"

# --- SANITIZERS ПРОВЕРКИ ---

sanitize_arithmetic: $(TARGET) $(ARITHOBJ) $(OBJ) | $(BINDIR)
	@echo "🛡️  Компиляция arithmetic тестов с sanitizers..."
	$(CC) $(CFLAGS) $(SANITIZE_FLAGS) $(ARITHOBJ) $(OBJ) -o $(ARITH_TEST_BIN_SANITIZE) $(SANITIZE_LDFLAGS) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🔍 Запуск arithmetic тестов с sanitizers..."
	@ASAN_OPTIONS=detect_leaks=1 ./$(ARITH_TEST_BIN_SANITIZE) > $(ARITHDIR)/sanitize_arithmetic.txt 2>&1; \
	EXIT_CODE=$$?; \
	if [ $$EXIT_CODE -ne 0 ]; then \
		echo "❌ Sanitizer обнаружил проблемы в arithmetic!"; \
		echo "=== SANITIZER ERRORS ===" > $(ARITHDIR)/sanitize_arithmetic_errors.txt; \
		./$(ARITH_TEST_BIN_SANITIZE) 2>> $(ARITHDIR)/sanitize_arithmetic_errors.txt || true; \
	fi; \
	echo "📊 Sanitize отчет → $(ARITHDIR)/sanitize_arithmetic.txt"

sanitize_comparison: $(TARGET) $(CMPOBJ) $(OBJ) | $(BINDIR)
	@echo "🛡️  Компиляция comparison тестов с sanitizers..."
	$(CC) $(CFLAGS) $(SANITIZE_FLAGS) $(CMPOBJ) $(OBJ) -o $(CMP_TEST_BIN_SANITIZE) $(SANITIZE_LDFLAGS) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🔍 Запуск comparison тестов с sanitizers..."
	@ASAN_OPTIONS=detect_leaks=1 ./$(CMP_TEST_BIN_SANITIZE) > $(CMPDIR)/sanitize_comparison.txt 2>&1; \
	EXIT_CODE=$$?; \
	if [ $$EXIT_CODE -ne 0 ]; then \
		echo "❌ Sanitizer обнаружил проблемы в comparison!"; \
		echo "=== SANITIZER ERRORS ===" > $(CMPDIR)/sanitize_comparison_errors.txt; \
		./$(CMP_TEST_BIN_SANITIZE) 2>> $(CMPDIR)/sanitize_comparison_errors.txt || true; \
	fi; \
	echo "📊 Sanitize отчет → $(CMPDIR)/sanitize_comparison.txt"

sanitize_convert: $(TARGET) $(CONVOBJ) $(OBJ) | $(BINDIR)
	@echo "🛡️  Компиляция convert тестов с sanitizers..."
	$(CC) $(CFLAGS) $(SANITIZE_FLAGS) $(CONVOBJ) $(OBJ) -o $(CONV_TEST_BIN_SANITIZE) $(SANITIZE_LDFLAGS) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🔍 Запуск convert тестов с sanitizers..."
	@ASAN_OPTIONS=detect_leaks=1 ./$(CONV_TEST_BIN_SANITIZE) > $(CONVDIR)/sanitize_convert.txt 2>&1; \
	EXIT_CODE=$$?; \
	if [ $$EXIT_CODE -ne 0 ]; then \
		echo "❌ Sanitizer обнаружил проблемы в convert!"; \
		echo "=== SANITIZER ERRORS ===" > $(CONVDIR)/sanitize_convert_errors.txt; \
		./$(CONV_TEST_BIN_SANITIZE) 2>> $(CONVDIR)/sanitize_convert_errors.txt || true; \
	fi; \
	echo "📊 Sanitize отчет → $(CONVDIR)/sanitize_convert.txt"

sanitize_other: $(TARGET) $(MISCOBJ) $(OBJ) | $(BINDIR)
	@echo "🛡️  Компиляция other тестов с sanitizers..."
	$(CC) $(CFLAGS) $(SANITIZE_FLAGS) $(MISCOBJ) $(OBJ) -o $(MISC_TEST_BIN_SANITIZE) $(SANITIZE_LDFLAGS) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🔍 Запуск other тестов с sanitizers..."
	@ASAN_OPTIONS=detect_leaks=1 ./$(MISC_TEST_BIN_SANITIZE) > $(MISCDIR)/sanitize_other.txt 2>&1; \
	EXIT_CODE=$$?; \
	if [ $$EXIT_CODE -ne 0 ]; then \
		echo "❌ Sanitizer обнаружил проблемы в other!"; \
		echo "=== SANITIZER ERRORS ===" > $(MISCDIR)/sanitize_other_errors.txt; \
		./$(MISC_TEST_BIN_SANITIZE) 2>> $(MISCDIR)/sanitize_other_errors.txt || true; \
	fi; \
	echo "📊 Sanitize отчет → $(MISCDIR)/sanitize_other.txt"

sanitize_helpers: $(TARGET) $(HELPOBJ) $(OBJ) | $(BINDIR)
	@echo "🛡️  Компиляция helpers тестов с sanitizers..."
	$(CC) $(CFLAGS) $(SANITIZE_FLAGS) $(HELPOBJ) $(OBJ) -o $(HELP_TEST_BIN_SANITIZE) $(SANITIZE_LDFLAGS) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🔍 Запуск helpers тестов с sanitizers..."
	@ASAN_OPTIONS=detect_leaks=1 ./$(HELP_TEST_BIN_SANITIZE) > $(HELPDIR)/sanitize_helpers.txt 2>&1; \
	EXIT_CODE=$$?; \
	if [ $$EXIT_CODE -ne 0 ]; then \
		echo "❌ Sanitizer обнаружил проблемы в helpers!"; \
		echo "=== SANITIZER ERRORS ===" > $(HELPDIR)/sanitize_helpers_errors.txt; \
		./$(HELP_TEST_BIN_SANITIZE) 2>> $(HELPDIR)/sanitize_helpers_errors.txt || true; \
	fi; \
	echo "📊 Sanitize отчет → $(HELPDIR)/sanitize_helpers.txt"

# Общая проверка sanitizers для всех тестов
sanitize: sanitize_arithmetic sanitize_comparison sanitize_convert sanitize_other sanitize_helpers
	@echo "🧩 Анализ sanitize отчетов..."
	@echo "=== SANITIZERS REPORTS SUMMARY ===" > $(TESTDIR)/sanitize_summary.txt
	@echo "Проверка на наличие ошибок sanitizer..." >> $(TESTDIR)/sanitize_summary.txt
	@ERROR_FOUND=0; \
	for category in arithmetic comparison convert other helpers; do \
		if [ -f "$(TESTDIR)/$$category/sanitize_$${category}_errors.txt" ]; then \
			echo "❌ Ошибки в $$category:" >> $(TESTDIR)/sanitize_summary.txt; \
			cat "$(TESTDIR)/$$category/sanitize_$${category}_errors.txt" >> $(TESTDIR)/sanitize_summary.txt; \
			ERROR_FOUND=1; \
		else \
			echo "✅ $$category: ошибок не обнаружено" >> $(TESTDIR)/sanitize_summary.txt; \
		fi; \
	done; \
	if [ $$ERROR_FOUND -eq 0 ]; then \
		echo "🎉 Все sanitizer проверки пройдены успешно!" >> $(TESTDIR)/sanitize_summary.txt; \
	else \
		echo "💥 Обнаружены проблемы с памятью!" >> $(TESTDIR)/sanitize_summary.txt; \
	fi
	@echo "📄 Sanitize summary → $(TESTDIR)/sanitize_summary.txt"
	@cat $(TESTDIR)/sanitize_summary.txt

# --- ПОЛНАЯ ПРОВЕРКА (все тесты + valgrind + sanitizers) ---
full_check: test valgrind sanitize
	@echo "🎉 Полная проверка завершена!"
	@echo "📊 Результаты:"
	@echo "   • Тесты: $(TESTDIR)/test_results.txt"
	@echo "   • Valgrind: $(TESTDIR)/valgrind_summary.txt"
	@echo "   • Sanitizers: $(TESTDIR)/sanitize_summary.txt"

# --- Красивый вывод результатов тестов в html-файл ---
gcov_report: clean | $(GCOVDIR) $(REPORTDIR)
	@echo "🔍 Создание coverage-версий и запуск тестов для сбора покрытия..."

	$(MAKE) -s gcov_build_arithmetic
	$(MAKE) -s gcov_build_comparison
	$(MAKE) -s gcov_build_convert
	$(MAKE) -s gcov_build_other
	$(MAKE) -s gcov_build_helpers

	cd $(GCOVDIR) && ./arithmetic_cov >/dev/null 2>&1 || true
	cd $(GCOVDIR) && ./comparison_cov >/dev/null 2>&1 || true
	cd $(GCOVDIR) && ./convert_cov >/dev/null 2>&1 || true
	cd $(GCOVDIR) && ./other_cov >/dev/null 2>&1 || true
	cd $(GCOVDIR) && ./helpers_cov >/dev/null 2>&1 || true

	cd $(GCOVDIR) && lcov -t "s21_decimal" -o s21_decimal.info -c -d .
	cd $(GCOVDIR) && genhtml -o report s21_decimal.info

	@cp -r $(GCOVDIR)/report/* $(REPORTDIR)/
	@echo "📊 Отчёт создан: $(REPORTDIR)/index.html"
	@xdg-open $(REPORTDIR)/index.html 2>/dev/null || true

gcov_build_arithmetic:
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage $(SRC) $(ARITHSRC) -o $(GCOVDIR)/arithmetic_cov -lcheck -lm -lpthread -lrt -lsubunit

gcov_build_comparison:
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage $(SRC) $(CMPSRC) -o $(GCOVDIR)/comparison_cov -lcheck -lm -lpthread -lrt -lsubunit

gcov_build_convert:
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage $(SRC) $(CONVSRC) -o $(GCOVDIR)/convert_cov -lcheck -lm -lpthread -lrt -lsubunit

gcov_build_other:
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage $(SRC) $(MISCSRC) -o $(GCOVDIR)/other_cov -lcheck -lm -lpthread -lrt -lsubunit

gcov_build_helpers:
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage $(SRC) $(HELPSRC) -o $(GCOVDIR)/helpers_cov -lcheck -lm -lpthread -lrt -lsubunit

# --- Форматирование и очистка ---
clang_format:
	clang-format -i *.c $(ARITHDIR)/*.c $(CMPDIR)/*.c $(CONVDIR)/*.c $(MISCDIR)/*.c $(HELPDIR)/*.c *.h

clang_check:
	clang-format -n *.c $(ARITHDIR)/*.c $(CMPDIR)/*.c $(CONVDIR)/*.c $(MISCDIR)/*.c $(HELPDIR)/*.c *.h

clean:
	rm -rf $(OBJDIR) $(ARITHOBJDIR) $(CMPOBJDIR) $(CONVOBJDIR) $(MISCODIR) $(HELPDIR_OBJ) $(BINDIR) $(GCOVDIR) $(REPORTDIR) *.a \
		$(ARITHDIR)/*_test_results.txt $(CMPDIR)/*_test_results.txt \
		$(CONVDIR)/*_test_results.txt $(MISCDIR)/*_test_results.txt $(HELPDIR)/*_test_results.txt \
		$(TESTDIR)/test_results.txt $(TESTDIR)/valgrind_summary.txt $(TESTDIR)/sanitize_summary.txt \
		$(ARITHDIR)/valgrind_*.txt $(CMPDIR)/valgrind_*.txt $(CONVDIR)/valgrind_*.txt $(MISCDIR)/valgrind_*.txt $(HELPDIR)/valgrind_*.txt \
		$(ARITHDIR)/sanitize_*.txt $(CMPDIR)/sanitize_*.txt $(CONVDIR)/sanitize_*.txt $(MISCDIR)/sanitize_*.txt $(HELPDIR)/sanitize_*.txt

rebuild: clean all

.PHONY: all test clean rebuild clang_format clang_check \
        arithmetic_test comparison_test convert_test other_test helpers_test \
        valgrind valgrind_arithmetic valgrind_comparison valgrind_convert valgrind_other valgrind_helpers \
        sanitize sanitize_arithmetic sanitize_comparison sanitize_convert sanitize_other sanitize_helpers \
        full_check gcov_report