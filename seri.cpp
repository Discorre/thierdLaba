#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include "myArray.hpp"
#include "myVector.hpp"

static void seriArrayToBinary(){
    try{
        MyArray<std::string> arr(10);

        arr.MPUSH("Alice");
        arr.MPUSH("Bob");
        arr.MPUSH("Charlie");

        std::cout << "Initial array:" << std::endl;
        arr.print();

        // Сериализация в бинарный файл
        std::string binaryFile = "seriTest/binArr.bin";
        arr.saveToBinaryFile(binaryFile);
        //arr.saveToFile(binaryFile);
        std::cout << "Array serialized to binary file: " << binaryFile << std::endl;

        arr.print();
        // Создаем новую хеш-таблицу и загружаем из файла
        MyArray<std::string> newArr(10);
        newArr.loadFromBinaryFile(binaryFile);
        //newArr.loadFromFile(binaryFile);

        // Печатаем загруженную таблицу
        std::cout << "Array deserialized from binary file:" << std::endl;
        newArr.print();

        // Проверка значения по ключу
        std::cout << "Value for key 'Alice': " << newArr.MGET(0) << std::endl;
    }
    catch(const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

static void seriArrayToFile(){}

static void seriVectorToBinary(){
    try {
        MyVector<std::string> vec;
        vec.push_back("Alice");
        vec.push_back("Bob");
        vec.push_back("Charlie");
        std::cout << "Original vector: ";
        vec.print();

        vec.saveToBinaryFile("seriTest/binVec.bin");

        MyVector<std::string> vec2;
        vec2.loadFromBinaryFile("seriTest/binVec.bin");
        std::cout << "Loaded vector: ";
        vec2.print();

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    
}

int main() {
    system("clear");
    seriArrayToBinary();
    std::cout << std::endl;
    seriVectorToBinary();
    return 0;
}