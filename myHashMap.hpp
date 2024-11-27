#ifndef MYHASHMAP_HPP
#define MYHASHMAP_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include "myListKV.hpp"

template <typename K, typename V>
class MyHashMap {
private:
    MyList<K, V>* table; // Массив списков
    int capacity; // Вместимость хеш-таблицы

    // Простая хеш-функция
    int hash(const K& key) const {
        int hashValue = 0;
        for (char c : key) { // Простой способ для строк
            hashValue = (hashValue * 31 + c) % capacity;
        }
        return hashValue;
    }

public:
    // Конструктор
    MyHashMap(int cap = 10) : capacity(cap) {
        table = new MyList<K, V>[capacity]; // Создаем массив списков
    }

    // Деструктор
    ~MyHashMap() {
        delete[] table; // Освобождаем память
    }

    // Метод для получения элемента по ключу (HGET)
    V HGET(const K& key) {
        V value{};
        if (table[hash(key)].find(key, value)) {
            return value;
        }
        else {
            //throw std::out_of_range("Key not found");
            std::cout << "Key not found" << std::endl;
        }
    }

    // Метод для добавления элемента (HSET)
    void HSET(const K& key, const V& value) {
        V value2{};
        if(table[hash(key)].find(key, value2) == 0){
            table[hash(key)].push_back(key, value);
        }else{
            std::cout << "Not robuit" << std::endl;
        }
    }
    
    // Метод для удаления элемента по ключу (HDEL)
    void HDEL(const K& key) {
        int index = hash(key);
        V value{};
        if (table[index].find(key, value)) {  // Проверяем существование ключа
            table[index].remove(key);
        } else {
            //throw std::out_of_range("Key not found");
            std::cout << "Key not found" << std::endl;
        }
    }
    // Метод для печати хеш-таблицы
    void print() const {
        for (int i = 0; i < capacity; i++) {
            std::cout << "Bucket " << i << ": ";
            table[i].print();
        }
        std::cout << std::endl;
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file) {
            throw std::runtime_error("Unable to open file for writing");
        }
        for (int i = 0; i < capacity; i++) {
            // Проверяем, содержит ли текущий список данные
            MyList<K, V>& bucket = table[i];
            if (bucket.size() == 0) {
                continue; // Переходим к следующему списку, если данных нет
            }

            // Сохраняем все пары ключ-значение из корзины в файл
            for (int j = 0; j < bucket.size(); j++) {
                K key;
                V value;
                if (bucket.findAt(j, key, value)) { // Проверяем, что элемент найден
                    file << key << " " << value << "\n";
                }
            }
        }
        file.close();
    }


    // Загрузка хеш-таблицы из файла
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Unable to open file for reading");
        }
        clear(); // Очищаем текущую хеш-таблицу перед загрузкой

        K key;
        V value;
        while (file >> key >> value) { // Чтение ключей и значений из файла
            HSET(key, value); // Добавляем пары ключ-значение в хеш-таблицу
        }

        file.close();
    }

    // Сохранение в бинарный файл
    void saveToBinaryFile(const std::string& filename) const {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Unable to open file for writing");
        }

        file.write(reinterpret_cast<const char*>(&capacity), sizeof(capacity));

        for (int i = 0; i < capacity; i++) {
            const MyList<K, V>& bucket = table[i];

            int bucketSize = bucket.size();
            file.write(reinterpret_cast<const char*>(&bucketSize), sizeof(bucketSize));

            for (int j = 0; j < bucketSize; j++) {
                K key;
                V value;
                if (bucket.findAt(j, key, value)) {
                    if constexpr (std::is_same<K, std::string>::value) {
                        size_t keySize = key.size();
                        file.write(reinterpret_cast<const char*>(&keySize), sizeof(keySize));
                        file.write(key.c_str(), keySize);
                    } else {
                        file.write(reinterpret_cast<const char*>(&key), sizeof(key));
                    }

                    file.write(reinterpret_cast<const char*>(&value), sizeof(value));
                }
            }
        }

        file.close();
    }

    void loadFromBinaryFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Unable to open file for reading");
        }

        clear();
        delete[] table;

        file.read(reinterpret_cast<char*>(&capacity), sizeof(capacity));
        table = new MyList<K, V>[capacity];

        for (int i = 0; i < capacity; i++) {
            int bucketSize;
            file.read(reinterpret_cast<char*>(&bucketSize), sizeof(bucketSize));

            for (int j = 0; j < bucketSize; j++) {
                K key;
                V value;

                if constexpr (std::is_same<K, std::string>::value) {
                    size_t keySize;
                    file.read(reinterpret_cast<char*>(&keySize), sizeof(keySize));

                    char* buffer = new char[keySize + 1];
                    file.read(buffer, keySize);
                    buffer[keySize] = '\0';
                    key = std::string(buffer);
                    delete[] buffer;
                } else {
                    file.read(reinterpret_cast<char*>(&key), sizeof(key));
                }

                file.read(reinterpret_cast<char*>(&value), sizeof(value));
                HSET(key, value);
            }
        }

        file.close();
    }

    // Очистка хеш-таблицы
    void clear() {
        for (int i = 0; i < capacity; i++) {
            table[i].clear(); // Очищаем каждую корзину
        }
    }
};

#endif