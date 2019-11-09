#include <iostream>
#include <string>

#include "HashTable.h"
#include "HashEntry.h"

unsigned long stringHasher(const std::string& key) {
    unsigned long hashValue = 0;
    const char* keyBuffer = key.c_str();
    int bufferSize = sizeof(char) * key.length();

    for (int i = 0; i < bufferSize; ++i) {
        hashValue += 37 * hashValue + keyBuffer[i];
    }

    return hashValue;
}

int main() {
    HashTable<std::string, int> table;
    table.setHasher(&stringHasher);

    table.put("dog", 4);
    table.put("cow", 5);
    table.put("mouse", 14);
    table.put("cat", 45);
    table.put("giraffe", 3);
    table.put("cow", 98);

    table.dump();

    std::cout << "Key 'giraffe' is" << (table.hashKey("giraffe") ? "" : " not") << " in the table." << std::endl;

    table.remove("mouse");
    table.dump();

    try {
        int value = table["horse"];
        std::cout << "The value of key 'horse' is " << value << "." << std::endl;
    } catch(std::exception& exc) {
        std::cout << exc.what() << std::endl;
    }

    std::cout << "The value of key 'dog' is " << table["dog"] << "." << std::endl;

    return 0;
}