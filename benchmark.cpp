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

}
BENCHMARK(BM_MyList_PushBack)->Range(10000, 10000);

static void BM_MyList_Find(benchmark::State& state) {
    MyList<int, int> list;
    for (int i = 0; i < state.range(0); ++i) {
        list.push_back(i, i);  // Заполняем список
    }
    for (auto _ : state) {
        int value;
        list.find(state.range(0) / 2, value);  // Поиск элемента в середине
    }

}
BENCHMARK(BM_MyList_Find)->Range(10000, 10000);

static void BM_MyList_Remove(benchmark::State& state) {
    MyList<int, int> list;
    for (int i = 0; i < state.range(0); ++i) {
        list.push_back(i, i);  // Заполняем список
    }
    for (auto _ : state) {
        list.remove(state.range(0) / 2);  // Удаляем элемент из середины
        list.push_back(state.range(0), 42);  // Восстанавливаем элемент, чтобы длина оставалась постоянной
    }

}
BENCHMARK(BM_MyList_Remove)->Range(10000, 10000);

// ==== Benchmarks for MyArray ====

static void BM_MyArray_Combined(benchmark::State& state) {
    MyArray<int> myArray;
    
    suppressOutput(); // Запрещаем вывод сообщений на экран
    // Заполнение массива перед началом бенчмарка
    for (int i = 0; i < state.range(0); ++i) {
        myArray.MPUSH(i); // Заполняем массив
    }

    for (auto _ : state) {
        // Добавление элемента в конец массива
        myArray.MPUSH(42);

        // Вставка элемента по индексу (в середину массива)
        myArray.MPUSH(myArray.lengtharr() / 2, 42);

        // Удаление элемента из середины массива
        myArray.MDEL(myArray.lengtharr() / 2);

        // Получение элемента по индексу
        benchmark::DoNotOptimize(myArray.MGET(state.range(0) / 2));

        // Получение элемента по индексу (константная версия)
        const MyArray<int>& constArray = myArray;
        benchmark::DoNotOptimize(constArray.MGET(constArray.lengtharr() / 2));
        myArray.MGET(-11); 

        // Замена элемента по индексу
        myArray.MRESET(state.range(0) / 2, 99);
    }

    // Восстановление состояния массива для теста
    myArray.MRESET(-12, 42);  // Восстановление элемента, чтобы длина оставалась постоянной
    restoreOutput();
}
BENCHMARK(BM_MyArray_Combined)->Range(10000, 10000);


// Benchmark для сохранения массива в файл
static void BM_MyArray_SaveToFile(benchmark::State& state) {
    MyArray<int> myArray;
    for (int i = 0; i < state.range(0); ++i) {
        myArray.MPUSH(i); // Заполняем массив
    }
    for (auto _ : state) {
        myArray.saveToFile("seriTest/myarray_test.txt"); // Сохраняем массив в файл
    }

}
BENCHMARK(BM_MyArray_SaveToFile)->Range(10000, 10000);

// Benchmark для загрузки массива из файла
static void BM_MyArray_LoadFromFile(benchmark::State& state) {
    MyArray<int> myArray;
    for (int i = 0; i < state.range(0); ++i) {
        myArray.MPUSH(i); // Заполняем массив
    }
    myArray.saveToFile("seriTest/myarray_test.txt"); // Сохраняем массив в файл
    for (auto _ : state) {
        myArray.loadFromFile("seriTest/myarray_test.txt"); // Загружаем массив из файла
    }
}
BENCHMARK(BM_MyArray_LoadFromFile)->Range(10000, 10000);

// Benchmark для очистки массива
static void BM_MyArray_Clear(benchmark::State& state) {
    MyArray<int> myArray;
    for (int i = 0; i < state.range(0); ++i) {
        myArray.MPUSH(i); // Заполняем массив
    }
    for (auto _ : state) {
        myArray.clear(); // Очищаем массив
    }

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
    array.saveToBinaryFile("seriTest/myarray_test.bin"); // Сохраняем хэш-таблицу в бинарный файл
    array.clear();
    for (auto _ : state) {
        
        array.loadFromBinaryFile("seriTest/myarray_test.bin"); // Загружаем хэш-таблицу из бинарного файла
    }
    // Устанавливаем количество байт для анализа пропускной способности
    state.SetBytesProcessed(static_cast<int64_t>(state.range(0)) * 10);
    restoreOutput();
}
BENCHMARK(BM_MyArray_SaveLoadFromBinaryFile)->Range(10000, 10000);

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
BENCHMARK(BM_HashMap_Insert)->Range(10000, 10000);

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
BENCHMARK(BM_HashMap_Get)->Range(10000, 10000);

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
BENCHMARK(BM_HashMap_Delete)->Range(10000, 10000);

