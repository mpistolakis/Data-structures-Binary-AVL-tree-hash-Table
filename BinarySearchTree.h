#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <string>
#include <chrono>

class BinarySearchTree {
public:
    BinarySearchTree() { root = nullptr; flag= true;}

    bool isEmpty() const { return root == nullptr; }

    void Insert(const std::string& x);

    bool search(const std::string& key, int *counter);

    void callPreorder();
    void callInorder();
    void callPostorder();

    bool Delete(const std::string& key);



protected:

private:
    struct node {
        explicit node(const std::string &data);

        node *left;
        node *right;
        std::string data;
        int counter;
    };

    node *root;

    bool printLevel(node *current, int level);

    void Inorder(node *p);

    void Preorder(node *node);

    void postorder(node *p);
    bool flag{};

    std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long long int, std::ratio<1, 1000000000>>>time;

};

#endif // BINARYSEARCHTREE_H
