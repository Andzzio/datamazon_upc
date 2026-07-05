#pragma once

template <typename T, typename Key>
struct BSTNode {
    Key key;
    T value;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Key k, T val) : key(k), value(val), left(nullptr), right(nullptr) {}
};

template <typename T, typename Key>
class BST {
private:
    BSTNode<T, Key>* root;

    void clear(BSTNode<T, Key>* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    BSTNode<T, Key>* insert(BSTNode<T, Key>* node, Key key, T value) {
        if (node == nullptr) {
            return new BSTNode<T, Key>(key, value);
        }
        if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
        }
        return node;
    }

    T find(BSTNode<T, Key>* node, Key key) const {
        if (node == nullptr) {
            return T();
        }
        if (key == node->key) {
            return node->value;
        }
        if (key < node->key) {
            return find(node->left, key);
        } else {
            return find(node->right, key);
        }
    }

    template <typename Func>
    void inOrderTraversal(BSTNode<T, Key>* node, Func func) const {
        if (node != nullptr) {
            inOrderTraversal(node->left, func);
            func(node->value);
            inOrderTraversal(node->right, func);
        }
    }

    int countNodes(BSTNode<T, Key>* node) const {
        if (node == nullptr) {
            return 0;
        }
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    T findMin(BSTNode<T, Key>* node) const {
        if (node == nullptr) {
            return T();
        }
        if (node->left == nullptr) {
            return node->value;
        }
        return findMin(node->left);
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        clear(root);
    }

    void clear() {
        clear(root);
        root = nullptr;
    }

    void insert(Key key, T value) {
        root = insert(root, key, value);
    }

    T find(Key key) const {
        return find(root, key);
    }

    template <typename Func>
    void inOrderTraversal(Func func) const {
        inOrderTraversal(root, func);
    }

    BSTNode<T, Key>* getRoot() const { return root; }

    int countNodes() const {
        return countNodes(root);
    }

    T findMin() const {
        return findMin(root);
    }
};
