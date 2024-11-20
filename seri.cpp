#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "serial.hpp"
#include <string>
#include "myListKV.hpp"
#include "myArray.hpp"
#include "myStack.hpp"
#include "myHashMap.hpp"

static void seriHashMapToBinary(){
    try {
        // Создаем хеш-таблицу
        MyHashMap<std::string, int> map(10);

        // Добавляем данные в хеш-таблицу
        map.HSET("Alice", 25);
        map.HSET("Bob", 30);
        map.HSET("Charlie", 35);

        // Печатаем текущую таблицу
        std::cout << "Initial hash map:" << std::endl;
        map.print();

        // Сериализация в бинарный файл
        std::string binaryFile = "hashmap.bin";
        map.saveToFile(binaryFile);
        std::cout << "Hash map serialized to binary file: " << binaryFile << std::endl;

        // Создаем новую хеш-таблицу и загружаем из файла
        MyHashMap<std::string, int> newMap(10);
        newMap.loadFromFile(binaryFile);

        // Печатаем загруженную таблицу
        std::cout << "Hash map deserialized from binary file:" << std::endl;
        newMap.print();

        // Проверка значения по ключу
        std::cout << "Value for key 'Alice': " << newMap.HGET("Alice") << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    seriHashMapToBinary();
}