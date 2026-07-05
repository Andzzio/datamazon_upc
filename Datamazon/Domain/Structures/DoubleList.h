#pragma once
#include "Node.h"
#include <iostream>
using namespace std;
template<typename T>
class DoubleList
{
public:
    Node<T>* head;
    Node<T>* tail;

    class Iterator {
    private:
        Node<T>* current;
    public:
        Iterator(Node<T>* node) : current(node) {}
        
        T& operator*() { return current->value; }
        
        Iterator& operator++() {
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }

        Iterator& operator--() {
            if (current != nullptr) {
                current = current->previous;
            }
            return *this;
        }
        
        bool operator!=(const Iterator& other) const { return current != other.current; }
        bool operator==(const Iterator& other) const { return current == other.current; }
    };

    DoubleList() {
        head = tail = nullptr;
    }

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

    void addBack(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (tail == nullptr) { tail = head = newNode; return; }
        newNode->previous = tail;
        tail->next = newNode;
        tail = newNode;
    }

    void addFront(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) { head = tail = newNode; return; }
        newNode->next = head;
        head->previous = newNode;
        head = newNode;
    }

    void showFrontToBack() {
        if (head == nullptr) { cout << "Lista vacia." << endl; return; }
        Node<T>* current = head;
        while (current != nullptr) {
            current->value->show();
            current = current->next;
        }
    }

    template<typename Funcion>
    void filter(Funcion condition) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (condition(current->value)) current->value->show();
            current = current->next;
        }
    }

    void deleteById(int id) {
        if (head == nullptr) { cout << "Lista vacia." << endl; return; }
        if (head->value->getId() == id) {
            Node<T>* temp = head;
            head = head->next;
            if (head != nullptr) head->previous = nullptr;
            else tail = nullptr;
            delete temp;
            return;
        }
        Node<T>* current = head;
        while (current->next != nullptr) {
            if (current->next->value->getId() == id) {
                Node<T>* temp = current->next;
                current->next = temp->next;
                if (temp->next != nullptr) temp->next->previous = current;
                else tail = current;
                delete temp;
                return;
            }
            current = current->next;
        }
        cout << "Elemento no encontrado." << endl;
    }

    int count() {
        int total = 0;
        Node<T>* current = head;
        while (current != nullptr) { total++; current = current->next; }
        return total;
    }

    bool contains(int id) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->value->getId() == id) return true;
            current = current->next;
        }
        return false;
    }

    T getById(int id) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->value->getId() == id) return current->value;
            current = current->next;
        }
        return nullptr;
    }

    void showBackToFront() {
        if (tail == nullptr) { cout << "Lista vacia." << endl; return; }
        Node<T>* current = tail;
        cout << "=== LISTA INVERSA ===" << endl;
        while (current != nullptr) {
            current->value->show();
            current = current->previous;
        }
    }

    void sortByPrice() {
        if (head == nullptr) return;
        bool swapped;
        do {
            swapped = false;
            Node<T>* current = head;
            while (current->next != nullptr) {
                if (current->value->getPrice() > current->next->value->getPrice()) {
                    T temp = current->value;
                    current->value = current->next->value;
                    current->next->value = temp;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
        cout << "Productos ordenados por precio (menor a mayor)." << endl;
    }

    void sortByName() {
        if (head == nullptr) return;
        bool swapped;
        do {
            swapped = false;
            Node<T>* current = head;
            while (current->next != nullptr) {
                if (current->value->getName() > current->next->value->getName()) {
                    T temp = current->value;
                    current->value = current->next->value;
                    current->next->value = temp;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
        cout << "Lista ordenada alfabeticamente." << endl;
    }

    void mergeSort() {
        head = mergeSortHelper(head);
        Node<T>* current = head;
        while (current && current->next) current = current->next;
        tail = current;
        cout << "Productos ordenados con Merge Sort (precio asc)." << endl;
    }

    int countRecursive(Node<T>* node) {
        if (node == nullptr) return 0;
        return 1 + countRecursive(node->next);
    }

    T searchRecursive(Node<T>* node, int id) {
        if (node == nullptr) return nullptr;
        if (node->value->getId() == id) return node->value;
        return searchRecursive(node->next, id);
    }

private:
    Node<T>* mergeSortHelper(Node<T>* node) {
        if (node == nullptr || node->next == nullptr) return node;
        Node<T>* mid = getMiddle(node);
        Node<T>* half = mid->next;
        mid->next = nullptr;
        if (half) half->previous = nullptr;
        Node<T>* left = mergeSortHelper(node);
        Node<T>* right = mergeSortHelper(half);
        return merge(left, right);
    }

    Node<T>* getMiddle(Node<T>* node) {
        Node<T>* slow = node;
        Node<T>* fast = node->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    Node<T>* merge(Node<T>* a, Node<T>* b) {
        if (!a) return b;
        if (!b) return a;
        if (a->value->getPrice() <= b->value->getPrice()) {
            a->next = merge(a->next, b);
            if (a->next) a->next->previous = a;
            a->previous = nullptr;
            return a;
        }
        else {
            b->next = merge(a, b->next);
            if (b->next) b->next->previous = b;
            b->previous = nullptr;
            return b;
        }
    }
};
