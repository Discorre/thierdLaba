package main

import (
	"errors"
	"fmt"
	"os"

)

type MyHashMap[K comparable, V any] struct {
	table    []*MyList[K, V]
	capacity int
}

// Конструктор
func NewMyHashMap[K comparable, V any](capacity int) *MyHashMap[K, V] {
	hm := &MyHashMap[K, V]{capacity: capacity}
	hm.table = make([]*MyList[K, V], capacity)
	for i := 0; i < capacity; i++ {
		hm.table[i] = NewMyList[K, V]()
	}
	return hm
}



// Хеш-функция
func (hm *MyHashMap[K, V]) hash(key K) int {
	hashValue := 0
	keyStr := fmt.Sprintf("%v", key)
	for _, c := range keyStr {
		hashValue = (hashValue*31 + int(c)) % hm.capacity
	}
	return hashValue
}

// HGET - получение элемента по ключу
func (hm *MyHashMap[K, V]) HGET(key K) (V, error) {
	index := hm.hash(key)
	value, found := hm.table[index].Find(key)
	if !found {
		var zeroValue V
		return zeroValue, errors.New("key not found")
	}
	return value, nil
}

// HSET - добавление элемента
func (hm *MyHashMap[K, V]) HSET(key K, value V) {
	index := hm.hash(key)
	if _, found := hm.table[index].Find(key); !found {
		hm.table[index].PushBack(key, value)
	} else {
		fmt.Println("Key already exists")
	}
}

// HDEL - удаление элемента по ключу
func (hm *MyHashMap[K, V]) HDEL(key K) error {
	index := hm.hash(key)
	if !hm.table[index].Remove(key) {
		return errors.New("key not found")
	}
	return nil
}

// Печать хеш-таблицы
func (hm *MyHashMap[K, V]) Print() {
	for i, list := range hm.table {
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
	for i := 0; i < hm.capacity; i++ {
		for j := 0; j < hm.table[i].Size(); j++ {
			key, value, ok := hm.table[i].FindAt(j)
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
	for i := 0; i < hm.capacity; i++ {
		hm.table[i].Clear()
	}
}
