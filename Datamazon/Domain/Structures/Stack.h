#pragma once
#include "Node.h"
#include <iostream>
using namespace std;

template<typename T>
class Stack {
private:
    Node<T>* top;

public:
    Stack() { top = nullptr; }

    Node<T>* getTop() const { return top; }

    void push(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (top == nullptr) { cout << "Stack vacio" << endl; return; }
        Node<T>* temp = top;
        top = temp->next;
        delete temp;
    }

    T peek() {
        if (top == nullptr) { cout << "Stack vacio..."; return T(); }
        return top->value;
    }

    bool isEmpty() { return top == nullptr; }

    void show() {
        Node<T>* current = top;
        cout << "=== HISTORIAL DEL CARRITO ===" << endl;
        cout << "TOP" << endl;
        while (current != nullptr) {
            cout << "  -> " << current->value->getName()
                << " | S/." << current->value->getPrice() << endl;
            current = current->next;
        }
        cout << "BOTTOM" << endl;
    }

    int count() {
        int total = 0;
        Node<T>* current = top;
        while (current != nullptr) { total++; current = current->next; }
        return total;
    }

    int countRecursive(Node<T>* node) {
        if (node == nullptr) return 0;
        return 1 + countRecursive(node->next);
    }

    bool contains(int id) {
        Node<T>* current = top;
        while (current != nullptr) {
            if (current->value->getId() == id) return true;
            current = current->next;
        }
        return false;
    }

    double getTotalPrice() {
        double total = 0;
        Node<T>* current = top;
        while (current != nullptr) {
            total += current->value->getPrice();
            current = current->next;
        }
        return total;
    }

    void showTotal() {
        show();
        cout << "  TOTAL: S/." << getTotalPrice() << endl;
    }

    void clearAll() {
        clearRecursive(top);
        top = nullptr;
        cout << "Carrito vaciado." << endl;
    }

    ~Stack() {}

private:
    void clearRecursive(Node<T>* node) {
        if (node == nullptr) return;
        clearRecursive(node->next);
        delete node;
    }
};
