#ifndef BST_H
#define BST_H

#include <iostream>
#include <queue>

template <typename T>
class BST {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        
        Node(T val) : data(val), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    int nodeCount;
    
    // Helper functions
    Node* insertHelper(Node* node, T value);
    void inorderHelper(Node* node, std::queue<T>& q);
    void destroyTree(Node* node);
    void displayHelper(Node* node, int depth);
    int heightHelper(Node* node);
    
public:
    BST();
    ~BST();
    
    void insert(T value);
    void inorderToQueue(std::queue<T>& q);
    void display();
    int size() const;
    int height();
    bool isEmpty() const;
};

// Constructor
template <typename T>
BST<T>::BST() : root(nullptr), nodeCount(0) {}

// Destructor
template <typename T>
BST<T>::~BST() {
    destroyTree(root);
}

// Destroy tree helper
template <typename T>
void BST<T>::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Insert value into BST
template <typename T>
void BST<T>::insert(T value) {
    root = insertHelper(root, value);
    nodeCount++;
}

// Insert helper (recursive)
template <typename T>
typename BST<T>::Node* BST<T>::insertHelper(Node* node, T value) {
    if (node == nullptr) {
        return new Node(value);
    }
    
    if (value < node->data) {
        node->left = insertHelper(node->left, value);
    } else {
        node->right = insertHelper(node->right, value);
    }
    
    return node;
}

// Perform inorder traversal and store in queue (ascending order)
template <typename T>
void BST<T>::inorderToQueue(std::queue<T>& q) {
    inorderHelper(root, q);
}

// Inorder traversal helper
template <typename T>
void BST<T>::inorderHelper(Node* node, std::queue<T>& q) {
    if (node != nullptr) {
        inorderHelper(node->left, q);
        q.push(node->data);
        inorderHelper(node->right, q);
    }
}

// Display tree structure
template <typename T>
void BST<T>::display() {
    if (root == nullptr) {
        std::cout << "Tree is empty.\n";
        return;
    }
    std::cout << "\nTree Structure (rotated 90° clockwise):\n";
    std::cout << "========================================\n";
    displayHelper(root, 0);
    std::cout << "========================================\n";
}

// Display helper (visual tree representation)
template <typename T>
void BST<T>::displayHelper(Node* node, int depth) {
    if (node != nullptr) {
        displayHelper(node->right, depth + 1);
        for (int i = 0; i < depth; i++) {
            std::cout << "    ";
        }
        std::cout << node->data << std::endl;
        displayHelper(node->left, depth + 1);
    }
}

// Get size
template <typename T>
int BST<T>::size() const {
    return nodeCount;
}

// Get height
template <typename T>
int BST<T>::height() {
    return heightHelper(root);
}

// Height helper
template <typename T>
int BST<T>::heightHelper(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = heightHelper(node->left);
    int rightHeight = heightHelper(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Check if empty
template <typename T>
bool BST<T>::isEmpty() const {
    return root == nullptr;
}

#endif