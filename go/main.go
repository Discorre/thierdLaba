package main

/*func main(){
	myMap := NewMyHashMap[string, int](10)
	myMap.HSET("key1", 100)
	myMap.HSET("key2", 200)
	myMap.HSET("key3", 300)
	myMap.HSET("key4", 400)
	myMap.HSET("4eyk", 500)
	myMap.Print()
}

/*func TestMyHashMap(t *testing.T) {
	hashMap := NewMyHashMap[string, int](10)

	// Test HSET and HGET
	hashMap.HSET("key1", 100)
	value, err := hashMap.HGET("key1")
	assert.NoError(t, err)
	assert.Equal(t, 100, value)

	// Test HDEL
	err = hashMap.HDEL("key1")
	assert.NoError(t, err)
	_, err = hashMap.HGET("key1")
	assert.Error(t, err)

	// Test SaveToFile and LoadFromFile
	err = hashMap.SaveToFile("test_hashmap.txt")
	assert.NoError(t, err)

	hashMap.Clear()
	err = hashMap.LoadFromFile("test_hashmap.txt")
	assert.NoError(t, err)
	value, err = hashMap.HGET("key1")
	assert.Error(t, err)
}*/