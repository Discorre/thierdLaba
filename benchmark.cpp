#include <benchmark/benchmark.h>
#include "myListKV.hpp"
#include "myArray.hpp"
#include "myHashMap.hpp"
#include "myVector.hpp"
#include "myQueue.hpp"
#include "myStack.hpp"
#include "mySinglyLinkedList.hpp"
#include "myDoublyLinkedList.hpp"
#include "myFullBinaryTree.hpp"
#include <iostream>
#include <random>
#include <string>
#include <cstdlib>

void suppressOutput() {
    std::cout.setstate(std::ios::failbit);
}

void restoreOutput() {
    std::cout.clear();
}

// Генератор случайных строк
std::string generateRandomString(size_t length) {
    static const char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";
    static std::mt19937 generator{std::random_device{}()};
    static std::uniform_int_distribution<size_t> distribution(0, sizeof(charset) - 2);

    std::string result(length, '\0');
    for (size_t i = 0; i < length; ++i) {
        result[i] = charset[distribution(generator)];
    }
    return result;
}

//==== Benchmarks for MyList ====

static void BM_MyList_PushBack(benchmark::State& state) {
    MyList<int, int> list;
    
    for (auto _ : state) {
        list.push_back(1, 42);  // Добавляем элемент с ключом и значением
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyList_PushBack)->Range(10000, 10000)->Complexity();

static void BM_MyList_Find(benchmark::State& state) {
    MyList<int, int> list;
    for (int i = 0; i < state.range(0); ++i) {
        list.push_back(i, i);  // Заполняем список
    }
    for (auto _ : state) {
        int value;
        list.find(state.range(0) / 2, value);  // Поиск элемента в середине
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyList_Find)->Range(10000, 10000)->Complexity();

static void BM_MyList_Remove(benchmark::State& state) {
    MyList<int, int> list;
    for (int i = 0; i < state.range(0); ++i) {
        list.push_back(i, i);  // Заполняем список
    }
    for (auto _ : state) {
        list.remove(state.range(0) / 2);  // Удаляем элемент из середины
        list.push_back(state.range(0), 42);  // Восстанавливаем элемент, чтобы длина оставалась постоянной
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyList_Remove)->Range(10000, 10000)->Complexity();

// ==== Benchmarks for MyArray ====

// Benchmark для добавления элементов в конец массива
static void BM_MyArray_MPush_Back(benchmark::State& state) {
    MyArray<int> myArray;
    for (auto _ : state) {
        myArray.MPUSH(42); // Добавляем элемент
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyArray_MPush_Back)->Range(10000, 10000)->Complexity();

// Benchmark для вставки элементов по индексу
static void BM_MyArray_MPush_Index(benchmark::State& state) {
    MyArray<int> myArray;
    for (int i = 0; i < state.range(0); ++i) {
        myArray.MPUSH(i); // Заполняем массив
    }
    for (auto _ : state) {
        myArray.MPUSH(myArray.lengtharr() / 2, 42); // Вставляем элемент в середину
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyArray_MPush_Index)->Range(10000, 10000)->Complexity();

// Benchmark для удаления элемента
static void BM_MyArray_MDEL(benchmark::State& state) {
    suppressOutput();
    MyArray<int> myArray;
    for (int i = 0; i < state.range(0); ++i) {
        myArray.MPUSH(i); // Заполняем массив
    }
    for (auto _ : state) {
        myArray.MDEL(myArray.lengtharr() / 2); // Удаляем элемент из середины
    }
    myArray.MGET(-11);
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyArray_MDEL)->Range(10000, 10000)->Complexity();

// Benchmark для получения элемента по индексу
static void BM_MyArray_MGET(benchmark::State& state) {
    suppressOutput();
    MyArray<int> myArray;
    for (int i = 0; i < state.range(0); ++i) {
        myArray.MPUSH(i); // Заполняем массив
    }
    for (auto _ : state) {
        benchmark::DoNotOptimize(myArray.MGET(state.range(0) / 2)); // Получаем элемент
    }
    myArray.MGET(-11); // Восстанавливаем элемент, чтобы длина оставалась постоянной
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyArray_MGET)->Range(10000, 10000)->Complexity();

// Benchmark для получения элемента по индексу (константная версия)
static void BM_MyArray_ConstMGET(benchmark::State& state) {
    suppressOutput();
    MyArray<int> myArray;
    // Заполняем массив
    for (int i = 0; i < state.range(0); ++i) {
        myArray.MPUSH(i);
    }
    const MyArray<int>& constArray = myArray; // Создаем константную ссылку
    for (auto _ : state) {
        benchmark::DoNotOptimize(constArray.MGET(constArray.lengtharr() / 2)); // Вызываем константный MGET
    }
    state.SetComplexityN(state.range(0));
    restoreOutput();
}
BENCHMARK(BM_MyArray_ConstMGET)->Range(10000, 10000)->Complexity();

// Benchmark для замены элемента по индексу
static void BM_MyArray_MRESET(benchmark::State& state) {
    MyArray<int> myArray;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        myArray.MPUSH(i); // Заполняем массив
    }
    for (auto _ : state) {
        myArray.MRESET(state.range(0) / 2, 99); // Заменяем элемент в середине
    }
    state.SetComplexityN(state.range(0));

    myArray.MRESET(-12, 42); // Восстанавливаем элемент, чтобы длина оставалась постоянной
    restoreOutput();
}
BENCHMARK(BM_MyArray_MRESET)->Range(10000, 10000)->Complexity();

// Benchmark для сохранения массива в файл
static void BM_MyArray_SaveToFile(benchmark::State& state) {
    MyArray<int> myArray;
    for (int i = 0; i < state.range(0); ++i) {
        myArray.MPUSH(i); // Заполняем массив
    }
    for (auto _ : state) {
        myArray.saveToFile("myarray_test.txt"); // Сохраняем массив в файл
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyArray_SaveToFile)->Range(10000, 10000)->Complexity();

// Benchmark для загрузки массива из файла
static void BM_MyArray_LoadFromFile(benchmark::State& state) {
    MyArray<int> myArray;
    for (int i = 0; i < state.range(0); ++i) {
        myArray.MPUSH(i); // Заполняем массив
    }
    myArray.saveToFile("myarray_test.txt"); // Сохраняем массив в файл
    for (auto _ : state) {
        myArray.loadFromFile("myarray_test.txt"); // Загружаем массив из файла
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyArray_LoadFromFile)->Range(10000, 10000)->Complexity();;

// Benchmark для очистки массива
static void BM_MyArray_Clear(benchmark::State& state) {
    MyArray<int> myArray;
    for (int i = 0; i < state.range(0); ++i) {
        myArray.MPUSH(i); // Заполняем массив
    }
    for (auto _ : state) {
        myArray.clear(); // Очищаем массив
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyArray_Clear)->Range(10000, 10000);

// Benchmark для печати массива
static void BM_MyArray_Print(benchmark::State& state) {
    MyArray<int> myArray;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        myArray.MPUSH(i); // Заполняем массив
    }
    for (auto _ : state) {
        myArray.print(); // Печатаем массив
    }
    restoreOutput();
}
BENCHMARK(BM_MyArray_Print)->Range(10000, 10000);

static void BM_MyArray_SaveLoadFromBinaryFile(benchmark::State& state) {
    MyArray<std::string> array;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        array.MPUSH("key" + std::to_string(i));
    }
    array.saveToBinaryFile("myarray_test.bin"); // Сохраняем хэш-таблицу в бинарный файл
    for (auto _ : state) {
        array.clear();
        array.loadFromBinaryFile("myarray_test.bin"); // Загружаем хэш-таблицу из бинарного файла
    }
    state.SetComplexityN(state.range(0));
    // Устанавливаем количество байт для анализа пропускной способности
    state.SetBytesProcessed(static_cast<int64_t>(state.range(0)) * 10);
    restoreOutput();
}
BENCHMARK(BM_MyArray_SaveLoadFromBinaryFile)->Range(10000, 10000)->Complexity();

// ==== Benchmarks for MyHashMap ====

MyHashMap<std::string, int> hashmap(100);

static void BM_HashMap_Insert(benchmark::State& state) {
    for (auto _ : state) {
        hashmap.clear();
        for (int i = 0; i < state.range(0); ++i) {
            hashmap.HSET("key" + std::to_string(i), i);
        }
    }
}
BENCHMARK(BM_HashMap_Insert)->Range(10000, 10000)->Complexity();

static void BM_HashMap_Get(benchmark::State& state) {
    hashmap.clear();
    for (int i = 0; i < state.range(0); ++i) {
        hashmap.HSET("key" + std::to_string(i), i);
    }
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            int value = hashmap.HGET("key" + std::to_string(i));
            benchmark::DoNotOptimize(value);
        }
    }
}
BENCHMARK(BM_HashMap_Get)->Range(10000, 10000)->Complexity();

static void BM_HashMap_Delete(benchmark::State& state) {
    hashmap.clear();
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        hashmap.HSET("key" + std::to_string(i), i);
    }
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            hashmap.HDEL("key" + std::to_string(i));
        }
    }
    restoreOutput();
} 
BENCHMARK(BM_HashMap_Delete)->Range(10000, 10000)->Complexity();

