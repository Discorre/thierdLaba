# Имя основного исполняемого файла
TARGET = benchmark_main
SERI_TARGET = seri

# Компилятор и флаги компиляции с покрытием
CXX = g++
CXXFLAGS = -std=c++17 -g -O0 -fprofile-arcs -ftest-coverage

# Источники и заголовочные файлы
SRC = benchmark.cpp
HEADERS = MyListKV.hpp MyArray.hpp
OBJ = $(SRC:.cpp=.o)

# Директория для отчетов о покрытии
COVERAGE_DIR = coverage_report

# Цель по умолчанию
all: $(TARGET) $(SERI_TARGET)

# Сборка основного исполняемого файла
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) -L/usr/local/lib -lbenchmark -lpthread

# Компиляция файлов объекта
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Сборка и запуск seri.cpp
$(SERI_TARGET): seri.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

run_seri: cleanSeriData $(SERI_TARGET) 
	mkdir -p seriTest
	./$(SERI_TARGET)

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
clean: cleanSeriData
	rm -f $(TARGET) $(SERI_TARGET) *.o *.gcda *.gcno
	rm -rf $(COVERAGE_DIR)
	rm -f *_test.txt
	rm -f *_data.txt
	rm -f *_test.bin
	rm -f benchmark_tree.txt

cleanSeriData:
	rm -rf seriTest
	rm -f seri
	rm -f seri.gcda seri.gcno