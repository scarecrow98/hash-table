#ifndef HASH_TABLE_HASHENTRY_H
#define HASH_TABLE_HASHENTRY_H

template<typename K, typename V>
class HashEntry {
private:
    K key;
    V value;
    HashEntry* next;
public:
    HashEntry(K& key, V& value)
            : key(key), value(value), next(nullptr){
    }

    const K& getKey() const {
        return key;
    }

    const V& getValue() const {
        return value;
    }

    template<typename, typename> friend class HashTable;
};

#endif //HASH_TABLE_HASHENTRY_H
