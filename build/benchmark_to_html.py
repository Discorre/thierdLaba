import json

def json_to_html(json_file, html_file):
    with open(json_file, 'r') as f:
        data = json.load(f)

    with open(html_file, 'w') as f:
        # Начало HTML с CSS стилями
        f.write("""
        <html>
        <head>
            <title>Benchmark Report</title>
            <style>
                body { font-family: Arial, sans-serif; background-color: #f4f4f9; color: #333; }
                h1 { text-align: center; color: #4CAF50; }
                table { width: 80%; margin: 20px auto; border-collapse: collapse; }
                th, td { padding: 12px; border: 1px solid #ddd; text-align: center; }
                th { background-color: #4CAF50; color: white; }
                tr:nth-child(even) { background-color: #f2f2f2; }
                .code-block { background-color: #f9f9f9; border: 1px solid #ddd; padding: 10px; margin: 20px auto; width: 80%; }
            </style>
        </head>
        <body>
            <h1>Benchmark Report</h1>
        """)

        # Таблица с результатами бенчмарка
        f.write("<table>")
        f.write("<tr><th>Benchmark</th><th>Iterations</th><th>Time (ns)</th><th>CPU (ns)</th><th>Bytes Processed</th><th>Items Processed</th></tr>")

        for benchmark in data["benchmarks"]:
            name = benchmark["name"]
            iterations = benchmark["iterations"]
            time = benchmark["real_time"]
            cpu_time = benchmark["cpu_time"]
            bytes_processed = benchmark.get("bytes_per_second", "N/A")
            items_processed = benchmark.get("items_per_second", "N/A")
            
            f.write(f"<tr><td>{name}</td><td>{iterations}</td><td>{time}</td><td>{cpu_time}</td><td>{bytes_processed}</td><td>{items_processed}</td></tr>")

        f.write("</table>")

        # Вставка кода тестируемого класса с подсветкой
        code = """
#ifndef MYLISTKV_HPP
#define MYLISTKV_HPP

#include <iostream>

template <typename K, typename V>
class MyList {
private:
    struct Node {
        K key;
        V value;
        Node* next;
        Node(K key, V value) : key(key), value(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int length;

public:
    MyList() : head(nullptr), tail(nullptr), length(0) {}
    ~MyList() { clear(); }

    void push_back(const K& key, const V& value) {
        Node* newNode = new Node(key, value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

    bool find(const K& key, V& value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->key == key) {
                value = current->value;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool findAt(int index, K& key, V& value) const {
        if (index < 0 || index >= length) return false;
        Node* current = head;
        for (int i = 0; i < index; i++) current = current->next;
        key = current->key;
        value = current->value;
        return true;
    }

    bool remove(const K& key) {
        Node* current = head;
        Node* prev = nullptr;
        while (current != nullptr) {
            if (current->key == key) {
                if (prev != nullptr) prev->next = current->next;
                else head = current->next;
                if (current == tail) tail = prev;
                delete current;
                length--;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << "{" << current->key << ": " << current->value << "} ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    int size() const { return length; }
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        length = 0;
    }
};

#endif
"""
        f.write(f"<div class='code-block'><pre>{code}</pre></div>")

        # Закрытие HTML
        f.write("</body></html>")

# Использование скрипта
json_to_html("result.json", "benchmark_report.html")
