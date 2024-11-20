package main

import (
	"fmt"
)

type MyList[K comparable, V any] struct {
	Head *Node[K, V]
	Tail *Node[K, V]
	Length int
}

type Node[K comparable, V any] struct {
	Key   K
	Value V
	Next  *Node[K, V]
}

// Конструктор
func NewMyList[K comparable, V any]() *MyList[K, V] {
	return &MyList[K, V]{}
}

// Добавление пары ключ-значение в конец списка
func (l *MyList[K, V]) PushBack(key K, value V) {
	newNode := &Node[K, V]{Key: key, Value: value}
	if l.Tail == nil {
		l.Head = newNode
		l.Tail = newNode
	} else {
		l.Tail.Next = newNode
		l.Tail = newNode
	}
	l.Length++
}

// Поиск элемента по ключу
func (l *MyList[K, V]) Find(key K) (V, bool) {
	current := l.Head
	var zeroValue V
	for current != nil {
		if current.Key == key {
			return current.Value, true
		}
		current = current.Next
	}
	return zeroValue, false
}

// Получение элемента по индексу
func (l *MyList[K, V]) FindAt(index int) (K, V, bool) {
	if index < 0 || index >= l.Length {
		var zeroK K
		var zeroV V
		return zeroK, zeroV, false
	}
	current := l.Head
	for i := 0; i < index; i++ {
		current = current.Next
	}
	return current.Key, current.Value, true
}

// Удаление элемента по ключу
func (l *MyList[K, V]) Remove(key K) bool {
	current := l.Head
	var prev *Node[K, V]
	for current != nil {
		if current.Key == key {
			if prev != nil {
				prev.Next = current.Next
			} else {
				l.Head = current.Next
			}
			if current == l.Tail {
				l.Tail = prev
			}
			l.Length--
			return true
		}
		prev = current
		current = current.Next
	}
	return false
}

// Печать элементов списка
func (l *MyList[K, V]) Print() {
	current := l.Head
	for current != nil {
		fmt.Printf("{%v: %v} ", current.Key, current.Value)
		current = current.Next
	}
	fmt.Println()
}

// Получение длины списка
func (l *MyList[K, V]) Size() int {
	return l.Length
}

// Очистка списка
func (l *MyList[K, V]) Clear() {
	l.Head = nil
	l.Tail = nil
	l.Length = 0
}
