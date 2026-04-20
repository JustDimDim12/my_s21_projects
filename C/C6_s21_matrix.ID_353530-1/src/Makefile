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
MAKDIR = $(TESTDIR)/making
ARITHDIR = $(TESTDIR)/arithmetic
CHNGDIR = $(TESTDIR)/changing
MISCDIR = $(TESTDIR)/other
HELPDIR = $(TESTDIR)/helpers

# Объектные директории
MAKOBJDIR = $(MAKDIR)/obj
ARITHOBJDIR = $(ARITHDIR)/obj
CHNGOBJDIR = $(CHNGDIR)/obj
MISCOBJDIR = $(MISCDIR)/obj
HELPOBJDIR = $(HELPDIR)/obj

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))

# Источники тестов
MAKSRC = $(wildcard $(MAKDIR)/*.c)
ARITHSRC = $(wildcard $(ARITHDIR)/*.c)
CHNGSRC = $(wildcard $(CHNGDIR)/*.c)
MISCSRC = $(wildcard $(MISCDIR)/*.c)
HELPSRC = $(wildcard $(HELPDIR)/*.c)

# Объектники тестов
MAKOBJ = $(patsubst $(MAKDIR)/%.c, $(MAKOBJDIR)/%.o, $(MAKSRC))
ARITHOBJ = $(patsubst $(ARITHDIR)/%.c, $(ARITHOBJDIR)/%.o, $(ARITHSRC))
CHNGOBJ = $(patsubst $(CHNGDIR)/%.c, $(CHNGOBJDIR)/%.o, $(CHNGSRC))
MISCOBJ = $(patsubst $(MISCDIR)/%.c, $(MISCOBJDIR)/%.o, $(MISCSRC))
HELPOBJ = $(patsubst $(HELPDIR)/%.c, $(HELPOBJDIR)/%.o, $(HELPSRC))

TARGET = s21_matrix.a

# Бинарники тестов
MAK_TEST_BIN = $(BINDIR)/making_tests_run
ARITH_TEST_BIN = $(BINDIR)/arithmetic_tests_run
CHNG_TEST_BIN = $(BINDIR)/changing_tests_run
MISC_TEST_BIN = $(BINDIR)/other_tests_run
HELP_TEST_BIN = $(BINDIR)/helpers_tests_run

# Бинарники тестов с sanitizers
MAK_TEST_BIN_SANITIZE = $(BINDIR)/making_tests_sanitize
ARITH_TEST_BIN_SANITIZE = $(BINDIR)/arithmetic_tests_sanitize
CHNG_TEST_BIN_SANITIZE = $(BINDIR)/changing_tests_sanitize
MISC_TEST_BIN_SANITIZE = $(BINDIR)/other_tests_sanitize
HELP_TEST_BIN_SANITIZE = $(BINDIR)/helpers_tests_sanitize

# --- Основные цели ---

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BINDIR)
	@ar rcs $@ $^

$(OBJDIR) $(MAKOBJDIR) $(ARITHOBJDIR) $(CHNGOBJDIR) $(MISCOBJDIR) $(HELPOBJDIR) $(BINDIR) $(GCOVDIR) $(REPORTDIR):
	@mkdir -p $@

# --- Правила компиляции ---
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(MAKOBJDIR)/%.o: $(MAKDIR)/%.c | $(MAKOBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ARITHOBJDIR)/%.o: $(ARITHDIR)/%.c | $(ARITHOBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(CHNGOBJDIR)/%.o: $(CHNGDIR)/%.c | $(CHNGOBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(MISCOBJDIR)/%.o: $(MISCDIR)/%.c | $(MISCOBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(HELPOBJDIR)/%.o: $(HELPDIR)/%.c | $(HELPOBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@


# --- Тестовые цели ---

making_test: $(TARGET) $(MAKOBJ) $(OBJ) | $(BINDIR)
	@echo "🔧 Компиляция тестов making..."
	$(CC) $(CFLAGS) $(MAKOBJ) $(OBJ) -o $(MAK_TEST_BIN) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🚀 Запуск тестов making..."
	@chmod +x $(MAK_TEST_BIN)
	./$(MAK_TEST_BIN) > $(MAKDIR)/making_test_results.txt 2>&1
	@echo "✅ Результаты making → $(MAKDIR)/making_test_results.txt"

arithmetic_test: $(TARGET) $(ARITHOBJ) $(OBJ) | $(BINDIR)
	@echo "🔧 Компиляция тестов arithmetic..."
	$(CC) $(CFLAGS) $(ARITHOBJ) $(OBJ) -o $(ARITH_TEST_BIN) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🚀 Запуск тестов arithmetic..."
	@chmod +x $(ARITH_TEST_BIN)
	./$(ARITH_TEST_BIN) > $(ARITHDIR)/arithmetic_test_results.txt 2>&1
	@echo "✅ Результаты arithmetic → $(ARITHDIR)/arithmetic_test_results.txt"

changing_test: $(TARGET) $(CHNGOBJ) $(OBJ) | $(BINDIR)
	@echo "🔧 Компиляция тестов changing..."
	$(CC) $(CFLAGS) $(CHNGOBJ) $(OBJ) -o $(CHNG_TEST_BIN) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🚀 Запуск тестов changing..."
	@chmod +x $(CHNG_TEST_BIN)
	./$(CHNG_TEST_BIN) > $(CHNGDIR)/changing_test_results.txt 2>&1
	@echo "✅ Результаты changing → $(CHNGDIR)/changing_test_results.txt"

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
test: making_test arithmetic_test changing_test other_test helpers_test
	@echo "🧩 Объединение результатов..."
	@cat \
		$(MAKDIR)/making_test_results.txt \
		$(ARITHDIR)/arithmetic_test_results.txt \
		$(CHNGDIR)/changing_test_results.txt \
		$(MISCDIR)/other_test_results.txt \
		$(HELPDIR)/helpers_test_results.txt \
		> $(TESTDIR)/test_results.txt
	@echo "📄 Все результаты → $(TESTDIR)/test_results.txt"

# --- VALGRIND ПРОВЕРКИ ---

valgrind_making: $(TARGET) $(MAKOBJ) $(OBJ) | $(BINDIR)
	@echo "🧠 Компиляция making тестов для valgrind..."
	$(CC) $(CFLAGS) -g $(MAKOBJ) $(OBJ) -o $(MAK_TEST_BIN) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🔍 Запуск valgrind для making..."
	@valgrind --tool=memcheck --leak-check=yes --track-origins=yes --log-file=$(MAKDIR)/valgrind_making.txt ./$(MAK_TEST_BIN) >/dev/null 2>&1 || true
	@echo "📊 Valgrind отчет → $(MAKDIR)/valgrind_making.txt"

valgrind_arithmetic: $(TARGET) $(ARITHOBJ) $(OBJ) | $(BINDIR)
	@echo "🧠 Компиляция arithmetic тестов для valgrind..."
	$(CC) $(CFLAGS) -g $(ARITHOBJ) $(OBJ) -o $(ARITH_TEST_BIN) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🔍 Запуск valgrind для arithmetic..."
	@valgrind --tool=memcheck --leak-check=yes --track-origins=yes --log-file=$(ARITHDIR)/valgrind_arithmetic.txt ./$(ARITH_TEST_BIN) >/dev/null 2>&1 || true
	@echo "📊 Valgrind отчет → $(ARITHDIR)/valgrind_arithmetic.txt"

valgrind_changing: $(TARGET) $(CHNGOBJ) $(OBJ) | $(BINDIR)
	@echo "🧠 Компиляция changing тестов для valgrind..."
	$(CC) $(CFLAGS) -g $(CHNGOBJ) $(OBJ) -o $(CHNG_TEST_BIN) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🔍 Запуск valgrind для changing..."
	@valgrind --tool=memcheck --leak-check=yes --track-origins=yes --log-file=$(CHNGDIR)/valgrind_changing.txt ./$(CHNG_TEST_BIN) >/dev/null 2>&1 || true
	@echo "📊 Valgrind отчет → $(CHNGDIR)/valgrind_changing.txt"

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
valgrind: valgrind_making valgrind_arithmetic valgrind_changing valgrind_other valgrind_helpers
	@echo "🧩 Объединение valgrind отчетов..."
	@echo "=== VALGRIND REPORTS SUMMARY ===" > $(TESTDIR)/valgrind_summary.txt
	@echo -e "\n=== Making ===" >> $(TESTDIR)/valgrind_summary.txt
	@tail -n 10 $(MAKDIR)/valgrind_making.txt >> $(TESTDIR)/valgrind_summary.txt 2>/dev/null || echo "No convert valgrind report" >> $(TESTDIR)/valgrind_summary.txt
	@echo "=== Arithmetic ===" >> $(TESTDIR)/valgrind_summary.txt
	@tail -n 10 $(ARITHDIR)/valgrind_arithmetic.txt >> $(TESTDIR)/valgrind_summary.txt 2>/dev/null || echo "No arithmetic valgrind report" >> $(TESTDIR)/valgrind_summary.txt
	@echo -e "\n=== Changing ===" >> $(TESTDIR)/valgrind_summary.txt
	@tail -n 10 $(CHNGDIR)/valgrind_changing.txt >> $(TESTDIR)/valgrind_summary.txt 2>/dev/null || echo "No comparison valgrind report" >> $(TESTDIR)/valgrind_summary.txt
	@echo -e "\n=== Other ===" >> $(TESTDIR)/valgrind_summary.txt
	@tail -n 10 $(MISCDIR)/valgrind_other.txt >> $(TESTDIR)/valgrind_summary.txt 2>/dev/null || echo "No other valgrind report" >> $(TESTDIR)/valgrind_summary.txt
	@echo "📄 Valgrind summary → $(TESTDIR)/valgrind_summary.txt"
	@tail -n 10 $(HELPDIR)/valgrind_helpers.txt >> $(TESTDIR)/valgrind_summary.txt 2>/dev/null || echo "No helpers valgrind report" >> $(TESTDIR)/valgrind_summary.txt
	@echo "📄 Valgrind summary → $(TESTDIR)/valgrind_summary.txt"

# --- SANITIZERS ПРОВЕРКИ ---

sanitize_making: $(TARGET) $(MAKOBJ) $(OBJ) | $(BINDIR)
	@echo "🛡️  Компиляция making тестов с sanitizers..."
	$(CC) $(CFLAGS) $(SANITIZE_FLAGS) $(MAKOBJ) $(OBJ) -o $(MAK_TEST_BIN_SANITIZE) $(SANITIZE_LDFLAGS) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🔍 Запуск making тестов с sanitizers..."
	@ASAN_OPTIONS=detect_leaks=1 ./$(MAK_TEST_BIN_SANITIZE) > $(MAKDIR)/sanitize_making.txt 2>&1; \
	EXIT_CODE=$$?; \
	if [ $$EXIT_CODE -ne 0 ]; then \
		echo "❌ Sanitizer обнаружил проблемы в making!"; \
		echo "=== SANITIZER ERRORS ===" > $(MAKDIR)/sanitize_making_errors.txt; \
		./$(MAK_TEST_BIN_SANITIZE) 2>> $(MAKDIR)/sanitize_making_errors.txt || true; \
	fi; \
	echo "📊 Sanitize отчет → $(MAKDIR)/sanitize_making.txt"

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

sanitize_changing: $(TARGET) $(CHNGOBJ) $(OBJ) | $(BINDIR)
	@echo "🛡️  Компиляция changing тестов с sanitizers..."
	$(CC) $(CFLAGS) $(SANITIZE_FLAGS) $(CHNGOBJ) $(OBJ) -o $(CHNG_TEST_BIN_SANITIZE) $(SANITIZE_LDFLAGS) -lcheck -lm -lpthread -lrt -lsubunit
	@echo "🔍 Запуск comparison тестов с sanitizers..."
	@ASAN_OPTIONS=detect_leaks=1 ./$(CHNG_TEST_BIN_SANITIZE) > $(CHNGDIR)/sanitize_changing.txt 2>&1; \
	EXIT_CODE=$$?; \
	if [ $$EXIT_CODE -ne 0 ]; then \
		echo "❌ Sanitizer обнаружил проблемы в changing!"; \
		echo "=== SANITIZER ERRORS ===" > $(CHNGDIR)/sanitize_changing_errors.txt; \
		./$(CHNG_TEST_BIN_SANITIZE) 2>> $(CHNGDIR)/sanitize_changing_errors.txt || true; \
	fi; \
	echo "📊 Sanitize отчет → $(CHNGDIR)/sanitize_changing.txt"

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
sanitize: sanitize_making sanitize_arithmetic sanitize_changing sanitize_other sanitize_helpers
	@echo "🧩 Анализ sanitize отчетов..."
	@echo "=== SANITIZERS REPORTS SUMMARY ===" > $(TESTDIR)/sanitize_summary.txt
	@echo "Проверка на наличие ошибок sanitizer..." >> $(TESTDIR)/sanitize_summary.txt
	@ERROR_FOUND=0; \
	for category in making arithmetic changing other; do \
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

	$(MAKE) -s gcov_build_making
	$(MAKE) -s gcov_build_arithmetic
	$(MAKE) -s gcov_build_changing
	$(MAKE) -s gcov_build_other
	$(MAKE) -s gcov_build_helpers

	cd $(GCOVDIR) && ./making_cov >/dev/null 2>&1 || true
	cd $(GCOVDIR) && ./arithmetic_cov >/dev/null 2>&1 || true
	cd $(GCOVDIR) && ./changing_cov >/dev/null 2>&1 || true
	cd $(GCOVDIR) && ./other_cov >/dev/null 2>&1 || true
	cd $(GCOVDIR) && ./helpers_cov >/dev/null 2>&1 || true

	cd $(GCOVDIR) && lcov -t "s21_matrix" -o s21_matrix.info -c -d .
	cd $(GCOVDIR) && genhtml -o report s21_matrix.info

	@cp -r $(GCOVDIR)/report/* $(REPORTDIR)/
	@echo "📊 Отчёт создан: $(REPORTDIR)/index.html"
	@xdg-open $(REPORTDIR)/index.html 2>/dev/null || true

gcov_build_making:
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage $(SRC) $(MAKSRC) -o $(GCOVDIR)/making_cov -lcheck -lm -lpthread -lrt -lsubunit

gcov_build_arithmetic:
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage $(SRC) $(ARITHSRC) -o $(GCOVDIR)/arithmetic_cov -lcheck -lm -lpthread -lrt -lsubunit

gcov_build_changing:
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage $(SRC) $(CHNGSRC) -o $(GCOVDIR)/changing_cov -lcheck -lm -lpthread -lrt -lsubunit

gcov_build_other:
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage $(SRC) $(MISCSRC) -o $(GCOVDIR)/other_cov -lcheck -lm -lpthread -lrt -lsubunit

gcov_build_helpers:
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage $(SRC) $(HELPSRC) -o $(GCOVDIR)/helpers_cov -lcheck -lm -lpthread -lrt -lsubunit

# --- Форматирование и очистка ---
clang_format:
	clang-format -i *.c $(MAKDIR)/*.c $(ARITHDIR)/*.c $(CHNGDIR)/*.c $(MISCDIR)/*.c $(HELPDIR)/*.c *.h

clang_check:
	clang-format -n *.c $(MAKDIR)/*.c $(ARITHDIR)/*.c $(CHNGDIR)/*.c $(MISCDIR)/*.c $(HELPDIR)/*.c *.h

clean:
	rm -rf $(OBJDIR) $(MAKOBJDIR) $(ARITHOBJDIR) $(CHNGOBJDIR) $(MISCOBJDIR) $(HELPOBJDIR) $(BINDIR) $(GCOVDIR) $(REPORTDIR) *.a \
		$(MAKDIR)/*_test_results.txt $(ARITHDIR)/*_test_results.txt $(CHNGDIR)/*_test_results.txt $(MISCDIR)/*_test_results.txt $(HELPDIR)/*_test_results.txt \
		$(TESTDIR)/test_results.txt $(TESTDIR)/valgrind_summary.txt $(TESTDIR)/sanitize_summary.txt \
		$(MAKDIR)/valgrind_*.txt $(ARITHDIR)/valgrind_*.txt $(CHNGDIR)/valgrind_*.txt $(MISCDIR)/valgrind_*.txt $(HELPDIR)/valgrind_*.txt \
		$(MAKDIR)/sanitize_*.txt $(ARITHDIR)/sanitize_*.txt $(CHNGDIR)/sanitize_*.txt $(MISCDIR)/sanitize_*.txt $(HELPDIR)/sanitize_*.txt

rebuild: clean all

.PHONY: all test clean rebuild clang_format clang_check \
        making_test arithmetic_test changing_test other_test helpers_test \
        valgrind valgrind_making valgrind_arithmetic valgrind_changing valgrind_other valgrind_helpers \
        sanitize sanitize_making sanitize_arithmetic sanitize_chnaging sanitize_other sanitize_helpers \
        full_check gcov_report
