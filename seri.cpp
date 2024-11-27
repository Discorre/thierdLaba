#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include "myArray.hpp"
#include "myVector.hpp"
#include "myFullBinaryTree.hpp"
#include "myQueue.hpp"
#include "myStack.hpp"
#include "mySinglyLinkedList.hpp" 
#include "myDoublyLinkedList.hpp"
#include "myHashMap.hpp"

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

static void seriFullBinaryTreeToBinary(){
    FullBinaryTree<int> tree;

    // Добавляем элементы в дерево
    tree.TINSERT(10);
    tree.TINSERT(20);
    tree.TINSERT(30);
    tree.TINSERT(40);
    tree.TINSERT(50);

    // Выводим оригинальное дерево
    std::cout << "Original tree (in-order): ";
    tree.print();

    const std::string filename = "tree_data.bin";

    // Сериализация
    tree.saveToBinaryFile(filename);
    std::cout << "Tree has been serialized to " << filename << std::endl;

    // Десериализация
    FullBinaryTree<int> loadedTree;
    loadedTree.loadFromBinaryFile(filename);

    // Проверяем десериализованное дерево
    std::cout << "Deserialized tree (in-order): ";
    loadedTree.print();


    return;
}

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

static void seriQueueToBinary(){
    try {
        // Создаём очередь и заполняем её
        Queue<std::string> q;
        q.Q_PUSH("10");
        q.Q_PUSH("20");
        q.Q_PUSH("30");
        q.Q_PUSH("40");
        q.Q_PUSH("50");

        std::cout << "Original queue: ";
        q.print();

        // Сериализуем очередь в файл
        q.saveToFile("queue_data.bin");
        std::cout << "Queue has been serialized to queue_data.bin\n";

        // Создаём новую очередь и загружаем данные из файла
        Queue<std::string> newQueue;
        newQueue.loadFromFile("queue_data.bin");

        std::cout << "Deserialized queue: ";
        newQueue.print();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return;
}

static void seriStackToBinary(){
    try {
        MyStack<std::string> stack;

        // Добавляем элементы в стек
        stack.SPUSH("Hello");
        stack.SPUSH("World");
        stack.SPUSH("Stack");
        stack.SPUSH("Serialization");

        std::cout << "Original stack: ";
        stack.print();

        // Сохраняем стек в файл
        stack.saveToFileBinary("stack_data.bin");
        std::cout << "Stack has been serialized to stack_data.bin\n";

        // Создаем новый стек и загружаем данные из файла
        MyStack<std::string> newStack;
        newStack.loadFromBinaryFile("stack_data.bin");

        std::cout << "Deserialized stack: ";
        newStack.print();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return;
}

static void seriSinglyLinkedListToBinary(){
    MySinglyLinkedList<std::string> list;

    // Добавляем элементы в список
    list.LPUSHTAIL("Hello");
    list.LPUSHTAIL("World");
    list.LPUSHTAIL("Linked");
    list.LPUSHTAIL("List");
    list.LPUSHTAIL("Serialization");

    std::cout << "Original list: ";
    list.print();

    // Сохраняем список в файл
    try {
        list.saveToBinaryFile("list_data.bin");
        std::cout << "List has been serialized to list_data.bin\n";
    } catch (const std::exception& e) {
        std::cerr << "Error during serialization: " << e.what() << "\n";
        return;
    }

    // Загружаем список из файла
    MySinglyLinkedList<std::string> loadedList;
    try {
        loadedList.loadFromBinaryFile("list_data.bin");
        std::cout << "Deserialized list: ";
        loadedList.print();
    } catch (const std::exception& e) {
        std::cerr << "Error during deserialization: " << e.what() << "\n";
        return;
}

    return;
}

static void seriDoublyLinkedListToBinary(){
    try{
        MyDoublyLinkedList<std::string> list;

        // Добавляем данные
        list.LPUSHTAIL("Alice");
        list.LPUSHTAIL("Bob");
        list.LPUSHTAIL("Charlie");

        std::cout << "Original dlist: ";
        list.print();

        // Сериализация
        list.saveToBinaryFile("dlist_data.bin");
        std::cout << "Dlist has been serialized to dlist_data.bin\n";

        // Десериализация
        MyDoublyLinkedList<std::string> loadedList;
        loadedList.loadFromBinaryFile("dlist_data.bin");

        std::cout << "Deserialized dlist: ";
        loadedList.print();

        return;
    } catch (const std::exception e){
        std::cerr << "Error during deserialization: " << e.what() << "\n";
        return;
    }
}

static void seriHashMapToBinary(){
    try{
        MyHashMap<std::string, int> hashMap(5);

        hashMap.HSET("Alice", 30);
        hashMap.HSET("Bob", 25);
        hashMap.HSET("Charlie", 35);

        std::cout << "Original hashmap:" << std::endl;
        hashMap.print();

        std::cout << "HashMap has been serialized to data.bin" << std::endl;
        hashMap.saveToBinaryFile("data.bin");

        MyHashMap<std::string, int> loadedHashMap;
        loadedHashMap.loadFromBinaryFile("data.bin");

        std::cout << "Loaded hashmap:" << std::endl;
        loadedHashMap.print();

        return;
    }
    catch(const std::exception e){
        std::cerr << "Error during deserialization: " << e.what() << "\n";
        return;
    }
}

int main() {
    system("clear");
    seriArrayToBinary();
    std::cout << std::endl;
    seriVectorToBinary();
    std::cout << std::endl;
    seriFullBinaryTreeToBinary();
    std::cout << std::endl;
    seriQueueToBinary();
    std::cout << std::endl;
    seriStackToBinary();
    std::cout << std::endl;
    seriSinglyLinkedListToBinary();
    std::cout << std::endl;
    seriDoublyLinkedListToBinary();
    std::cout << std::endl;
    seriHashMapToBinary();


    return 0;
}