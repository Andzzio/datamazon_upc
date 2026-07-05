#pragma once

template <typename T, typename Key>
struct AVLNode {
    Key key;
    T value;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(Key k, T v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
};

template <typename T, typename Key>
class AVLTree {
private:
    AVLNode<T, Key>* root;

    AVLNode<T, Key>* rotateRight(AVLNode<T, Key>* y) {
        AVLNode<T, Key>* x = y->left;
        AVLNode<T, Key>* T2 = x->right;

        x->right = y;
        y->left = T2;

        int yLeftHeight = getHeight(y->left);
        int yRightHeight = getHeight(y->right);
        y->height = ((yLeftHeight > yRightHeight) ? yLeftHeight : yRightHeight) + 1;

        int xLeftHeight = getHeight(x->left);
        int xRightHeight = getHeight(x->right);
        x->height = ((xLeftHeight > xRightHeight) ? xLeftHeight : xRightHeight) + 1;

        return x;
    }

    AVLNode<T, Key>* rotateLeft(AVLNode<T, Key>* x) {
        AVLNode<T, Key>* y = x->right;
        AVLNode<T, Key>* T2 = y->left;

        y->left = x;
        x->right = T2;

        int xLeftHeight = getHeight(x->left);
        int xRightHeight = getHeight(x->right);
        x->height = ((xLeftHeight > xRightHeight) ? xLeftHeight : xRightHeight) + 1;

        int yLeftHeight = getHeight(y->left);
        int yRightHeight = getHeight(y->right);
        y->height = ((yLeftHeight > yRightHeight) ? yLeftHeight : yRightHeight) + 1;

        return y;
    }

    AVLNode<T, Key>* rotateLeftRight(AVLNode<T, Key>* node) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    AVLNode<T, Key>* rotateRightLeft(AVLNode<T, Key>* node) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    AVLNode<T, Key>* insert(AVLNode<T, Key>* node, const Key& key, const T& value) {
        if (node == nullptr) {
            return new AVLNode<T, Key>(key, value);
        }

        if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
        } else {
            node->value = value;
            return node;
        }

        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = ((leftHeight > rightHeight) ? leftHeight : rightHeight) + 1;

        int balance = getBalanceFactor(node);

        if (balance > 1 && key < node->left->key) {
            return rotateRight(node);
        }

        if (balance < -1 && key > node->right->key) {
            return rotateLeft(node);
        }

        if (balance > 1 && key > node->left->key) {
            return rotateLeftRight(node);
        }

        if (balance < -1 && key < node->right->key) {
            return rotateRightLeft(node);
        }

        return node;
    }

    T* search(AVLNode<T, Key>* node, const Key& key) {
        if (node == nullptr) return nullptr;
        if (key == node->key) return &node->value;
        if (key < node->key) return search(node->left, key);
        return search(node->right, key);
    }

    template <typename Funcion>
    void rangeSearch(AVLNode<T, Key>* node, const Key& minKey, const Key& maxKey, Funcion lambda) {
        if (node == nullptr) return;
        if (node->key > minKey) {
            rangeSearch(node->left, minKey, maxKey, lambda);
        }
        if (node->key >= minKey && node->key <= maxKey) {
            lambda(node->value);
        }
        if (node->key < maxKey) {
            rangeSearch(node->right, minKey, maxKey, lambda);
        }
    }

    void clear(AVLNode<T, Key>* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        clear(root);
    }

    void clear() {
        clear(root);
        root = nullptr;
    }

    void insert(const Key& key, const T& value) {
        root = insert(root, key, value);
    }

    T* search(const Key& key) {
        return search(root, key);
    }

    int getHeight() const {
        return getHeight(root);
    }

    int getHeight(AVLNode<T, Key>* node) const {
        if (node == nullptr) return 0;
        return node->height;
    }

    int getBalanceFactor() const {
        return getBalanceFactor(root);
    }

    int getBalanceFactor(AVLNode<T, Key>* node) const {
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    template <typename Funcion>
    void rangeSearch(const Key& minKey, const Key& maxKey, Funcion lambda) {
        rangeSearch(root, minKey, maxKey, lambda);
    }

    AVLNode<T, Key>* getRoot() const {
        return root;
    }
};