static void BM_HashMap_SaveToFile(benchmark::State& state) {
    hashmap.clear();
    for (int i = 0; i < state.range(0); ++i) {
        hashmap.HSET("key" + std::to_string(i), i);
    }
    for (auto _ : state) {
        hashmap.saveToFile("hashmap_data.txt");
    }
}
BENCHMARK(BM_HashMap_SaveToFile)->Range(10000, 10000)->Complexity();

static void BM_HashMap_LoadFromFile(benchmark::State& state) {
    hashmap.clear();
    for (int i = 0; i < state.range(0); ++i) {
        hashmap.HSET("key" + std::to_string(i), i);
    }
    hashmap.saveToFile("hashmap_data.txt");
    for (auto _ : state) {
        hashmap.clear();
        hashmap.loadFromFile("hashmap_data.txt");
    }
}
BENCHMARK(BM_HashMap_LoadFromFile)->Range(10000, 10000)->Complexity();

// Benchmark для метода print в HashMap для малых значений
static void BM_MyHashMap_Print_Small(benchmark::State& state) {
    MyHashMap<std::string, int> hashMap;
    suppressOutput();
    
    // Заполняем HashMap малым количеством элементов
    for (int i = 0; i < state.range(0); ++i) {
        hashMap.HSET("key" + std::to_string(i), i);
    }

    for (auto _ : state) {
        hashMap.print();
    }

    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyHashMap_Print_Small)->Range(1 << 8, 1 << 8)->Complexity();

