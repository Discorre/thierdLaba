package main
 

import (
    "fmt"
)


func main() {
	hm := NewMyHashMap[string, string](10)
	hm.HSET("one", "1")
	hm.HSET("two", "2")
	hm.HSET("three", "3")

	// Сохранение в бинарный файл
	err := hm.SaveToBinaryFile("hashmap.bin")
	if err != nil {
		fmt.Println("Error saving to binary file:", err)
		return
	}

	// Очистка хеш-таблицы
	hm.Clear()

	// Загрузка из бинарного файла
	err = hm.LoadFromBinaryFile("hashmap.bin")
	if err != nil {
		fmt.Println("Error loading from binary file:", err)
		return
	}

	// Печать хеш-таблицы
	hm.Print()
}