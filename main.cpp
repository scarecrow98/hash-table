#include <iostream>
#include <string>

template<typename K, typename V>
class HashEntry {
private:
    K key;
    V value;
    HashEntry* next;
public:
    HashEntry(const K& key, V& value)
    : key(key), value(value), next(nullptr){
    }

    template<typename, typename> friend class HashTable;
};

template<typename K, typename V>
class HashTable {
private:
    int capacity = 10;
    int size = 0;
    HashEntry<K, V>** entries;

    unsigned int hash(const K& key) const {
        unsigned long hashValue = 0;
        const char* keyBlock = (char *)&key;
        unsigned int blockSize = sizeof(K);

        for (int i = 0; i < blockSize; i++) {
            hashValue += 37 * hashValue + keyBlock[i];
        }

        return hashValue % capacity;
    }
public:
    HashTable() {
        entries = new HashEntry<K, V>*[capacity];
        for (int i = 0; i < capacity; i++) {
            entries[i] = nullptr;
        }
    }

    void put(K key, V value) {
        unsigned int index = hash(key);
        std::cout << "hashed index for " << key << " is " << index << std::endl;

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

        curr = prev;
        curr->next = new HashEntry<K, V>(key, value);
        size++;
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

};

int main() {
    std::cout << "Hello, World!" << std::endl;
    HashTable<const char *, int> table;
    table.put("macska", 4);
    table.put("elefánt", 5);
    table.put("elefánt", 6);
    table.put("kutya", 12);
    table.put("cica", 4);
    table.put("egér", 34);


    table.dump();

    return 0;
}