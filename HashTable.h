#ifndef HASH_TABLE_HASHTABLE_H
#define HASH_TABLE_HASHTABLE_H

#include <iostream>
#include "HashEntry.h"

template<typename K, typename V>
class HashTable {
private:
    int capacity = 10;
    int size = 0;
    HashEntry<K, V>** entries;
    typedef unsigned long(*Hasher)(const K&);
    Hasher hasherFunction = nullptr;

public:
    HashTable() {
        entries = new HashEntry<K, V>*[capacity];
        for (int i = 0; i < capacity; i++) {
            entries[i] = nullptr;
        }
    }

    void setHasher(Hasher hasherFunction) {
        this->hasherFunction = hasherFunction;
    };

    void put(K key, V value) {
        unsigned long index = (*hasherFunction)(key) % capacity;
//        std::cout << "hashed index for " << key << " is " << index << std::endl;

        //if the slot is empty, just create the new entry there with the given key and value
        if (entries[index] == nullptr) {
            entries[index] = new HashEntry<K, V>(key, value);
            return;
        }

        //slot is not empty, there is at least one entry
        //now we need to find an entry with the given key and update that entry with the given value,
        //or add a new entry at the end of the linked list in the slot
        HashEntry<K, V>* prev = nullptr;
        HashEntry<K, V>* curr = entries[index];

        while (curr) {
            if (curr->key == key) {
                curr->value = value;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        prev->next = new HashEntry<K, V>(key, value);
        size++;
    }

    void remove(const K& key) {
        unsigned long index = (*hasherFunction)(key) % capacity;
        HashEntry<K,V>* curr = entries[index];

        if (!curr) {
            return;
        }
        HashEntry<K,V>* prev = nullptr;

        while(curr && curr->key != key) {
            prev = curr;
            curr = curr->next;
        }

        if (!curr) {
            return;
        }

        if (!prev) {
            entries[index] = curr->next;
        } else {
            prev->next = curr->next;
        }
        free(curr);
    }

    bool hashKey(const K& key) const {
        unsigned long index = (*hasherFunction)(key) % capacity;

        HashEntry<K,V>* entry = entries[index];
        if (!entry) {
            return false;
        }

        while (entry && entry->key != key) {
            entry = entry->next;
        }

        return entry != nullptr;
    }

    const V& operator [](const K& key) const {
        unsigned long index = (*hasherFunction)(key) % capacity;

        HashEntry<K,V>* entry = entries[index];
        if (!entry) {
            throw KeyNotFoundException();
        }

        while(entry && entry->key != key) {
            entry = entry->next;
        }

        if (!entry) {
            throw KeyNotFoundException();
        }

        return entry->value;
    }

    void dump() const {
        for (int i = 0; i < capacity; i++) {
            HashEntry<K, V>* entry = entries[i];
            std::cout << "Bucket (" << i << ".): ";
            while (entry) {
                std::cout << entry->key << "-->" << entry->value << " ; ";
                entry = entry->next;
            }
            std::cout << std::endl;
        }
    }

    class KeyNotFoundException : public std::exception {
    public:
        const char* what() const noexcept override {
            return "The given key is not in the table!";
        }
    };
};

#endif //HASH_TABLE_HASHTABLE_H
