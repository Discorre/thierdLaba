#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

template <typename T>
class MyVector {
private:
    T* data;        // Указатель на массив элементов
    int capacity;   // Текущая емкость массива
    int length;     // Текущая длина массива

public:
    // Конструктор по умолчанию
    MyVector(int size = 10) : capacity(10), length(0) {
        data = new T[capacity];
    }

    // Деструктор
    ~MyVector() {
        delete[] data;
    }

    // Метод для добавления элемента в конец массива
    void push_back(const T& element) {
        if (length == capacity) {
            resize();
        }
        data[length++] = element;
    }

    // Метод для добавления элемента по индексу
    void insert(int index, const T& element) {
        if (index < 0 || index > length) {
            throw std::out_of_range("Index out of range");
        }
        if (length == capacity) {
            resize();
        }
        for (int i = length; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = element;
        length++;
    }

    // Метод для удаления элемента по индексу
    void erase(int index) {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }
        for (int i = index; i < length - 1; ++i) {
            data[i] = data[i + 1];
        }
        length--;
    }

    // Метод для получения элемента по индексу
    T& get(int index) {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Константная версия метода get
    const T& get(int index) const {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Метод для замены элемента по индексу
    void set(int index, const T& element) {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }
        data[index] = element;
    }

    // Увеличение емкости массива (bin)
    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i < length; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

    // Метод для получения текущей длины массива
    int size() const {
        return length;
    }

    // Метод для чтения всех элементов массива
    void print() const {
        for (int i = 0; i < length; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    // Сохранение в бинарный файл
    void saveToBinaryFile(const std::string& filename) const {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file for writing");
        }
        file.write(reinterpret_cast<const char*>(&length), sizeof(length));
        for (int i = 0; i < length; ++i) {
            size_t str_size = data[i].size();
            file.write(reinterpret_cast<const char*>(&str_size), sizeof(str_size));
            file.write(data[i].c_str(), str_size);
        }
        file.close();
    }

    // Загрузка из бинарного файла
    void loadFromBinaryFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file for reading");
        }
        // Read the length of the vector
        file.read(reinterpret_cast<char*>(&length), sizeof(length));
        if (length > capacity) {
            capacity = length;
            T* newData = new T[capacity];
            delete[] data;
            data = newData;
        }
        for (int i = 0; i < length; ++i) {
            size_t str_size;
            file.read(reinterpret_cast<char*>(&str_size), sizeof(str_size));
            data[i].resize(str_size);
            file.read(reinterpret_cast<char*>(data[i].data()), str_size);
        }
        file.close();
    }

    // Метод begin() для работы с диапазоном
    T* begin() {
        return data;
    }

    // Метод end() для работы с диапазоном
    T* end() {
        return data + length;
    }

    // Константные версии методов begin() и end()
    const T* begin() const {
        return data;
    }

    const T* end() const {
        return data + length;
    }
};

#endif