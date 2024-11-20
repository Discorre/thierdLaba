package main

import (
	"fmt"
	"os"
	"testing"
	"encoding/gob"
	"github.com/stretchr/testify/assert"
	"strconv"
)

func init() {
	gob.Register(&MyHashMap[string, int]{})
	gob.Register(&MyList[string, int]{})
}


func BenchmarkHSET(b *testing.B) {
	hashMap := NewMyHashMap[string, int](1000)
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		hashMap.HSET(fmt.Sprintf("key%d", i), i)
	}
}

func BenchmarkHGET(b *testing.B) {
	hashMap := NewMyHashMap[string, int](1000)
	for i := 0; i < 1000; i++ {
		hashMap.HSET(fmt.Sprintf("key%d", i), i)
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		_, _ = hashMap.HGET(fmt.Sprintf("key%d", i%1000))
	}
}

func BenchmarkHDEL(b *testing.B) {
	hashMap := NewMyHashMap[string, int](1000)
	for i := 0; i < 1000; i++ {
		hashMap.HSET(fmt.Sprintf("key%d", i), i)
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		_ = hashMap.HDEL(fmt.Sprintf("key%d", i%1000))
	}
}

func BenchmarkSaveToFile(b *testing.B) {
	hashMap := NewMyHashMap[string, int](1000)
	for i := 0; i < 1000; i++ {
		hashMap.HSET(fmt.Sprintf("key%d", i), i)
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		_ = hashMap.SaveToFile(fmt.Sprintf("testFiles/benchmark_test_%d.txt", i))
	}
}

func BenchmarkLoadFromFile(b *testing.B) {
	hashMap := NewMyHashMap[string, string](1000)
	for i := 0; i < 1000; i++ {
		hashMap.HSET(fmt.Sprintf("key%d", i), strconv.Itoa(i))
	}
	_ = hashMap.SaveToFile("benchmark_test.txt")
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		newHashMap := NewMyHashMap[string, int](1000)
		_ = newHashMap.LoadFromFile("benchmark_test.txt")
	}
}

func BenchmarkPrint(b *testing.B) {
	hashMap := NewMyHashMap[string, string](1000)
	for i := 0; i < 1000; i++ {
		hashMap.HSET(fmt.Sprintf("key%d", i), strconv.Itoa(i))
	}

	// Перенаправляем вывод в никуда, чтобы не засорять консоль
	old := os.Stdout
	os.Stdout, _ = os.Open(os.DevNull)
	defer func() { os.Stdout = old }()

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		hashMap.Print()
	}
}

func BenchmarkMyHashMap_Exception(b *testing.B) {
	hashMap := NewMyHashMap[string, int](10)
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		// Test HSET with nil value
		hashMap.HSET(fmt.Sprintf("key%d", i), -1)
		// Test HGET with non-existent key
		_, _ = hashMap.HGET(fmt.Sprintf("nonexistent_key%d", i))
		// Test HDEL with non-existent key
		_ = hashMap.HDEL(fmt.Sprintf("nonexistent_key%d", i))
	}

	old := os.Stdout
	os.Stdout, _ = os.Open(os.DevNull)
	defer func() { os.Stdout = old }()

	hashMap.HSET("key1", 100)
	
}

func BenchmarkMyList_Exception(b *testing.B) {
    list := NewMyList[int, int]()
    b.ResetTimer()
    for i := 0; i < b.N; i++ {
        list.PushBack(100, i)
		list.Remove(-101)
        _, _, _ = list.FindAt(-101)
    }
}

func BenchmarkMyHashMap_Serialize(b *testing.B) {
	// Создаем хеш-таблицу и добавляем в нее данные
	hm := NewMyHashMap[string, string](1000)
	for i := 0; i < 1000; i++ {
		hm.HSET("key"+strconv.Itoa(i), strconv.Itoa(i))
	}

	// Бенчмарк для метода SaveToBinaryFile
	b.ResetTimer() // Сбрасываем таймер для учета только времени сериализации
	for i := 0; i < b.N; i++ {
		err := hm.SaveToBinaryFile("hashmap.bin") // Сериализация в файл
		assert.NoError(b, err, "Expected no error during SaveToBinaryFile")
	}
}

func BenchmarkMyHashMap_Deserialize(b *testing.B) {
	// Создаем хеш-таблицу и сохраняем ее в бинарный файл
	hm := NewMyHashMap[string, string](1000)
	for i := 0; i < 1000; i++ {
		hm.HSET("key"+strconv.Itoa(i), strconv.Itoa(i))
	}
	err := hm.SaveToBinaryFile("testFiles/hashmap.bin")
	if err != nil {
		b.Fatal("Error saving hashmap:", err)
	}

	// Бенчмарк для метода LoadFromBinaryFile
	b.ResetTimer() // Сбрасываем таймер для учета только времени десериализации
	for i := 0; i < b.N; i++ {
		err := hm.LoadFromBinaryFile("testFiles/hashmap.bin") // Десериализация из файла
		assert.NoError(b, err, "Expected no error during LoadFromBinaryFile")
	}
}