static void BM_HashMap_SaveToFile(benchmark::State& state) {
    hashmap.clear();
    for (int i = 0; i < state.range(0); ++i) {
        hashmap.HSET("key" + std::to_string(i), i);
    }
    for (auto _ : state) {
        hashmap.saveToFile("seriTest/hashmap_data.txt");
    }
}
BENCHMARK(BM_HashMap_SaveToFile)->Range(10000, 10000);

static void BM_HashMap_LoadFromFile(benchmark::State& state) {
    hashmap.clear();
    for (int i = 0; i < state.range(0); ++i) {
        hashmap.HSET("key" + std::to_string(i), i);
    }
    hashmap.saveToFile("seriTest/hashmap_data.txt");
    for (auto _ : state) {
        hashmap.clear();
        hashmap.loadFromFile("seriTest/hashmap_data.txt");
    }
}
BENCHMARK(BM_HashMap_LoadFromFile)->Range(10000, 10000);

// Тест производительности сериализации
static void BM_SaveToBinaryFileHM(benchmark::State& state) {
    MyHashMap<std::string, int> hashMap(1000);
    for (int i = 0; i < state.range(0); ++i) {
        hashMap.HSET("key" + std::to_string(i), i);
    }

    for (auto _ : state) {
        hashMap.saveToBinaryFile("seriTest/temp_data.bin");
    }
}
BENCHMARK(BM_SaveToBinaryFileHM)->Range(10000, 10000);

// Тест производительности десериализации
static void BM_LoadFromBinaryFileHM(benchmark::State& state) {
    MyHashMap<std::string, int> hashMap(1000);
    for (int i = 0; i < state.range(0); ++i) {
        hashMap.HSET("key" + std::to_string(i), i);
    }
    hashMap.saveToBinaryFile("seriTest/temp_data.bin");

    for (auto _ : state) {
        MyHashMap<std::string, int> loadedHashMap;
        loadedHashMap.loadFromBinaryFile("seriTest/temp_data.bin");
    }
}
BENCHMARK(BM_LoadFromBinaryFileHM)->Range(10000, 10000);

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

}
BENCHMARK(BM_MyHashMap_Print_Small)->Range(1 << 8, 1 << 8);

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

}
BENCHMARK(BM_MyVector_Insert)->Range(10000, 10000);

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

}
BENCHMARK(BM_MyVector_Erase)->Range(10000, 10000);

// Benchmark для метода get
static void BM_MyVector_Get(benchmark::State& state) {
    MyVector<int> vec;
    for (int i = 0; i < state.range(0); i++) {
        vec.push_back(i); // Заполняем вектор
    }
    for (auto _ : state) {
        benchmark::DoNotOptimize(vec.get(state.range(0) / 2)); // Доступ к элементу в середине
    }

}
BENCHMARK(BM_MyVector_Get)->Range(10000, 10000);

// Benchmark для метода set
static void BM_MyVector_Set(benchmark::State& state) {
    MyVector<int> vec;
    for (int i = 0; i < state.range(0); i++) {
        vec.push_back(i); // Заполняем вектор
    }
    for (auto _ : state) {
        vec.set(state.range(0) / 2, 99); // Замена элемента в середине
    }

}
BENCHMARK(BM_MyVector_Set)->Range(10000, 10000);

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

    restoreOutput();
}
BENCHMARK(BM_MyVector_Print)->Range(10000, 10000);

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

}
BENCHMARK(BM_MyVector_Size)->Range(10000, 10000);

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

}
BENCHMARK(BM_MyVector_ConstGet)->Range(10000, 10000);

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

}
BENCHMARK(BM_MyVector_Iterate)->Range(10000, 10000);

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

}
BENCHMARK(BM_MyVector_ConstIterate)->Range(10000, 10000);

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

}
BENCHMARK(BM_MyVector_ModifyWithIterators)->Range(10000, 10000);

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

}
BENCHMARK(BM_MyVector_ForEach)->Range(10000, 10000);

