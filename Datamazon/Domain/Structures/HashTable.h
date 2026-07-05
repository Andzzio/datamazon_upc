#pragma once
#include <iostream>
#include <string>
#include <cstdint>
#include <cstddef>

template <typename T>
struct KeyHasher {
    static size_t hash(const T& key, size_t capacity) {
        unsigned long long val = 0;
        const unsigned char* p = reinterpret_cast<const unsigned char*>(&key);
        for (size_t i = 0; i < sizeof(T); ++i) {
            val = (val * 31) + p[i];
        }
        return static_cast<size_t>((val * 2654435769U) % capacity);
    }
};

template <>
struct KeyHasher<int> {
    static size_t hash(const int& key, size_t capacity) {
        unsigned int val = static_cast<unsigned int>(key);
        return static_cast<size_t>((val * 2654435769U) % capacity);
    }
};

template <>
struct KeyHasher<const int> {
    static size_t hash(const int& key, size_t capacity) {
        unsigned int val = static_cast<unsigned int>(key);
        return static_cast<size_t>((val * 2654435769U) % capacity);
    }
};

template <>
struct KeyHasher<std::string> {
    static size_t hash(const std::string& key, size_t capacity) {
        unsigned long long h = 0;
        unsigned long long p = 31;
        unsigned long long p_pow = 1;
        unsigned long long m = 1000000009;
        for (size_t i = 0; i < key.length(); ++i) {
            unsigned char c = static_cast<unsigned char>(key[i]);
            h = (h + c * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        return static_cast<size_t>(h % capacity);
    }
};

template <>
struct KeyHasher<const std::string> {
    static size_t hash(const std::string& key, size_t capacity) {
        unsigned long long h = 0;
        unsigned long long p = 31;
        unsigned long long p_pow = 1;
        unsigned long long m = 1000000009;
        for (size_t i = 0; i < key.length(); ++i) {
            unsigned char c = static_cast<unsigned char>(key[i]);
            h = (h + c * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        return static_cast<size_t>(h % capacity);
    }
};

template <typename T>
struct KeyHasher<T*> {
    static size_t hash(T* const& key, size_t capacity) {
        uintptr_t val = reinterpret_cast<uintptr_t>(key);
        return static_cast<size_t>((val * 2654435769U) % capacity);
    }
};

template <typename T>
struct KeyHasher<const T*> {
    static size_t hash(const T* const& key, size_t capacity) {
        uintptr_t val = reinterpret_cast<uintptr_t>(key);
        return static_cast<size_t>((val * 2654435769U) % capacity);
    }
};

template <typename K, typename V>
struct HashNode {
    K key;
    V value;
    HashNode* next;
    HashNode(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
};

template <typename K, typename V>
class HashTable {
private:
    HashNode<K, V>** table;
    size_t capacity;
    size_t currentSize;

    size_t getHash(const K& key, size_t cap) const {
        return KeyHasher<K>::hash(key, cap);
    }

public:
    HashTable(size_t initialCapacity = 16) {
        capacity = initialCapacity;
        currentSize = 0;
        table = new HashNode<K, V>*[capacity];
        for (size_t i = 0; i < capacity; ++i) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        clear();
        delete[] table;
    }

    void clear() {
        for (size_t i = 0; i < capacity; ++i) {
            HashNode<K, V>* current = table[i];
            while (current != nullptr) {
                HashNode<K, V>* temp = current;
                current = current->next;
                delete temp;
            }
            table[i] = nullptr;
        }
        currentSize = 0;
    }

    void rehash() {
        size_t oldCapacity = capacity;
        capacity = capacity * 2;
        HashNode<K, V>** newTable = new HashNode<K, V>*[capacity];
        for (size_t i = 0; i < capacity; ++i) {
            newTable[i] = nullptr;
        }
        for (size_t i = 0; i < oldCapacity; ++i) {
            HashNode<K, V>* current = table[i];
            while (current != nullptr) {
                HashNode<K, V>* nextNode = current->next;
                size_t newIndex = getHash(current->key, capacity);
                current->next = newTable[newIndex];
                newTable[newIndex] = current;
                current = nextNode;
            }
        }
        delete[] table;
        table = newTable;
    }

    double getLoadFactor() const {
        if (capacity == 0) {
            return 0.0;
        }
        return static_cast<double>(currentSize) / capacity;
    }

    void insertar(const K& key, const V& value) {
        size_t index = getHash(key, capacity);
        HashNode<K, V>* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }
        HashNode<K, V>* newNode = new HashNode<K, V>(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        currentSize++;
        if (getLoadFactor() > 0.75) {
            rehash();
        }
    }

    V* buscar(const K& key) {
        size_t index = getHash(key, capacity);
        HashNode<K, V>* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return &(current->value);
            }
            current = current->next;
        }
        return nullptr;
    }

    const V* buscar(const K& key) const {
        size_t index = getHash(key, capacity);
        HashNode<K, V>* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return &(current->value);
            }
            current = current->next;
        }
        return nullptr;
    }

    HashNode<K, V>** getTable() const { return table; }
    size_t getCapacity() const { return capacity; }
};
