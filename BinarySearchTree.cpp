#include "BinarySearchTree.h"
#include <string>
#include <iostream>
#include <chrono>

/**
 * constructor for struct node.
 * @param data string.
 */
BinarySearchTree::node::node(const std::string &data) {
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
    this->counter = 1;
}
/**
 * Loop function to insert a new node.
 * @param d string.
 */
void BinarySearchTree::Insert(const std::string& d) {

    node *p = new node(d);
    node *parent;

    parent = nullptr;
    if (isEmpty()) root = p; // If the tree is empty , p is obviously gonna be the root.
    else {
        node *curr;
        curr = root;
        bool pExists = true; // Guard value.
        while (curr) {
            parent = curr; //Assign the current element to the parent node.
            if (p->data.compare(curr->data) > 0)
                curr = curr->right;//If p->data > curr->data , assign current to the right node.
            else if (p->data.compare(curr->data) < 0)
                curr = curr->left; // Similarly , the element will go to the left node.
            else if (p->data == curr->data) { // in case that the element is already in the tree,
                delete p; // we delete the element that would be otherwise inserted
                pExists = false;
                curr->counter = curr->counter + 1; // and we obviously increment the node's counter value by 1
                break;
            }
        }
        if (pExists) { // Lastly , compare the parent and data  and assign accordingly
            if (p->data.compare(parent->data) < 0)
                parent->left = p;
            else if (p->data.compare(parent->data) > 0)
                parent->right = p;
        }
    }
}
/**
 * Loop function to delete a node from the tree.
 * @param key string.
 * @return bool depending on whether the deletion was successful or not.
 */
bool BinarySearchTree::Delete(const std::string& key) {

    node *current = root; // Starting out with the root,
    node *parent = nullptr; // a pointer to store the parent node of the current node.

    while (current != nullptr && current->data == key) {
        parent = current;
        if (current->data.compare(key) > 0)
            current = current->left;
        else if (current->data.compare(key) < 0)
            current = current->right;
    } // Find the key element and set its parent pointer.

    if (current == nullptr) return false; // return if it's not found .

    if (current->counter > 1) {
        current->counter = current->counter - 1;
        return true;
    }   // Checking the counter before deletion.

    // ------1st case : node has no children------
    if (current->left == nullptr && current->right == nullptr) {
        if (current == root) {
            //If BST has only a root node, delete it and return.
            delete root;
            return true;
        }
        //Setting the node parent's left or right child to null in case the key node is not the root of the tree.
        if (parent->left == current)
            parent->left = nullptr;
        else
            parent->right = nullptr;
        delete current;
        return true; //Delete the key node and return.
    } else if (current->left == nullptr || current->right == nullptr) {
        //------2nd case : node has only one child------
        node *child;
        //Locating the child node properly.
        if (current->right)
            child = current->right;
        else
            child = current->left;

        if (current == root) {
            root = child;
        } else {
            if (parent->left == current)
                parent->left = child;
            else
                parent->right = child; //Set the parent node to its child node if the node to be deleted is not the root.
        }
        delete current;
        return true;
    } else { // ------3rd case : node has two children------
        node *b = current->left;
        node *parentOf_b = current;
        /*The idea is to find the successor (or predecessor) of the given node . Then we delete that from the tree
         *and in the end we end up replacing the node with the said successor (or predecessor). */
        while (b->right) {
            parentOf_b = b;
            b = b->right;
        }
        if (current == root) {
            b->right = root->right;
            root = b;
            if (parentOf_b != current) {
                parentOf_b->right = nullptr;
                b->left = current->left;
            }
            delete current;
            return true;
        } else if (parent->right == current)
            parent->right = b;
        else
            parent->left = b;

        if (parentOf_b == current) {
            b->right = current->right;
            delete current;
            return true;
        } else {
            b->left = current->left;
            b->right = current->right;
            parentOf_b->right = nullptr;
            delete current;
            return true;
        }
    }
}
/**
 * Function to search an element - node in tree.
 * @param key string the node.
 * @param counter int.needed to save the appearances of node.
 * @return bool.
 */
bool BinarySearchTree::search(const std::string& key, int *counter) {
    node *current = root;
    while (current != nullptr) {

        // If the key is less than the current node , traverse the left subtree , else to the right one .
        if (current->data.compare(key) > 0)current = current->left;
        else if (current->data.compare(key) < 0) current = current->right;
        else if (current->data == key) {
            *counter = current->counter;
            return true;
        }
    }
    *counter = 0;
    return false;
}



/**
 * Function to print levelOrder
 * traversal of the tree.
 * @param p node struct.
 */
bool BinarySearchTree::printLevel(BinarySearchTree::node *current, int level) {
    if (current == nullptr)
        return false;

    if (level == 1) {
        std::cout << current->data << " ";

        // return true if at least one node is present at the given level
        return true;
    }

    bool left = printLevel(current->left, level - 1);
    bool right = printLevel(current->right, level - 1);

    return left || right;
}
/**
 * Function to print Inorder
// traversal of the tree.
 * @param p node struct.
 */
void BinarySearchTree::Inorder(struct node *p) {
    if (p != nullptr) {
        Inorder(p->left);
        std::cout << " " << p->data << " ";
        Inorder(p->right);
    } else return;
}
/**
 * Function to print preorder
// traversal of the tree.
 * @param p node struct.
 */
void BinarySearchTree::Preorder(BinarySearchTree::node *node) {

    if (node == nullptr)
        return;

    //Output the node data
    std::cout << node->data << " " << std::endl;


    //Recur
    Preorder(node->left);

    /* now recur on right subtree */
    Preorder(node->right);
}


/**
 * Function to print postOrder
// traversal of the tree.
 * @param p node struct.
 */

void BinarySearchTree::postorder(struct node *p) {
    if (p == nullptr)
        return;

    // first recur on left subtree
    postorder(p->left);

    // then recur on right subtree
    postorder(p->right);

    // now deal with the node
    std::cout << p->data << " ";
}

void BinarySearchTree::callPreorder() {
   Preorder(root);
}

void BinarySearchTree::callInorder() {
  Inorder(root);
}

void BinarySearchTree::callPostorder() {
    postorder(root);
}




