#include <iostream>
#include "HashTable.h"
#include <cmath>


/**
 * Constructor of HashTable class initialize the arrays,the counterTAble with one because is the counter array,
 * the Table with " " cause of the table is empty.
 * @param size int of the array.
 */
HashTable::HashTable(int size) {
    Table = new std::string[size];
    counterTable= new int [size];
    for (int i = 0; i < size; ++i) {
        counterTable[i] = 1;
        Table[i] = "0"; // Filling up the table with 0's for later usage in a do while statement.
    }
}

/**The following function is essentially what Java Strings use . Since it doesnt work that well for larger strings
we implemented a second hash function to achieve a more functional program.*/
int HashTable::hashFunction1(const std::string& key, int size) {
    int hashVal = 0;
    for (char i : key) {
        hashVal = hashVal + 37 * i;
    }
    hashVal %= size;
    if (hashVal < 0)
        hashVal += size;

    return hashVal;
}

/*
 * The following function is used as the second hash function that we will incorporate in our insert algorithm, in order
to  double hash. Basically, we multiply the value from the hashFunction1 with the power of p(prime)
to the i-th index value. */
int HashTable::hashFunction2(const std::string& key, int size) {
    int hashVal = 0;
    int p = 7;
    for (int i = 0; i < key.length(); ++i) {
        hashVal = hashVal + 37 * key.at(i) * (int) pow(p, i);
    }
    hashVal %= size;
    if (hashVal < 0)
        hashVal += size;
    return hashVal;
}

//
/**
 * Function tha implementing insertion by combining the two functions for double hashing.
 * @param key string
 * @param size int
 * @return bool
 */
bool HashTable::insert(const std::string& key, int size) {
    int locationA;
    int locationB = hashFunction2(key, size);
    int counter = 1;
    locationA = hashFunction1(key, size);
    do { // rehash by incorporating the second hash function
        locationA = (locationA + locationB) % size;
        counter = counter + 1;
        //repeat until a location without a previous key is found
        if (Table[locationA] == key) break;
    } while (!(Table[locationA] == "0")  );// modulo is being used for diversity

    if (counter < 500) {
        if (Table[locationA] == "0") {
            Table[locationA] = key;
        } else
            counterTable[locationA] += 1;
        return true;
    }
    if (counter > 500) std::cout << "out of bounds" << counter;
    return false;
}

/**
 * Search method of hash table
 * @param key &string
 * @param size int size of table
 * @param counter int parameter to save the appearances of node.
 * @return bool
 */
bool HashTable::search(const std::string& key, int size, int *counter) {

    int locationA;
    int locationB = hashFunction2(key, size);
    int sum = 0;

    locationA = hashFunction1(key, size);
    do {
        locationA = (locationA + locationB) % size;
        if (Table[locationA] == key) {
            *counter = counterTable[locationA];
            return true;
        }
        sum++;
    } while (sum < 500); //

    return false;
}




