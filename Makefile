# Имя исполняемого файла(для Windows)
#TARGET = a.exe

# Имя исполняемого файла(для Linux)
TARGET = a.out

# Имя исполняемого файла для тестов
TEST_TARGET = test_a.out

# Список исходных файлов .cpp
SRCS = mainMenu.cpp

# Список исходных файлов для тестов
TEST_SRCS = mainMenu_test.cpp

# Список заголовочных файлов .h и .hpp
#HDRS = myListKV.hpp myVector.hpp mySinglyLinkedList.hpp myArray.hpp myDoublyLinkedList.hpp myQueue.hpp myStack.hpp 

# Список объектных файлов .o, которые будут созданы
OBJS = $(SRCS:.cpp=.o)

# Список объектных файлов для тестов
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Флаги компиляции
CXXFLAGS = -Wall -Wextra -std=c++17

# Флаги для компиляции тестов
TEST_CXXFLAGS = $(CXXFLAGS) -isystem googletest/googletest/include -isystem googletest/googlemock/include

# Компилятор
CXX = g++

# Правило для сборки исполняемого файла
$(TARGET): $(OBJS)
    $(CXX) $(OBJS) -o $(TARGET)

# Правило для компиляции каждого .cpp файла в .o файл
%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

# Правило для сборки исполняемого файла тестов
$(TEST_TARGET): $(TEST_OBJS) $(OBJS)
    $(CXX) $(TEST_OBJS) $(OBJS) -o $(TEST_TARGET) -L googletest/build/lib -lgtest -lgtest_main -lpthread

# Правило для компиляции каждого .cpp файла тестов в .o файл
%.o: %.cpp
    $(CXX) $(TEST_CXXFLAGS) -c $< -o $@

# Правило для очистки объектных файлов и исполняемого файла
clean:
    rm -f $(OBJS) $(TARGET) $(TEST_OBJS) $(TEST_TARGET)

# Правило для перекомпиляции всего проекта
rebuild: clean $(TARGET)

# Правило для запуска тестов
test: $(TEST_TARGET)
    ./$(TEST_TARGET)

# Правило по умолчанию
.PHONY: all clean rebuild test