// ==== Benchmarks for MyVector ====

// Benchmark для метода insert
static void BM_MyVector_Insert(benchmark::State& state) {
    MyVector<int> vec;
    for (int i = 0; i < state.range(0); i++) {
        vec.push_back(i); // Заполняем вектор
    }
    for (auto _ : state) {
        vec.insert(state.range(0) / 2, 99); // Вставка в середину
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyVector_Insert)->Range(10000, 10000)->Complexity();

// Benchmark для метода erase
static void BM_MyVector_Erase(benchmark::State& state) {
    MyVector<int> vec;
    for (int i = 0; i < state.range(0); i++) {
        vec.push_back(42); // Заполняем вектор
    }
    for (auto _ : state) {
        vec.erase(state.range(0) / 2); // Удаление из середины
        vec.push_back(42);             // Восстанавливаем длину для консистентности
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyVector_Erase)->Range(10000, 10000)->Complexity();

// Benchmark для метода get
static void BM_MyVector_Get(benchmark::State& state) {
    MyVector<int> vec;
    for (int i = 0; i < state.range(0); i++) {
        vec.push_back(i); // Заполняем вектор
    }
    for (auto _ : state) {
        benchmark::DoNotOptimize(vec.get(state.range(0) / 2)); // Доступ к элементу в середине
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyVector_Get)->Range(10000, 10000)->Complexity();

// Benchmark для метода set
static void BM_MyVector_Set(benchmark::State& state) {
    MyVector<int> vec;
    for (int i = 0; i < state.range(0); i++) {
        vec.push_back(i); // Заполняем вектор
    }
    for (auto _ : state) {
        vec.set(state.range(0) / 2, 99); // Замена элемента в середине
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyVector_Set)->Range(10000, 10000)->Complexity();

// Benchmark для метода resize (косвенно через push_back)
static void BM_MyVector_Resize(benchmark::State& state) {
    MyVector<int> vec(state.range(0));
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            vec.push_back(i); // Заполнение массива с переразмериванием
        }
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyVector_Resize)->Range(10000, 10000)->Complexity();

// Benchmark для метода print
static void BM_MyVector_Print(benchmark::State& state) {
    MyVector<int> vec;
    for (int i = 0; i < state.range(0); ++i) {
        vec.push_back(i); // Заполняем вектор
    }
    suppressOutput();
    for (auto _ : state) {
        vec.print(); // Вывод всех элементов
    }
    state.SetComplexityN(state.range(0));
    restoreOutput();
}
BENCHMARK(BM_MyVector_Print)->Range(10000, 10000)->Complexity();

// Benchmark для метода size
static void BM_MyVector_Size(benchmark::State& state) {
    MyVector<int> vec;
    for (int i = 0; i < state.range(0); ++i) {
        vec.push_back(i); // Заполняем вектор
    }
    suppressOutput();
    for (auto _ : state) {
        benchmark::DoNotOptimize(vec.size()); // Получение текущей длины массива
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyVector_Size)->Range(10000, 10000)->Complexity();

// Benchmark для константного метода get
static void BM_MyVector_ConstGet(benchmark::State& state) {
    const MyVector<int> vec(state.range(0)); // Создаем константный вектор
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        const_cast<MyVector<int>&>(vec).push_back(i); // Заполняем вектор через const_cast
    }
    for (auto _ : state) {
        benchmark::DoNotOptimize(vec.get(state.range(0) / 2)); // Доступ к элементу в середине
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyVector_ConstGet)->Range(10000, 10000)->Complexity();

// Benchmark для перебора элементов с помощью итераторов
static void BM_MyVector_Iterate(benchmark::State& state) {
    MyVector<int> vec;
    for (int i = 0; i < state.range(0); i++) {
        vec.push_back(i); // Заполняем вектор
    }
    for (auto _ : state) {
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            benchmark::DoNotOptimize(*it); // Обрабатываем каждый элемент
        }
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyVector_Iterate)->Range(10000, 10000)->Complexity();

// Benchmark для const-итераторов
static void BM_MyVector_ConstIterate(benchmark::State& state) {
    const MyVector<int> vec = [] {
        MyVector<int> tmp;
        for (int i = 0; i < 1 << 20; i++) { // Заполняем вектор до максимального размера
            tmp.push_back(i);
        }
        return tmp;
    }();
    for (auto _ : state) {
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            benchmark::DoNotOptimize(*it); // Обрабатываем каждый элемент
        }
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyVector_ConstIterate)->Range(10000, 10000)->Complexity();

// Benchmark для перебора с изменением значений через итераторы
static void BM_MyVector_ModifyWithIterators(benchmark::State& state) {
    MyVector<int> vec;
    for (int i = 0; i < state.range(0); i++) {
        vec.push_back(i); // Заполняем вектор
    }
    for (auto _ : state) {
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            *it += 1; // Изменяем каждый элемент
        }
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyVector_ModifyWithIterators)->Range(10000, 10000)->Complexity();

// Benchmark для std::for_each с использованием итераторов
static void BM_MyVector_ForEach(benchmark::State& state) {
    MyVector<int> vec;
    for (int i = 0; i < state.range(0); i++) {
        vec.push_back(i); // Заполняем вектор
    }
    for (auto _ : state) {
        std::for_each(vec.begin(), vec.end(), [](int& value) {
            benchmark::DoNotOptimize(value); // Применяем операцию ко всем элементам
        });
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyVector_ForEach)->Range(10000, 10000)->Complexity();

// Бенчмарк для десериализации
static void BM_LoadFromBinaryFile(benchmark::State& state) {
    MyVector<std::string> vec;
    for (int i = 0; i < state.range(0); ++i) {
        vec.push_back(generateRandomString(10));
    }
    vec.saveToBinaryFile("vector_test.bin");

    for (auto _ : state) {
        MyVector<std::string> newVec;
        newVec.loadFromBinaryFile("vector_test.bin");
    }

    // Устанавливаем количество байт для анализа пропускной способности
    state.SetBytesProcessed(static_cast<int64_t>(state.range(0)) * 10);
}
BENCHMARK(BM_LoadFromBinaryFile)->Range(1 << 10, 1 << 10);

// ==== Benchmarks for MyQueue ====

// Benchmark для добавления элементов в очередь
static void BM_Queue_Q_PUSH(benchmark::State& state) {
    Queue<int> queue;
    for (auto _ : state) {
        queue.Q_PUSH(42); // Добавляем элемент
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_Queue_Q_PUSH)->Range(10000, 10000)->Complexity();

// Benchmark для удаления элемента из очереди
static void BM_Queue_Q_DEL(benchmark::State& state) {
    Queue<int> queue;
    for (int i = 0; i < state.range(0); ++i) {
        queue.Q_PUSH(i); // Заполняем очередь
    }
    for (auto _ : state) {
        queue.Q_DEL(); // Удаляем элемент
        queue.Q_PUSH(42); // Восстанавливаем, чтобы очередь оставалась заполненной
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_Queue_Q_DEL)->Range(10000, 10000)->Complexity();

// Benchmark для извлечения элемента из очереди
static void BM_Queue_Q_POP(benchmark::State& state) {
    Queue<int> queue;
    for (int i = 0; i < state.range(0); ++i) {
        queue.Q_PUSH(i); // Заполняем очередь
    }
    for (auto _ : state) {
        benchmark::DoNotOptimize(queue.Q_POP()); // Извлекаем элемент
        queue.Q_PUSH(42); // Восстанавливаем очередь
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_Queue_Q_POP)->Range(10000, 10000)->Complexity();

// Benchmark для проверки пустоты
static void BM_Queue_isEmpty(benchmark::State& state) {
    Queue<int> queue;
    for (auto _ : state) {
        benchmark::DoNotOptimize(queue.isEmpty()); // Проверяем, пуста ли очередь
    }
}
BENCHMARK(BM_Queue_isEmpty);

// Benchmark для получения размера очереди
static void BM_Queue_getSize(benchmark::State& state) {
    Queue<int> queue;
    for (int i = 0; i < state.range(0); ++i) {
        queue.Q_PUSH(i); // Заполняем очередь
    }
    for (auto _ : state) {
        benchmark::DoNotOptimize(queue.getSize()); // Получаем размер
    }
}
BENCHMARK(BM_Queue_getSize)->Range(10000, 10000);

// Benchmark для сохранения очереди в файл
static void BM_Queue_saveToFile(benchmark::State& state) {
    Queue<int> queue;
    for (int i = 0; i < state.range(0); ++i) {
        queue.Q_PUSH(i); // Заполняем очередь
    }
    for (auto _ : state) {
        queue.saveToFile("queue_test.txt"); // Сохраняем очередь в файл
    }
}
BENCHMARK(BM_Queue_saveToFile)->Range(10000, 10000);

// Benchmark для загрузки очереди из файла
static void BM_Queue_loadFromFile(benchmark::State& state) {
    Queue<int> queue;
    for (int i = 0; i < state.range(0); ++i) {
        queue.Q_PUSH(i); // Заполняем очередь
    }
    queue.saveToFile("queue_test.txt"); // Сохраняем очередь в файл
    for (auto _ : state) {
        queue.loadFromFile("queue_test.txt"); // Загружаем очередь из файла
    }
}
BENCHMARK(BM_Queue_loadFromFile)->Range(10000, 10000);

// Benchmark для очистки очереди
static void BM_Queue_clear(benchmark::State& state) {
    Queue<int> queue;
    for (int i = 0; i < state.range(0); ++i) {
        queue.Q_PUSH(i); // Заполняем очередь
    }
    for (auto _ : state) {
        queue.clear(); // Очищаем очередь
    }
}
BENCHMARK(BM_Queue_clear)->Range(10000, 10000);

// Benchmark для печати элементов очереди
static void BM_Queue_print(benchmark::State& state) {
    Queue<int> queue;
    for (int i = 0; i < state.range(0); ++i) {
        queue.Q_PUSH(i); // Заполняем очередь
    }
    suppressOutput();
    for (auto _ : state) {
        queue.print(); // Печатаем элементы
    }
    restoreOutput();
}
BENCHMARK(BM_Queue_print)->Range(10000, 10000);

// ==== Benchmarks for MyStack ====

// Benchmark для добавления элементов в стек
static void BM_MyStack_SPUSH(benchmark::State& state) {
    MyStack<int> myStack;
    suppressOutput();
    for (auto _ : state) {
        myStack.SPUSH(42); // Добавляем элемент
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyStack_SPUSH)->Range(10000, 10000)->Complexity();

// Benchmark для удаления элементов из стека
static void BM_MyStack_SDEL(benchmark::State& state) {
    MyStack<int> myStack;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        myStack.SPUSH(i); // Предварительно заполняем стек
    }
    for (auto _ : state) {
        myStack.SDEL(); // Удаляем элементы
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyStack_SDEL)->Range(10000, 10000)->Complexity();

// Benchmark для чтения верхнего элемента стека
static void BM_MyStack_SPOP(benchmark::State& state) {
    MyStack<int> myStack;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        myStack.SPUSH(i); // Заполняем стек
    }
    for (auto _ : state) {
        myStack.SPOP(); // Читаем верхний элемент
    }
    myStack.clear(); // Очищаем стек
    
    myStack.SPOP();
    restoreOutput();
    //state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyStack_SPOP)->Range(10000, 10000);


// Benchmark для очистки стека
static void BM_MyStack_Clear(benchmark::State& state) {
    MyStack<int> myStack;
    for (int i = 0; i < state.range(0); ++i) {
        myStack.SPUSH(i); // Заполняем стек
    }
    for (auto _ : state) {
        myStack.clear(); // Очищаем стек
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyStack_Clear)->Range(10000, 10000)->Complexity();

// Benchmark для сохранения стека в файл
static void BM_MyStack_SaveToFile(benchmark::State& state) {
    MyStack<int> myStack;
    for (int i = 0; i < state.range(0); ++i) {
        myStack.SPUSH(i); // Заполняем стек
    }
    for (auto _ : state) {
        myStack.saveToFile("stack_data.txt"); // Сохраняем в файл
    }
    std::remove("stack_data.txt"); // Удаляем файл после теста
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyStack_SaveToFile)->Range(10000, 10000)->Complexity();

// Benchmark для загрузки стека из файла
static void BM_MyStack_LoadFromFile(benchmark::State& state) {
    MyStack<int> myStack;
    {
        // Создаем тестовый файл
        std::ofstream outFile("stack_data.txt");
        for (int i = 0; i < state.range(0); ++i) {
            outFile << i << "\n";
        }
    }
    for (auto _ : state) {
        myStack.loadFromFile("stack_data.txt"); // Загружаем из файла
    }
    std::remove("stack_data.txt"); // Удаляем файл после теста
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyStack_LoadFromFile)->Range(10000, 10000)->Complexity();

// Benchmark для метода print
static void BM_MyStack_Print(benchmark::State& state) {
    MyStack<int> myStack;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        myStack.SPUSH(i); // Заполняем стек
    }
    for (auto _ : state) {
        myStack.print(); // Печать содержимого
    }
    myStack.clear(); // Очищаем стек
    myStack.print(); // Печать содержимого
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyStack_Print)->Range(10000, 10000)->Complexity();

// Benchmark для метода size
static void BM_MyStack_Size(benchmark::State& state) {
    MyStack<int> myStack;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        myStack.SPUSH(i); // Заполняем стек
    }
    for (auto _ : state) {
        benchmark::DoNotOptimize(myStack.size()); // Получение размера
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyStack_Size)->Range(10000, 10000)->Complexity();

// ==== Benchmarks for MySinglyLinkedList ====

// Benchmark для метода LPUSHHEAD
static void BM_MySinglyLinkedList_LPUSHHEAD(benchmark::State& state) {
    MySinglyLinkedList<int> list;
    suppressOutput();
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            list.LPUSHHEAD(i);
        }
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MySinglyLinkedList_LPUSHHEAD)->Range(10000, 10000)->Complexity();

// Benchmark для метода LPUSHTAIL
static void BM_MySinglyLinkedList_LPUSHTAIL(benchmark::State& state) {
    MySinglyLinkedList<int> list;
    suppressOutput();
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            list.LPUSHTAIL(i);
        }
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MySinglyLinkedList_LPUSHTAIL)->Range(10000, 10000)->Complexity();

// Benchmark для метода LDELHEAD
static void BM_MySinglyLinkedList_LDELHEAD(benchmark::State& state) {
    MySinglyLinkedList<int> list;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL(i);
    }
    for (auto _ : state) {
        while (list.getSize() > 0) {
            list.LDELHEAD();
        }
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MySinglyLinkedList_LDELHEAD)->Range(10000, 10000)->Complexity();

// Benchmark для метода LDELTAIL
static void BM_MySinglyLinkedList_LDELTAIL(benchmark::State& state) {
    MySinglyLinkedList<int> list;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL(i);
    }
    for (auto _ : state) {
        while (list.getSize() > 0) {
            list.LDELTAIL();
        }
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MySinglyLinkedList_LDELTAIL)->Range(10000, 10000)->Complexity();

// Benchmark для метода LDEL
static void BM_MySinglyLinkedList_LDEL(benchmark::State& state) {
    for (auto _ : state) {
        MySinglyLinkedList<int> list;
        // Заполнение списка
        for (int i = 0; i < state.range(0); ++i) {
            list.LPUSHTAIL(i);
        }

        // Удаление элементов по индексу (удаляем элементы в случайных местах)
        for (int i = 0; i < state.range(0); ++i) {
            int index = (i % list.getSize());  // Получаем валидный индекс
            list.LDEL(index);
        }
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MySinglyLinkedList_LDEL)->Range(10000, 10000)->Complexity();

// Benchmark для метода contains
static void BM_MySinglyLinkedList_Contains(benchmark::State& state) {
    MySinglyLinkedList<int> list;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL(i);
    }
    for (auto _ : state) {
        benchmark::DoNotOptimize(list.contains(state.range(0) - 1));
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MySinglyLinkedList_Contains)->Range(10000, 10000)->Complexity();

// Benchmark для метода LGET
static void BM_MySinglyLinkedList_LGET(benchmark::State& state) {
    MySinglyLinkedList<int> list;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL(i);
    }
    for (auto _ : state) {
        benchmark::DoNotOptimize(list.LGET(state.range(0) / 2));
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MySinglyLinkedList_LGET)->Range(10000, 10000)->Complexity();

// Benchmark для метода print
static void BM_MySinglyLinkedList_Print(benchmark::State& state) {
    MySinglyLinkedList<int> list;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL(i);
    }
    for (auto _ : state) {
        list.print();
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MySinglyLinkedList_Print)->Range(10000, 10000)->Complexity();

// Benchmark для метода getSize
static void BM_MySinglyLinkedList_GetSize(benchmark::State& state) {
    MySinglyLinkedList<int> list;
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL(i);
    }
    for (auto _ : state) {
        benchmark::DoNotOptimize(list.getSize());
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MySinglyLinkedList_GetSize)->Range(10000, 10000)->Complexity();

// Benchmark для методов saveToFile и loadFromFile
static void BM_MySinglyLinkedList_SaveLoadFile(benchmark::State& state) {
    MySinglyLinkedList<int> list;
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL(i);
    }
    for (auto _ : state) {
        list.saveToFile("mysinglylinkedlist_test.txt");
        list.loadFromFile("mysinglylinkedlist_test.txt");
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MySinglyLinkedList_SaveLoadFile)->Range(10000, 10000)->Complexity();

// ==== Benchmarks for MyDoublyLinkedList ====

// Benchmark для метода LPUSHHEAD
static void BM_MyDoublyLinkedList_LPUSHHEAD(benchmark::State& state) {
    MyDoublyLinkedList<int> list;
    suppressOutput();
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            list.LPUSHHEAD(i);
        }
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyDoublyLinkedList_LPUSHHEAD)->Range(10000, 10000)->Complexity();

// Benchmark для метода LPUSHTAIL
static void BM_MyDoublyLinkedList_LPUSHTAIL(benchmark::State& state) {
    MyDoublyLinkedList<int> list;
    suppressOutput();
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            list.LPUSHTAIL(i);
        }
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyDoublyLinkedList_LPUSHTAIL)->Range(10000, 10000)->Complexity();

// Benchmark для метода LDELHEAD
static void BM_MyDoublyLinkedList_LDELHEAD(benchmark::State& state) {
    MyDoublyLinkedList<int> list;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL(i);
    }
    for (auto _ : state) {
        while (list.getSize() > 0) {
            list.LDELHEAD();
        }
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyDoublyLinkedList_LDELHEAD)->Range(10000, 10000)->Complexity();

// Benchmark для метода LDELTAIL
static void BM_MyDoublyLinkedList_LDELTAIL(benchmark::State& state) {
    MyDoublyLinkedList<int> list;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL(i);
    }
    for (auto _ : state) {
        while (list.getSize() > 0) {
            list.LDELTAIL();
        }
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyDoublyLinkedList_LDELTAIL)->Range(10000, 10000)->Complexity();

// Benchmark для метода LDEL (удаление по индексу)
static void BM_MyDoublyLinkedList_LDEL(benchmark::State& state) {
    suppressOutput();
    for (auto _ : state) {
        MyDoublyLinkedList<int> list;
        for (int i = 0; i < state.range(0); ++i) {
            list.LPUSHTAIL(i);
        }
        for (int i = 0; i < state.range(0); ++i) {
            int index = (i % list.getSize());
            list.LDEL(index);
        }
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyDoublyLinkedList_LDEL)->Range(10000, 10000)->Complexity();

// Benchmark для метода contains
static void BM_MyDoublyLinkedList_Contains(benchmark::State& state) {
    MyDoublyLinkedList<int> list;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL(i);
    }
    for (auto _ : state) {
        benchmark::DoNotOptimize(list.contains(state.range(0) - 1));
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyDoublyLinkedList_Contains)->Range(10000, 10000)->Complexity();

// Benchmark для метода LGET
static void BM_MyDoublyLinkedList_LGET(benchmark::State& state) {
    MyDoublyLinkedList<int> list;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL(i);
    }
    for (auto _ : state) {
        benchmark::DoNotOptimize(list.LGET(state.range(0) / 2));
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyDoublyLinkedList_LGET)->Range(10000, 10000)->Complexity();

// Benchmark для метода print
static void BM_MyDoublyLinkedList_Print(benchmark::State& state) {
    MyDoublyLinkedList<int> list;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL(i);
    }
    for (auto _ : state) {
        list.print();
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyDoublyLinkedList_Print)->Range(10000, 10000)->Complexity();

// Benchmark для метода getSize
static void BM_MyDoublyLinkedList_GetSize(benchmark::State& state) {
    MyDoublyLinkedList<int> list;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL(i);
    }
    for (auto _ : state) {
        benchmark::DoNotOptimize(list.getSize());
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyDoublyLinkedList_GetSize)->Range(10000, 10000)->Complexity();

// Benchmark для методов saveToFile и loadFromFile
static void BM_MyDoublyLinkedList_SaveLoadFile(benchmark::State& state) {
    MyDoublyLinkedList<int> list;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL(i);
    }
    for (auto _ : state) {
        list.saveToFile("mydoublylinkedlist_test.txt");
        list.loadFromFile("mydoublylinkedlist_test.txt");
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyDoublyLinkedList_SaveLoadFile)->Range(10000, 10000)->Complexity();

// ==== Benchmarks for MyFullBinaryTree ====

// Бенчмарк для функции TINSERT
static void BM_TINSERT(benchmark::State& state) {
    FullBinaryTree<int> tree;
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            tree.TINSERT(i);
        }
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_TINSERT)->Range(10000, 10000)->Complexity();

// Бенчмарк для функции TDEL
static void BM_TDEL(benchmark::State& state) {
    FullBinaryTree<int> tree;
    for (int i = 0; i < state.range(0); ++i) {
        tree.TINSERT(i);
    }
    for (auto _ : state) {
        tree.TDEL(state.range(0) - 1);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_TDEL)->Range(10000, 10000)->Complexity();

// Бенчмарк для функции TGET
static void BM_TGET(benchmark::State& state) {
    FullBinaryTree<int> tree;
    for (int i = 0; i < state.range(0); ++i) {
        tree.TINSERT(i);
    }
    for (auto _ : state) {
        benchmark::DoNotOptimize(tree.TGET(state.range(0) - 1));
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_TGET)->Range(10000, 10000)->Complexity();

// Бенчмарк для функции print
static void BM_PRINT(benchmark::State& state) {
    FullBinaryTree<int> tree;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        tree.TINSERT(i);
    }
    for (auto _ : state) {
        tree.print();
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_PRINT)->Range(10000, 10000)->Complexity();

// Бенчмарк для функции isFull
static void BM_ISFULL(benchmark::State& state) {
    FullBinaryTree<int> tree;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        tree.TINSERT(i);
    }
    for (auto _ : state) {
        tree.isFull();
    }
    FullBinaryTree<int> tree2;
    tree2.isFull();
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_ISFULL)->Range(10000, 10000)->Complexity();

// Бенчмарк для функции saveToFile
static void BM_SAVETOFILE(benchmark::State& state) {
    FullBinaryTree<int> tree;
    for (int i = 0; i < state.range(0); ++i) {
        tree.TINSERT(i);
    }
    for (auto _ : state) {
        tree.saveToFile("benchmark_tree.txt");
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_SAVETOFILE)->Range(10000, 10000)->Complexity();

// Бенчмарк для функции loadFromFile
static void BM_LOADFROMFILE(benchmark::State& state) {
    FullBinaryTree<int> tree;
    for (int i = 0; i < state.range(0); ++i) {
        tree.TINSERT(i);
    }
    tree.saveToFile("benchmark_tree.txt");
    for (auto _ : state) {
        tree.loadFromFile("benchmark_tree.txt");
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_LOADFROMFILE)->Range(10000, 10000)->Complexity();

static void BM_PRINTROOT(benchmark::State& state) {
    FullBinaryTree<int> tree;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        tree.TINSERT(i);
    }
    for (auto _ : state) {
        tree.printRoot();
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_PRINTROOT)->Range(10000, 10000)->Complexity();

static void BM_GETROOT(benchmark::State& state) {
    FullBinaryTree<int> tree;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        tree.TINSERT(i);
    }
    for (auto _ : state) {
        benchmark::DoNotOptimize(tree.getRoot());
    }
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_GETROOT)->Range(10000, 10000)->Complexity();

// Бенчмарк для удаления узла с одним потомком
static void BM_TDELOneChild(benchmark::State& state) {
    for (auto _ : state) {
        FullBinaryTree<int> tree;
        tree.TINSERT(50);
        tree.TINSERT(30);
        tree.TINSERT(70);
        tree.TINSERT(20);
        
        // Удаляем узел с одним потомком
        tree.TDEL(30);
    }
}
BENCHMARK(BM_TDELOneChild);

// Бенчмарк для удаления узла с двумя потомками
static void BM_TDELTwoChildren(benchmark::State& state) {
    for (auto _ : state) {
        FullBinaryTree<int> tree;
        tree.TINSERT(50);
        tree.TINSERT(30);
        tree.TINSERT(70);
        tree.TINSERT(20);
        tree.TINSERT(40);
        
        // Удаляем узел с двумя потомками
        tree.TDEL(30);
    }
}
BENCHMARK(BM_TDELTwoChildren);

// ==== Main Function to Run All Benchmarks ====

BENCHMARK_MAIN();

