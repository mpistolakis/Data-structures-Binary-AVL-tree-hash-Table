//
// Created by George on 6/13/2020.
//

#include "AVLTree.h"
#include <algorithm>
#include <iostream>

/**
 * Function that find the max height for one node.
 * @param temp avl_node
 * @return int  the max height of right and left children's
 */
int AVLTree::height(avl_node *temp) {

    if (temp == nullptr)return 0;
    else {
        int Lheight = (temp->left) ? temp->left->height : 0;// if the  node is not null
        int Rheight = (temp->right) ? temp->right->height : 0;
        return std::max(Rheight, Lheight) + 1; // return the max plus one for the current node.
    }


}

/**
 * These function find the different between heights of left and right children's.
 * @param temp avl_node
 * @return int
 */
int AVLTree::diff(avl_node *temp) {
    int l_height = height(temp->left);  // find the height for each child.
    int r_height = height(temp->right);
    int b_factor = l_height - r_height;
    return b_factor;

}

/**
 * These function make the right rotation of subtree with root y .
 * @param y the unbalanced node.
 * @return avl_node new root of subtree.
 */
AVLTree::avl_node *AVLTree::rr_rotation(avl_node *y) {

    avl_node *x = y->left;
    avl_node *T2 = x->right;

    // rotation
    x->right = y;
    y->left = T2;

    // Update heights of rotated nodes
    y->height = std::max(height(y->left),
                         height(y->right)) + 1;
    x->height = std::max(height(x->left),
                         height(x->right)) + 1;

    // Return new root
    return x;
}


/**
 * These function make the left rotation of subtree with root x .
 * @param x the unbalanced node.
 * @return avl_node new root of subtree.
 */
AVLTree::avl_node *AVLTree::ll_rotation(avl_node *x) {
    avl_node *y = x->right;
    avl_node *T2 = y->left;
    //  rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(height(x->left),
                         height(x->right)) + 1;
    y->height = std::max(height(y->left),
                         height(y->right)) + 1;

    // Return new root
    return y;

}


/**
 * Function to check if the
 * @param temp avl_node is unbalanced and to do the rotations if needed.
 * @param key string
 * @return the new root of subtree.
 */
AVLTree::avl_node *AVLTree::balance(avl_node *temp, const std::string& key) {

    int bal_factor = diff(temp); //find the difference of height's.
    // If this node becomes unbalanced, then  there are four cases.

    // Left Left Case
    if (bal_factor > 1 && key.compare(temp->left->data) < 0) {
        return rr_rotation(temp);
    }
    // Right Right Case
    if (bal_factor < -1 && key.compare(temp->right->data) > 0) {
        return ll_rotation(temp);
    }
    // Left Right Case
    if (bal_factor > 1 && key.compare(temp->left->data) > 0) {
        temp->left = ll_rotation(temp->left);
        return rr_rotation(temp);

    }
    // Right Left Case
    if (bal_factor < -1 && key.compare(temp->right->data) < 0) {
        temp->right = rr_rotation(temp->right);
        return ll_rotation(temp);
    }
    //Return the unchanged node.
    return temp;
}

/**
 *  Recursive function to insert a string
 * in the subtree rooted with node .
 * @param node struct avl_node
 * @param value string
 * @return returns the new root.
 */
AVLTree::avl_node *AVLTree::insert(avl_node *node, const std::string& value) {
    if (node == nullptr) { // If node is null initialise it.
        node = new avl_node;
        node->data = value;
        node->left = nullptr;
        node->right = nullptr;
        node->counter = 1;
        node->height = 1;
        return node;
    } else if (value.compare(node->data) <
               0) { // else move inside the tree until you find the node or the position it should be.
        node->left = insert(node->left, value);

    } else if (value.compare(node->data) > 0) {
        node->right = insert(node->right, value);

    } else if (value == node->data) { node->counter = node->counter + 1; } //If node exist already, update the counter.


    node->height = height(node);
    //    Check the balance factor of this ancestor node.
    return balance(node, value);

}

/**
 * Function to print Inorder
// traversal of the tree.
 * @param p avl_node struct.
 */
void AVLTree::inorder(avl_node *tree) {
    if (tree == nullptr)
        return;
    inorder(tree->left);
    std::cout << tree->data << "  ";
    inorder(tree->right);
}

/**
 * Function to print postOrder
// traversal of the tree.
 * @param p avl_node struct.
 */
