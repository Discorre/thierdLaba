#include <benchmark/benchmark.h>
#include "myListKV.hpp"
#include "myArray.hpp"
#include "myHashMap.hpp"
#include "myVector.hpp"
#include "myQueue.hpp"
#include <string>
#include <cstdlib>

void suppressOutput() {
    std::cout.setstate(std::ios::failbit);
}

void restoreOutput() {
    std::cout.clear();
}

// ==== Benchmarks for MyList ====

static void BM_MyList_PushBack(benchmark::State& state) {
    MyList<int, int> list;
    
    for (auto _ : state) {
        list.push_back(1, 42);  // Добавляем элемент с ключом и значением
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyList_PushBack)->Range(1 << 10, 1 << 20)->Complexity();

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
BENCHMARK(BM_MyList_Find)->Range(1 << 10, 1 << 20)->Complexity();

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
BENCHMARK(BM_MyList_Remove)->Range(1 << 10, 1 << 20)->Complexity();

// ==== Benchmarks for MyArray ====

// Benchmark для добавления элементов в конец массива
static void BM_MyArray_MPush_Back(benchmark::State& state) {
    MyArray<int> myArray;
    for (auto _ : state) {
        myArray.MPUSH(42); // Добавляем элемент
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyArray_MPush_Back)->Range(1 << 10, 1 << 20)->Complexity();

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
BENCHMARK(BM_MyArray_MPush_Index)->Range(1 << 10, 1 << 20)->Complexity();

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
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyArray_MDEL)->Range(1 << 10, 1 << 20)->Complexity();

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
    restoreOutput();
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyArray_MGET)->Range(1 << 10, 1 << 20)->Complexity();

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
    restoreOutput();
}
BENCHMARK(BM_MyArray_ConstMGET)->Range(1 << 10, 1 << 20);


// Benchmark для замены элемента по индексу
static void BM_MyArray_MRESET(benchmark::State& state) {
    MyArray<int> myArray;
    for (int i = 0; i < state.range(0); ++i) {
        myArray.MPUSH(i); // Заполняем массив
    }
    for (auto _ : state) {
        myArray.MRESET(state.range(0) / 2, 99); // Заменяем элемент в середине
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyArray_MRESET)->Range(1 << 10, 1 << 20)->Complexity();

// Benchmark для сохранения массива в файл
static void BM_MyArray_SaveToFile(benchmark::State& state) {
    MyArray<int> myArray;
    for (int i = 0; i < state.range(0); ++i) {
        myArray.MPUSH(i); // Заполняем массив
    }
    for (auto _ : state) {
        myArray.saveToFile("myarray_test.txt"); // Сохраняем массив в файл
    }
}
BENCHMARK(BM_MyArray_SaveToFile)->Range(1 << 10, 1 << 20);

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
}
BENCHMARK(BM_MyArray_LoadFromFile)->Range(1 << 10, 1 << 20);

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
BENCHMARK(BM_MyArray_Clear)->Range(1 << 10, 1 << 20);

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
BENCHMARK(BM_MyArray_Print)->Range(1 << 10, 1 << 12);

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
BENCHMARK(BM_HashMap_Insert)->Range(8, 1 << 8)->Complexity();

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
BENCHMARK(BM_HashMap_Get)->Range(8, 1 << 8)->Complexity();

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
BENCHMARK(BM_HashMap_Delete)->Range(8, 1 << 8)->Complexity();

static void BM_HashMap_SaveToFile(benchmark::State& state) {
    hashmap.clear();
    for (int i = 0; i < state.range(0); ++i) {
        hashmap.HSET("key" + std::to_string(i), i);
    }
    for (auto _ : state) {
        hashmap.saveToFile("hashmap_data.txt");
    }
}
BENCHMARK(BM_HashMap_SaveToFile)->Range(8, 1 << 8)->Complexity();

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
BENCHMARK(BM_HashMap_LoadFromFile)->Range(8, 1 << 8)->Complexity();

// ==== Benchmarks for MyVector ====

// Benchmark для метода push_back
static void BM_MyVector_PushBack(benchmark::State& state) {
    MyVector<int> vec;
    for (auto _ : state) {
        vec.push_back(42); // Добавляем элемент в конец
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyVector_PushBack)->Range(1 << 10, 1 << 20)->Complexity();

// Benchmark для метода insert
static void BM_MyVector_Insert(benchmark::State& state) {
    MyVector<int> vec;
    for (int i = 0; i < state.range(0); i++) {
        vec.push_back(42); // Заполняем вектор
    }
    for (auto _ : state) {
        vec.insert(state.range(0) / 2, 99); // Вставка в середину
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyVector_Insert)->Range(1 << 10, 1 << 20)->Complexity();

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
BENCHMARK(BM_MyVector_Erase)->Range(1 << 10, 1 << 20)->Complexity();

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
BENCHMARK(BM_MyVector_Get)->Range(1 << 10, 1 << 20)->Complexity();

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
BENCHMARK(BM_MyVector_Set)->Range(1 << 10, 1 << 20)->Complexity();

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
BENCHMARK(BM_MyVector_Resize)->Range(1 << 10, 1 << 20)->Complexity();

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
BENCHMARK(BM_MyVector_Print)->Range(1 << 10, 1 << 15)->Complexity();

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
BENCHMARK(BM_MyVector_Size)->Range(1 << 10, 1 << 20)->Complexity();

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
BENCHMARK(BM_MyVector_ConstGet)->Range(1 << 10, 1 << 20)->Complexity();

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
BENCHMARK(BM_MyVector_Iterate)->Range(1 << 10, 1 << 20)->Complexity();

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
BENCHMARK(BM_MyVector_ConstIterate)->Range(1 << 10, 1 << 20)->Complexity();

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
BENCHMARK(BM_MyVector_ModifyWithIterators)->Range(1 << 10, 1 << 20)->Complexity();

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
BENCHMARK(BM_MyVector_ForEach)->Range(1 << 10, 1 << 20)->Complexity();

// ==== Benchmarks for MyQueue ====

// Benchmark для добавления элементов в очередь
static void BM_Queue_Q_PUSH(benchmark::State& state) {
    Queue<int> queue;
    for (auto _ : state) {
        queue.Q_PUSH(42); // Добавляем элемент
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_Queue_Q_PUSH)->Range(1 << 10, 1 << 20)->Complexity();

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
BENCHMARK(BM_Queue_Q_DEL)->Range(1 << 10, 1 << 20)->Complexity();

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
BENCHMARK(BM_Queue_Q_POP)->Range(1 << 10, 1 << 20)->Complexity();

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
BENCHMARK(BM_Queue_getSize)->Range(1 << 10, 1 << 20);

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
BENCHMARK(BM_Queue_saveToFile)->Range(1 << 10, 1 << 20);

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
BENCHMARK(BM_Queue_loadFromFile)->Range(1 << 10, 1 << 20);

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
BENCHMARK(BM_Queue_clear)->Range(1 << 10, 1 << 20);

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
BENCHMARK(BM_Queue_print)->Range(1 << 10, 1 << 12);

// ==== Main Function to Run All Benchmarks ====

BENCHMARK_MAIN();

