#ifndef MYSTACK_HPP
#define MYSTACK_HPP

template <typename T>
class MyStack {
private:
    T* data;        // Указатель на массив элементов
    int capacity;   // Текущая емкость массива
    int length;     // Текущая длина стека

public:
    // Конструктор по умолчанию
    MyStack() : capacity(10), length(0) {
        data = new T[capacity];  // Инициализация массива с начальной емкостью
    }

    // Деструктор
    ~MyStack() {
        delete[] data; // Освобождение выделенной памяти
    }

    // Метод для добавления элемента в стек
    void SPUSH(const T& element) {
        if (length == capacity) {
            resize(); // Увеличение емкости, если стек полон
        }
        data[length++] = element; // Добавление элемента и увеличение длины
    }

    // Метод для удаления элемента из стека
    void SDEL() {
        if (length == 0) {
            //throw std::out_of_range("Stack is empty");
            std::cout << "Stack is empty. Cannot delete element." << std::endl;
        }
        length--; // Уменьшение длины (удаление последнего элемента)
    }

    // Метод для чтения (получения) верхнего элемента стека
    T& SPOP() {
        if (length == 0) {
            //throw std::out_of_range("Stack is empty");
            std::cout << "Stack is empty. Cannot get element." << std::endl;
            return data[0]; // Возвращаем первый элемент (для const-версии)
        }
        return data[length - 1]; // Возвращаем верхний элемент
    }

    // Метод для получения текущего размера стека
    int size() const {
        return length; // Возвращаем длину стека
    }

    // Метод для увеличения емкости стека
    void resize() {
        capacity *= 2; // Увеличиваем емкость в два раза
        T* newData = new T[capacity]; // Создаем новый массив с новой емкостью
        for (int i = 0; i < length; i++) {
            newData[i] = data[i]; // Копируем старые данные в новый массив
        }
        delete[] data; // Освобождаем старый массив
        data = newData; // Перенаправляем указатель на новый массив
    }

    // Метод для печати элементов стека
    void print() const {
        if (length == 0) {
            std::cout << "Stack is empty." << std::endl;
            return;
        }
        std::cout << "Stack elements: ";
        for (int i = 0; i < length; i++) {
            std::cout << data[i] << " "; // Выводим каждый элемент
        }
        std::cout << std::endl;
    }

    // Сохранение стека в файл
    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file) {
            //throw std::runtime_error("Unable to open file for writing");
            std::cout << "Unable to open file for writing. Stack will not be saved." << std::endl;
            return;
        }
        for (int i = 0; i < length; i++) {
            file << data[i] << "\n"; // Сохраняем каждый элемент
        }
        file.close();
    }

    // Загрузка стека из файла
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            //throw std::runtime_error("Unable to open file for reading");
            std::cout << "Unable to open file for reading. Stack will not be loaded." << std::endl;
            return;
        }
        clear(); // Очищаем текущий стек перед загрузкой
        T value;
        while (file >> value) {
            SPUSH(value); // Добавляем каждый считанный элемент в стек
        }
        file.close();
    }

    void saveToFileBinary(const std::string& filename) const {
        std::ofstream file(filename, std::ios::binary); // Бинарный режим
        if (!file) {
            throw std::runtime_error("Unable to open file for writing");
        }
        file.write(reinterpret_cast<const char*>(&length), sizeof(length)); // Сохраняем длину стека
        for (int i = 0; i < length; ++i) {
            if constexpr (std::is_same_v<T, std::string>) {
                size_t strLength = data[i].size();
                file.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength)); // Сохраняем длину строки
                file.write(data[i].c_str(), strLength); // Сохраняем содержимое строки
            } else {
                file.write(reinterpret_cast<const char*>(&data[i]), sizeof(data[i])); // Сохраняем элемент
            }
        }
        file.close();
    }

    void loadFromBinaryFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary); // Бинарный режим
        if (!file) {
            throw std::runtime_error("Unable to open file for reading");
        }
        clear(); // Очищаем стек перед загрузкой
        int newLength;
        file.read(reinterpret_cast<char*>(&newLength), sizeof(newLength)); // Читаем длину стека
        for (int i = 0; i < newLength; ++i) {
            T value;
            if constexpr (std::is_same_v<T, std::string>) {
                size_t strLength;
                file.read(reinterpret_cast<char*>(&strLength), sizeof(strLength)); // Читаем длину строки
                char* buffer = new char[strLength + 1];
                file.read(buffer, strLength); // Читаем содержимое строки
                buffer[strLength] = '\0';
                value = std::string(buffer);
                delete[] buffer;
            } else {
                file.read(reinterpret_cast<char*>(&value), sizeof(value)); // Читаем элемент
            }
            SPUSH(value);
        }
        file.close();
    }


    // Очистка стека
    void clear() {
        delete[] data; // Освобождаем память
        data = new T[capacity]; // Создаем новый массив с той же емкостью
        length = 0; // Сбрасываем длину
    }
};

#endif