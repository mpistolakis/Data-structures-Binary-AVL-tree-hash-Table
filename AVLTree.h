//
// Created by George on 6/13/2020.
//

#ifndef UNTITLED5_AVLTREE_H
#define UNTITLED5_AVLTREE_H


#include <string>




class AVLTree {

public:
    struct avl_node {
        std::string data;
        int counter;
        struct avl_node *left;
        struct avl_node *right;
        int height;


    };
    static int height(avl_node *);

    static int diff(avl_node *);

    static avl_node *rr_rotation(avl_node *);

    static avl_node *ll_rotation(avl_node *);

    static avl_node *balance(avl_node *, const std::string&);

    avl_node *insert(avl_node *, const std::string&);

    bool display(avl_node *, int);

    void inorder(avl_node *);

    void preorder(avl_node *);

    void postorder(avl_node *);

    avl_node *remove(avl_node *t, const std::string& x);

    avl_node *findMin(avl_node *);

    avl_node *getroot();

    bool setRooot(avl_node *r);

    bool isBalanced(avl_node *Root, int *height);

    bool search(const std::string& key, int *counter);

    AVLTree() {
        root = nullptr;
    }

private:
    avl_node *root;

};


#endif //UNTITLED5_AVLTREE_H
