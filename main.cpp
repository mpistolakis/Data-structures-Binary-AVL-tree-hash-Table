#include <iostream>
#include <fstream>
#include <sstream>
#include "BinarySearchTree.h"
#include "AVLTree.h"
#include "chrono"
#include "HashTable.h"


using namespace std;

/**
 * In the main method we insert the words from input file to all structures  */
int main() {


    ifstream file("inputfile");

    string *wordsFromQ;
    int sizeOfQ = 1000;    // the the number of words that will search later
    int sizeOfTable = 23167;
    wordsFromQ = new string[sizeOfQ];

    AVLTree avlTree;
    BinarySearchTree BstTree;
    HashTable hash(sizeOfTable);


    int index = 0;//indexes of array wordsFromQ
    int lineCounter = 0;

    string lines;
    string token;
    while (std::getline(file, lines)) {
        int i = 0, k = 0;
        lineCounter++;
        while (i < lines.length()) {  //int this loop we we separate the words from special contracts from each line.

            if ((lines[i] >= 'a' && lines[i] <= 'z') ||
                (lines[i] >= 'A' && lines[i] <= 'Z')) { //If this char is a word from alphabet we save it.
                basic_string<char> a;
                a = lines[i];
                token.insert(k, a); // insert every valid char.
                k++;
            } else {
                if (k >
                    0) { // when a string interrupted by a special key and the variable k is bigger than zero,that means tha we have a word

                    if (lineCounter > 5000) { // we save one word every 10 lines.
                        if (index < sizeOfQ) {
                            wordsFromQ[index] = token;
                            index++;
                        }
                    }
                    //insert the string word.
                    BstTree.Insert(token);
                    avlTree.setRooot(avlTree.insert(avlTree.getroot(), token));
                    hash.insert(token, sizeOfTable);

                    token.clear();
                    k = 0; //k  becomes zero the string "token" is empty.
                }
            }
            if (i + 1 == lines.length()) {  // when the line changes and we have kept a word on string token.
                BstTree.Insert(token);
                avlTree.setRooot(avlTree.insert(avlTree.getroot(), token));
                hash.insert(token, sizeOfTable);
                token.clear();
                k = 0;

            }

            i++;
        }

    }

/** The following pieces in the comments are the search for each structure separately and the time required for each,
 * search words  from wordsFromQ pool with size.
 */

    /** Binary Search tree  */
    int count;
    auto BstStart = std::chrono::high_resolution_clock::now();
    for (int l = 0; l < sizeOfQ; ++l) {
        if (BstTree.search(wordsFromQ[l], &count))
        std::cout<<"The word '"<<wordsFromQ[l]<<"' exists in the text "<<count<<" times"<<endl;
    }
    auto BStStop = std::chrono::high_resolution_clock::now();
    auto BstTime = std::chrono::duration_cast<std::chrono::milliseconds>(BStStop - BstStart);

        cout << "search in Binary tree of "<< sizeOfQ<< " words end in "<< BstTime.count() << " milliseconds" << endl;

     /** AVL tree  */

//    int counter = 0;
//    int counterOfSearch = 0;
//    auto AvlStart = std::chrono::high_resolution_clock::now();
//
//    for (int n = 0; n < sizeOfQ; ++n) {
//        if (avlTree.search(wordsFromQ[n], &counter)) {
//             std::cout<<"The word '"<<wordsFromQ[n]<<"' exists in the text "<<counter<<" times"<<endl;
//             counterOfSearch++;
//        }
//
//    }
//    auto AvlStop = std::chrono::high_resolution_clock::now();
//    auto avlTime = std::chrono::duration_cast<std::chrono::milliseconds>(AvlStop - AvlStart);
//        cout << "search in AVL tree of "<< sizeOfQ<< " words end in " << avlTime.count() << " milliseconds" << endl;

    /** hash TAble */

//    int hashCounter;
//    int counterOfHashSearch = 0;
//    auto HAshStart = std::chrono::high_resolution_clock::now();
//
//    for (int m = 0; m < sizeOfQ; ++m) {
//        if (hash.search(wordsFromQ[m], sizeOfTable, &hashCounter))
//        std::cout<<"The word '"<<wordsFromQ[m]<<"' exists in the text "<<hashCounter<<" times"<<endl;
//
//    }
//    auto HAshStop = std::chrono::high_resolution_clock::now();
//
//    auto HAshTime = std::chrono::duration_cast<std::chrono::milliseconds>(HAshStop - HAshStart);
//
//    cout << "search in hashTable of "<< sizeOfQ<< " words end in "<< HAshTime.count() << " milliseconds  " << endl;

/** compare the results of each structure */
    int v = 0, a = 0, b = 0;
    int wordCounter = 0;

    for (int j = 0; j < sizeOfQ; ++j) {
        hash.search(wordsFromQ[j], sizeOfTable, &v);
        avlTree.search(wordsFromQ[j], &a);
        BstTree.search(wordsFromQ[j], &b);
        if (a == b && b == v) { // run the following code to see the results
//            cout << "avl counter = " << a << " | bst counter = " << b << " | hash table counter = " << v
//                 << " | for the word : " << wordsFromQ[j] << endl;
            wordCounter++;
        } else cout << wordsFromQ[j] << "counter mismatch !!!!!! " << a << "  " << b << " " << v << endl;
        //cout<<"a= "<<a<<" b= "<<b<<" v="<<v<<"       "<<wordsFromQ[j]<<endl;
    }
    if (wordCounter == sizeOfQ)
        cout << "all structures have the same results !!" << endl;


    return 0;
}