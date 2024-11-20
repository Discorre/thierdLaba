# Имя основного исполняемого файла
TARGET = benchmark_main

# Компилятор и флаги компиляции с покрытием
CXX = g++
CXXFLAGS = -std=c++17 -g -O0 -fprofile-arcs -ftest-coverage

# Источники и заголовочные файлы
SRC = benchmark.cpp  # Замените на ваш файл с main
HEADERS = MyListKV.hpp MyArray.hpp
OBJ = $(SRC:.cpp=.o)

# Директория для отчетов о покрытии
COVERAGE_DIR = coverage_report

# Цель по умолчанию
all: $(TARGET)

# Сборка основного исполняемого файла
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) -L/usr/local/lib -lbenchmark -lpthread

# Компиляция файлов объекта
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Запуск тестов и генерация отчета о покрытии
coverage: clean $(TARGET)
	# Запуск бенчмарка для сбора данных покрытия
	./$(TARGET)

	# Создание директории для покрытия, если она не существует
	mkdir -p $(COVERAGE_DIR)

	# Сбор покрытия с использованием lcov
	lcov --capture --directory . --output-file $(COVERAGE_DIR)/coverage.info

	# Фильтрация системных файлов и библиотек
	lcov --remove $(COVERAGE_DIR)/coverage.info '/usr/*' --output-file $(COVERAGE_DIR)/coverage_filtered.info

	# Генерация пофайловых HTML-отчетов
	genhtml $(COVERAGE_DIR)/coverage_filtered.info --output-directory $(COVERAGE_DIR) --demangle-cpp --show-details

	@echo "HTML-отчет о покрытии создан в $(COVERAGE_DIR)/thierdLaba/index.html"

# Очистка скомпилированных файлов и отчетов о покрытии
clean:
	rm -f $(TARGET) *.o *.gcda *.gcno
	rm -rf $(COVERAGE_DIR)
