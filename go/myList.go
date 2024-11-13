package main

import (
	"fmt"
)

type node[K comparable, V any] struct {
	key   K
	value V
	next  *node[K, V]
}

type MyList[K comparable, V any] struct {
	head   *node[K, V]
	tail   *node[K, V]
	length int
}

// Конструктор
func NewMyList[K comparable, V any]() *MyList[K, V] {
	return &MyList[K, V]{}
}

// Добавление пары ключ-значение в конец списка
func (l *MyList[K, V]) PushBack(key K, value V) {
	newNode := &node[K, V]{key: key, value: value}
	if l.tail == nil {
		l.head = newNode
		l.tail = newNode
	} else {
		l.tail.next = newNode
		l.tail = newNode
	}
	l.length++
}

// Поиск элемента по ключу
func (l *MyList[K, V]) Find(key K) (V, bool) {
	current := l.head
	var zeroValue V
	for current != nil {
		if current.key == key {
			return current.value, true
		}
		current = current.next
	}
	return zeroValue, false
}

// Получение элемента по индексу
func (l *MyList[K, V]) FindAt(index int) (K, V, bool) {
	if index < 0 || index >= l.length {
		var zeroK K
		var zeroV V
		return zeroK, zeroV, false
	}
	current := l.head
	for i := 0; i < index; i++ {
		current = current.next
	}
	return current.key, current.value, true
}

// Удаление элемента по ключу
func (l *MyList[K, V]) Remove(key K) bool {
	current := l.head
	var prev *node[K, V]
	for current != nil {
		if current.key == key {
			if prev != nil {
				prev.next = current.next
			} else {
				l.head = current.next
			}
			if current == l.tail {
				l.tail = prev
			}
			l.length--
			return true
		}
		prev = current
		current = current.next
	}
	return false
}

// Печать элементов списка
func (l *MyList[K, V]) Print() {
	current := l.head
	for current != nil {
		fmt.Printf("{%v: %v} ", current.key, current.value)
		current = current.next
	}
	fmt.Println()
}

// Получение длины списка
func (l *MyList[K, V]) Size() int {
	return l.length
}

// Очистка списка
func (l *MyList[K, V]) Clear() {
	l.head = nil
	l.tail = nil
	l.length = 0
}