// Бенчмарк для десериализации
static void BM_LoadFromBinaryFile(benchmark::State& state) {
    MyVector<std::string> vec;
    for (int i = 0; i < state.range(0); ++i) {
        vec.push_back(generateRandomString(10));
    }
    vec.saveToBinaryFile("seriTest/vector_test.bin");

    for (auto _ : state) {
        MyVector<std::string> newVec;
        newVec.loadFromBinaryFile("seriTest/vector_test.bin");
    }

    // Устанавливаем количество байт для анализа пропускной способности
    state.SetBytesProcessed(static_cast<int64_t>(state.range(0)) * 10);
}
BENCHMARK(BM_LoadFromBinaryFile)->Range(10000, 10000);

// ==== Benchmarks for MyQueue ====

// Benchmark для добавления элементов в очередь
static void BM_Queue_Q_PUSH(benchmark::State& state) {
    Queue<int> queue;
    for (auto _ : state) {
        queue.Q_PUSH(42); // Добавляем элемент
    }

}
BENCHMARK(BM_Queue_Q_PUSH)->Range(10000, 10000);

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

}
BENCHMARK(BM_Queue_Q_DEL)->Range(10000, 10000);

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

}
BENCHMARK(BM_Queue_Q_POP)->Range(10000, 10000);

// Benchmark для проверки пустоты
static void BM_Queue_isEmpty(benchmark::State& state) {
    Queue<int> queue;
    for(int i = 0; i < state.range(0); ++i) {
        queue.Q_PUSH(i); // Заполняем очередь
    }
    for (auto _ : state) {
        queue.isEmpty(); // Проверяем, пуста ли очередь
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
        queue.saveToFile("seriTest/queue_test.txt"); // Сохраняем очередь в файл
    }
}
BENCHMARK(BM_Queue_saveToFile)->Range(10000, 10000);

