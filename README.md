# thierdLaba

## Описание
Краткое описание вашего проекта.

## Содержание
- [Установка](#установка)
- [Как запустить с помощью make coverage](#как-запустить-с-помощью-make-coverage)
- [Установка Google Benchmark на Linux](#установка-google-benchmark-на-linux)

## Установка
Шаги по установке и настройке вашего проекта:
1. Клонируйте репозиторий:
    ```sh
    git clone https://github.com/Discorre/thierdLaba.git
    ```
2. Перейдите в директорию проекта:
    ```sh
    cd thierdLaba
    ```
3. Дополнительные инструкции по установке.

## Как запустить с помощью make coverage
Для запуска покрытия кода с помощью make выполните следующие шаги:
1. Соберите проект с покрытием:
    ```sh
    make coverage
    ```
2. Отчет о покрытии будет создан в `coverage_report/thierdLab/index.html`.

## Установка Google Benchmark на Linux
Для установки Google Benchmark на Linux выполните следующие шаги:
1. Установите необходимые пакеты:
    ```sh
    sudo apt install -y git cmake g++ libbenchmark-dev
    ```
2. Клонируйте репозиторий Google Benchmark:
    ```sh
    git clone https://github.com/google/benchmark.git
    ```
3. Перейдите в директорию проекта и создайте директорию сборки:
    ```sh
    cd benchmark
    mkdir build && cd build
    ```
4. Запустите CMake для подготовки сборки:
    ```sh
    cmake .. -DCMAKE_BUILD_TYPE=Release
    ```
5. Соберите и установите библиотеку:
    ```sh
    make
    sudo make install
    ```
