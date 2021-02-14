
#ifndef UNTITLED5_HASHTABLE_H
#define UNTITLED5_HASHTABLE_H
#include <iostream>
#include "string"

class HashTable {

    static int hashFunction1(const std::string& , int size);

    static int hashFunction2(const std::string& , int size);

public:

    explicit HashTable(int size);



    bool insert(const std::string&, int size);

    bool search(const std::string&, int, int *);


private:
    std::string *Table;
    int *counterTable;

};


#endif //UNTITLED5_HASHTABLE_H