// Benchmark для загрузки очереди из файла
static void BM_Queue_loadFromFile(benchmark::State& state) {
    Queue<int> queue;
    for (int i = 0; i < state.range(0); ++i) {
        queue.Q_PUSH(i); // Заполняем очередь
    }
    queue.saveToFile("seriTest/queue_test.txt"); // Сохраняем очередь в файл
    for (auto _ : state) {
        queue.loadFromFile("seriTest/queue_test.txt"); // Загружаем очередь из файла
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

// Бенчмарк для сохранения очереди в бинарный файл
static void BM_SaveToBinaryFile_Queue(benchmark::State& state) {
    Queue<int> queue;
    for (size_t i = 0; i < state.range(0); ++i) {
        queue.Q_PUSH(i);
    }
    const std::string filename = "seriTest/queue_data.bin";

    for (auto _ : state) {
        queue.saveToBinaryFile(filename);
    }

}
BENCHMARK(BM_SaveToBinaryFile_Queue)->Range(10000, 10000);

// Бенчмарк для загрузки очереди из бинарного файла
static void BM_LoadFromBinaryFile_Queue(benchmark::State& state) {
    Queue<int> queue;
    for (size_t i = 0; i < state.range(0); ++i) {
        queue.Q_PUSH(i);
    }
    const std::string filename = "seriTest/queue_data.bin";
    queue.saveToBinaryFile(filename);

    for (auto _ : state) {
        Queue<int> loadedQueue;
        loadedQueue.loadFromBinaryFile(filename);
    }
}
BENCHMARK(BM_LoadFromBinaryFile_Queue)->Range(10000, 10000);

// ==== Benchmarks for MyStack ====

// Общий Benchmark для всех операций со стеком
static void BM_MyStack_AllOperations(benchmark::State& state) {
    MyStack<int> myStack;
    suppressOutput();

    // Заполняем стек
    for (int i = 0; i < state.range(0); ++i) {
        myStack.SPUSH(i);
    }

    for (auto _ : state) {
        // Добавляем элементы
        for (int i = 0; i < 10; ++i) {
            myStack.SPUSH(42);
        }

        // Удаляем элементы
        for (int i = 0; i < 10; ++i) {
            myStack.SDEL();
        }

        // Читаем верхний элемент
        for (int i = 0; i < 10; ++i) {
            myStack.SPOP();
        }

        // Очищаем стек
        myStack.clear();
    }

    restoreOutput();
}

BENCHMARK(BM_MyStack_AllOperations)->Range(10000, 10000);

// Benchmark для сохранения стека в файл
static void BM_MyStack_SaveToFile(benchmark::State& state) {
    MyStack<std::string> myStack;
    for (int i = 0; i < state.range(0); ++i) {
        myStack.SPUSH("key" + std::to_string(i)); // Заполняем стек
    }
    for (auto _ : state) {
        myStack.size();
        myStack.saveToFile("seriTest/stack_data.txt"); // Сохраняем в файл
    }

}
BENCHMARK(BM_MyStack_SaveToFile)->Range(10000, 10000);

// Benchmark для загрузки стека из файла
static void BM_MyStack_LoadFromFile(benchmark::State& state) {
    MyStack<std::string> myStack;

    for (auto _ : state) {
        myStack.loadFromFile("seriTest/stack_data.txt"); // Загружаем из файла
    }

}
BENCHMARK(BM_MyStack_LoadFromFile)->Range(10000, 10000);

// Бенчмарк для сериализации стека в файл
static void BM_SerializeStack(benchmark::State& state) {
    const std::string filename = "seriTest/stack_data.bin";

    // Создаём тестовый стек и заполняем его
    MyStack<std::string> stack;
    for (int i = 0; i < state.range(0); ++i) {
        stack.SPUSH("key" + std::to_string(i));
    }

    // Записываем стек в файл
    for (auto _ : state) {
        stack.saveToFileBinary(filename);
    }
}
BENCHMARK(BM_SerializeStack)->Range(10000, 10000);

// Бенчмарк для десериализации стека из файла
static void BM_DeserializeStack(benchmark::State& state) {
    const std::string filename = "seriTest/stack_data.bin";

    // Сначала создаём стек, сохраняем его и удаляем
    MyStack<std::string> stack;
    
    // Загружаем стек из файла
    for (auto _ : state) {
        stack.loadFromBinaryFile(filename);
    }
}
BENCHMARK(BM_DeserializeStack)->Range(10000, 10000);

// Benchmark для метода print
static void BM_MyStack_PrintSize(benchmark::State& state) {
    MyStack<std::string> myStack;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        myStack.SPUSH("key" + std::to_string(i)); // Заполняем стек
    }
    for (auto _ : state) {
        myStack.print(); // Печать содержимого
        myStack.size(); // Получение размера
    }
    myStack.clear(); // Очищаем стек
    myStack.print(); // Печать содержимого
    restoreOutput();

}
BENCHMARK(BM_MyStack_PrintSize)->Range(10000, 10000);


// ==== Benchmarks for MySinglyLinkedList ====

// Benchmark для метода LPUSHTAIL
static void BM_MySinglyLinkedList_LPUSHTAIL(benchmark::State& state) {
    MySinglyLinkedList<std::string> list;
    suppressOutput();
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            list.LPUSHTAIL("key" + std::to_string(i));
        }
    }
    restoreOutput();

}
BENCHMARK(BM_MySinglyLinkedList_LPUSHTAIL)->Range(10000, 10000);

static void BM_MySinglyLinkedList_SaveLoadToBinary(benchmark::State& state) {
    MySinglyLinkedList<std::string> list;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL("key" + std::to_string(i));
    }
    MySinglyLinkedList<std::string> loadedList;
    for (auto _ : state) {
        list.saveToBinaryFile("seriTest/list_data.bin");
        loadedList.loadFromBinaryFile("seriTest/list_data.bin");
    }

    restoreOutput();
}
BENCHMARK(BM_MySinglyLinkedList_SaveLoadToBinary)->Range(10000, 10000);

// Benchmark для метода LDELHEAD
static void BM_MySinglyLinkedList_LDELHEAD(benchmark::State& state) {
    MySinglyLinkedList<std::string> list;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL("key" + std::to_string(i));
    }
    for (auto _ : state) {
        while (list.getSize() > 0) {
            list.LDELHEAD();
        }
    }
    restoreOutput();

}
BENCHMARK(BM_MySinglyLinkedList_LDELHEAD)->Range(10000, 10000);

