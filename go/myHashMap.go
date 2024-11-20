package main

import (
	"errors"
	"fmt"
	"os"
	 "encoding/gob"

)

type MyHashMap[K comparable, V any] struct {
	Table    []*MyList[K, V] // Поменяли table на Table
	Capacity int              // Поменяли capacity на Capacity
}

// Конструктор
func NewMyHashMap[K comparable, V any](capacity int) *MyHashMap[K, V] {
	hm := &MyHashMap[K, V]{Capacity: capacity}
	hm.Table = make([]*MyList[K, V], capacity)
	for i := 0; i < capacity; i++ {
		hm.Table[i] = NewMyList[K, V]()
	}
	return hm
}



// Хеш-функция
func (hm *MyHashMap[K, V]) hash(key K) int {
	hashValue := 0
	keyStr := fmt.Sprintf("%v", key)
	for _, c := range keyStr {
		hashValue = (hashValue*31 + int(c)) % hm.Capacity
	}
	return hashValue
}

// HGET - получение элемента по ключу
func (hm *MyHashMap[K, V]) HGET(key K) (V, error) {
	index := hm.hash(key)
	value, found := hm.Table[index].Find(key)
	if !found {
		var zeroValue V
		return zeroValue, errors.New("key not found")
	}
	return value, nil
}

// HSET - добавление элемента
func (hm *MyHashMap[K, V]) HSET(key K, value V) {
	index := hm.hash(key)
	if _, found := hm.Table[index].Find(key); !found {
		hm.Table[index].PushBack(key, value)
	} else {
		fmt.Println("Key already exists")
	}
}

// HDEL - удаление элемента по ключу
func (hm *MyHashMap[K, V]) HDEL(key K) error {
	index := hm.hash(key)
	if !hm.Table[index].Remove(key) {
		return errors.New("key not found")
	}
	return nil
}

// Печать хеш-таблицы
func (hm *MyHashMap[K, V]) Print() {
	for i, list := range hm.Table {
		fmt.Printf("Bucket %d: ", i)
		list.Print()
	}
}

// Сохранение в файл
func (hm *MyHashMap[K, V]) SaveToFile(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()
	for i := 0; i < hm.Capacity; i++ {
		for j := 0; j < hm.Table[i].Size(); j++ {
			key, value, ok := hm.Table[i].FindAt(j)
			if ok {
				file.WriteString(fmt.Sprintf("%v %v\n", key, value))
			}
		}
	}
	return nil
}

// Загрузка из файла
func (hm *MyHashMap[K, V]) LoadFromFile(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()
	hm.Clear()
	var key K
	var value V
	for {
		_, err := fmt.Fscanf(file, "%v %v\n", &key, &value)
		if err != nil {
			break
		}
		hm.HSET(key, value)
	}
	return nil
}

// Очистка хеш-таблицы
func (hm *MyHashMap[K, V]) Clear() {
	for i := 0; i < hm.Capacity; i++ {
		hm.Table[i].Clear()
	}
}

// SaveToBinaryFile сохраняет MyHashMap в бинарный файл
func (hm *MyHashMap[K, V]) SaveToBinaryFile(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	encoder := gob.NewEncoder(file)
	err = encoder.Encode(hm)
	if err != nil {
		return err
	}
	return nil
}

// LoadFromBinaryFile загружает MyHashMap из бинарного файла
func (hm *MyHashMap[K, V]) LoadFromBinaryFile(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	decoder := gob.NewDecoder(file)
	err = decoder.Decode(hm)
	if err != nil {
		return err
	}
	return nil
}
