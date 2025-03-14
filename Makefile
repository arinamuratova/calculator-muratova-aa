# Компиляторы
CC = gcc
CXX = g++

# Флаги компиляции
CFLAGS = -Wall -Wextra -g
CXXFLAGS = -Wall -Wextra -g
LDFLAGS = -lm  # Линкуем math.h

# Пути
SRC_DIR = src
TEST_DIR = tests/unit
BUILD_DIR = build
INTEGRATION_TEST_DIR = tests/integration

# Исходники
SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/calculator.c
TEST_FILES = $(TEST_DIR)/test_calculator.cpp
INTEGRATION_TEST_FILES = $(INTEGRATION_TEST_DIR)/test_calculator.py

# Исполняемые файлы
APP_EXE = $(BUILD_DIR)/app.exe
UNIT_TEST_EXE = $(BUILD_DIR)/unit-tests.exe
INTEGRATION_TEST_EXE = $(BUILD_DIR)/integration-tests

# Флаги для GoogleTest
GTEST_LIBS = -lgtest -lgtest_main -lpthread

# Правило по умолчанию — собираем всё
all: $(APP_EXE) $(UNIT_TEST_EXE)

# Сборка основного приложения
$(APP_EXE): $(SRC_FILES)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(SRC_DIR) $(SRC_FILES) -o $(APP_EXE) $(LDFLAGS)

# Сборка юнит-тестов
$(UNIT_TEST_EXE): $(SRC_DIR)/calculator.c $(TEST_FILES)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) $(TEST_FILES) $(SRC_DIR)/calculator.c -o $(UNIT_TEST_EXE) $(GTEST_LIBS)
# Сборка интеграционных тестов
$(INTEGRATION_TEST_EXE): $(SRC_FILES)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(SRC_DIR) $(SRC_FILES) -o $(INTEGRATION_TEST_EXE) $(LDFLAGS)
 
# Запуск юнит-тестов
run-unit-test: $(UNIT_TEST_EXE)
	./$(UNIT_TEST_EXE)

# Запуск приложения в режиме целых чисел
run-int: $(APP_EXE)
	./$(APP_EXE)

# Запуск приложения в режиме float
run-float: $(APP_EXE)
	./$(APP_EXE) --float

# Запуск интеграционных тестов
run-integration-tests: $(INTEGRATION_TEST_EXE)
	python3 $(INTEGRATION_TEST_FILES)

# Очистка всех собранных файлов
clean:
	rm -rf $(BUILD_DIR)/*