// Benchmark для метода LDELTAIL
static void BM_MySinglyLinkedList_LDELTAIL(benchmark::State& state) {
    MySinglyLinkedList<std::string> list;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL("key" + std::to_string(i));
    }
    for (auto _ : state) {
        while (list.getSize() > 0) {
            list.LDELTAIL();
        }
    }
    restoreOutput();

}
BENCHMARK(BM_MySinglyLinkedList_LDELTAIL)->Range(10000, 10000);

// Benchmark для метода LDEL
static void BM_MySinglyLinkedList_LDEL(benchmark::State& state) {
    for (auto _ : state) {
        MySinglyLinkedList<std::string> list;
        // Заполнение списка
        for (int i = 0; i < state.range(0); ++i) {
            list.LPUSHHEAD("key" + std::to_string(i));
        }

        // Удаление элементов по индексу (удаляем элементы в случайных местах)
        for (int i = 0; i < state.range(0); ++i) {
            int index = (i % list.getSize());  // Получаем валидный индекс
            list.LDEL(index);
        }
    }

}
BENCHMARK(BM_MySinglyLinkedList_LDEL)->Range(10000, 10000);

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

}
BENCHMARK(BM_MySinglyLinkedList_Contains)->Range(10000, 10000);

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

}
BENCHMARK(BM_MySinglyLinkedList_LGET)->Range(10000, 10000);

// Benchmark для метода print
static void BM_MySinglyLinkedList_Print(benchmark::State& state) {
    MySinglyLinkedList<std::string> list;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL("key" + std::to_string(i));
    }
    for (auto _ : state) {
        list.print();
    }
    restoreOutput();

}
BENCHMARK(BM_MySinglyLinkedList_Print)->Range(10000, 10000);

// Benchmark для метода getSize
static void BM_MySinglyLinkedList_GetSize(benchmark::State& state) {
    MySinglyLinkedList<int> list;
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL(i);
    }
    for (auto _ : state) {
        benchmark::DoNotOptimize(list.getSize());
    }

}
BENCHMARK(BM_MySinglyLinkedList_GetSize)->Range(10000, 10000);

// Benchmark для методов saveToFile и loadFromFile
static void BM_MySinglyLinkedList_SaveLoadFile(benchmark::State& state) {
    MySinglyLinkedList<int> list;
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL(i);
    }
    for (auto _ : state) {
        list.saveToFile("seriTest/mysinglylinkedlist_test.txt");
        list.loadFromFile("seriTest/mysinglylinkedlist_test.txt");
    }

}
BENCHMARK(BM_MySinglyLinkedList_SaveLoadFile)->Range(10000, 10000);

// Бенчмарк сериализации
static void BM_Serialization(benchmark::State& state) {
    MyDoublyLinkedList<std::string> list;
    for (int i = 0; i < 10000; ++i) {
        list.LPUSHTAIL("key" + std::to_string(i));
    }
    for (auto _ : state) {
        list.saveToBinaryFile("seriTest/dlist_data.bin"); // Сериализация списка
    }
}
BENCHMARK(BM_Serialization)->Range(10000, 10000);

// Бенчмарк десериализации
static void BM_Deserialization(benchmark::State& state) {
    MyDoublyLinkedList<std::string> list;

    for (auto _ : state) {
        list.loadFromBinaryFile("seriTest/dlist_data.bin"); // Десериализация списка
    }
}
BENCHMARK(BM_Deserialization)->Range(10000, 10000);

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

}
BENCHMARK(BM_MyDoublyLinkedList_LPUSHHEAD)->Range(10000, 10000);

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

}
BENCHMARK(BM_MyDoublyLinkedList_LPUSHTAIL)->Range(10000, 10000);

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

}
BENCHMARK(BM_MyDoublyLinkedList_LDELHEAD)->Range(10000, 10000);

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

}
BENCHMARK(BM_MyDoublyLinkedList_LDELTAIL)->Range(10000, 10000);

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

}
BENCHMARK(BM_MyDoublyLinkedList_LDEL)->Range(10000, 10000);

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

}
BENCHMARK(BM_MyDoublyLinkedList_Contains)->Range(10000, 10000);

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

}
BENCHMARK(BM_MyDoublyLinkedList_LGET)->Range(10000, 10000);

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

}
BENCHMARK(BM_MyDoublyLinkedList_Print)->Range(10000, 10000);

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

}
BENCHMARK(BM_MyDoublyLinkedList_GetSize)->Range(10000, 10000);