void AVLTree::postorder(avl_node *tree) {
    if (tree == nullptr)
        return;
    postorder(tree->left);
    postorder(tree->right);
    std::cout << tree->data << "  ";
}

/**
 * Function to print preOrder
// traversal of the tree.
 * @param p avl_node struct.
 */
void AVLTree::preorder(avl_node *tree) {
    if (tree == nullptr)
        return;
    std::cout << tree->data << "  ";
    preorder(tree->left);
    preorder(tree->right);

}

/**
 * Function to find the smallest node of right subtree.
 * @param t root of subtree.
 * @return struct avl_node ,the smallest node.
 */
AVLTree::avl_node *AVLTree::findMin(avl_node *t) {
    if (t == nullptr) return nullptr;
    else if (t->left == nullptr) return t; // if element traverse on max left then return
    else return findMin(t->left); // or recursively traverse max left
}

/**
 *Recursive function to delete a node
 *with given key.
 * @param t avl_node the root.
 * @param x string the node for deletion.
 * @return avl_node the new root.
 */
AVLTree::avl_node *AVLTree::remove(avl_node *t, const std::string& x) {
    avl_node *temp;

    if (t == nullptr) return nullptr;
        // searching element,go left if it is smaller  than current node else go right.
    else if (x.compare(t->data) < 0) t->left = remove(t->left, x);
    else if (x.compare(t->data) > 0) t->right = remove(t->right, x);

    else if (t->counter > 1) { // when you find the node ,deleted if only the counter is equal to 1.
        t->counter = t->counter - 1;

    }
        // element has 2 children
    else if (t->left && t->right) {
        temp = findMin(t->right); // find the smallest node in the right subtree.
        t->data = temp->data;
        t->right = remove(t->right, t->data);
    }
        // if element has 1 or 0 child
    else {
        temp = t;
        if (t->left == nullptr) t = t->right;
        else if (t->right == nullptr) t = t->left;
        delete temp;
    }
    if (t == nullptr) return t;

    return balance(t, x); //check for unbalanced node at every change
}

/**
 * @return the current root.
 */
AVLTree::avl_node *AVLTree::getroot() {
    return this->root;
}

/**
 * Function to set root
 * @param r the new root
 * @return bool true if the r is not null.
 */
bool AVLTree::setRooot(avl_node *r) {
    if (r) // if new root is not null.
        this->root = r;
    else return false;

    return true;

}

/**
 * Function to print levelOrder
 * traversal of the tree.
 * @param current  avl_node root.
 * @param level int .
 * @return bool
 */
bool AVLTree::display(avl_node *current, int level) {
    if (current == nullptr)
        return false;

    if (level == 1) {
        std::cout << current->data << " ";

        // return true if at-least one node is present at given level
        return true;
    }

    bool left = display(current->left, level - 1);
    bool right = display(current->right, level - 1);

    return left || right;
}

/**
 * Loop function to find a specific node.
 * @param key string
 * @param counter int
 * @return bool
 */
bool AVLTree::search(const std::string& key, int *counter) {
    avl_node *current = root;
    while (current != nullptr) {

        if (key.compare(current->data) < 0)current = current->left;
        else if (key.compare(current->data) > 0) current = current->right;
        else if (key == current->data) {
            *counter = current->counter;
            return true;
        }
    }
    *counter = 0;
    return false;
}

/**
 * function that checks if the tree is AVl,based on balance of nodes.
 * @param Root avl_node
 * @param height int
 * @return bool
 */
bool AVLTree::isBalanced(avl_node *Root, int *height) {

    /* lh --> Height of left subtree
    rh --> Height of right subtree */
    int lh = 0, rh = 0;

    /* l will be true if left subtree is balanced
    and r will be true if right subtree is balanced */
    int l, r;

    if (Root == nullptr) {
        *height = 0;
        return true;
    }
    /* Get the heights of left and right subtrees in lh and rh
    And store the returned values in l and r */
    l = isBalanced(Root->left, &lh);
    r = isBalanced(Root->right, &rh);

    /* Height of current node is max of heights of left and
    right subtrees plus 1*/
    *height = (lh > rh ? lh : rh) + 1;

    /* If difference between heights of left and right
    subtrees is more than 2 then this node is not balanced
    so return 0 */
    if (abs(lh - rh) >= 2)
        return false;

        /* If this node is balanced and left and right subtrees
        are balanced then return true */
    else
        return l && r;

}