// Benchmark для методов saveToFile и loadFromFile
static void BM_MyDoublyLinkedList_SaveLoadFile(benchmark::State& state) {
    MyDoublyLinkedList<int> list;
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        list.LPUSHTAIL(i);
    }
    for (auto _ : state) {
        list.saveToFile("seriTest/mydoublylinkedlist_test.txt");
        list.loadFromFile("seriTest/mydoublylinkedlist_test.txt");
    }
    restoreOutput();

}
BENCHMARK(BM_MyDoublyLinkedList_SaveLoadFile)->Range(10000, 10000);

// ==== Benchmarks for MyFullBinaryTree ====

//Бенчмарк для функции TINSERT
static void BM_TINSERT(benchmark::State& state) {
    FullBinaryTree<int> tree;
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            tree.TINSERT(i);
        }
    }

}
BENCHMARK(BM_TINSERT)->Range(10000, 10000);

// Бенчмарк для функции TDEL
static void BM_TDEL(benchmark::State& state) {
    FullBinaryTree<int> tree;
    for (int i = 0; i < state.range(0); ++i) {
        tree.TINSERT(i);
    }
    for (auto _ : state) {
        tree.TDEL(state.range(0) - 1);
    }

}
BENCHMARK(BM_TDEL)->Range(10000, 10000);

// Бенчмарк для функции TGET
static void BM_TGET(benchmark::State& state) {
    FullBinaryTree<int> tree;
    for (int i = 0; i < state.range(0); ++i) {
        tree.TINSERT(i);
    }
    for (auto _ : state) {
        benchmark::DoNotOptimize(tree.TGET(state.range(0) - 1));
    }

}
BENCHMARK(BM_TGET)->Range(10000, 10000);

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

}
BENCHMARK(BM_PRINT)->Range(10000, 10000);

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

}
BENCHMARK(BM_ISFULL)->Range(10000, 10000);

// Бенчмарк для функции saveToFile
static void BM_SAVETOFILE(benchmark::State& state) {
    FullBinaryTree<int> tree;
    for (int i = 0; i < state.range(0); ++i) {
        tree.TINSERT(i);
    }
    for (auto _ : state) {
        tree.saveToFile("seriTest/benchmark_tree.txt");
    }
    FullBinaryTree<int> tree1;
    tree1.loadFromFile("seriTest/benchmark_tree.txt");
}
BENCHMARK(BM_SAVETOFILE)->Range(10000, 10000);

// Бенчмарк для функции loadFromFile
static void BM_LOADFROMFILE(benchmark::State& state) {
    FullBinaryTree<int> tree;
    for (int i = 0; i < state.range(0); ++i) {
        tree.TINSERT(i);
    }
    tree.saveToFile("seriTest/benchmark_tree.txt");
    for (auto _ : state) {
        tree.loadFromFile("seriTest/benchmark_tree.txt");
    }

}
BENCHMARK(BM_LOADFROMFILE)->Range(10000, 10000);

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

}
BENCHMARK(BM_PRINTROOT)->Range(10000, 10000);

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

}
BENCHMARK(BM_GETROOT)->Range(10000, 10000);

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

// Бенчмарк для сохранения дерева в бинарный файл
 static void BM_SaveToBinaryFileFBT(benchmark::State& state) {
     const std::string filename = "seriTest/test_tree.bin";

     for (auto _ : state) {
         FullBinaryTree<int> tree;
         tree.TINSERT(50);
         tree.TINSERT(30);
         tree.TINSERT(70);
         tree.TINSERT(20);
         tree.TINSERT(40);
        
         tree.saveToBinaryFile(filename);
     }
 }

// Бенчмарк для загрузки дерева из бинарного файла
 static void BM_LoadFromBinaryFileFBT(benchmark::State& state) {
     const std::string filename = "seriTest/test_tree.bin";
     for (auto _ : state) {
         FullBinaryTree<int> loadedTree;
         loadedTree.loadFromBinaryFile(filename);
     }
 }

// Регистрация бенчмарков с диапазоном количества узлов
BENCHMARK(BM_SaveToBinaryFileFBT);
BENCHMARK(BM_LoadFromBinaryFileFBT);

// ==== Main Function to Run All Benchmarks ====

BENCHMARK_MAIN();

