#pragma once
#include "Node.h"
#include <iostream>

template <typename T> class SimpleList {
public:
  Node<T> *head;

  class Iterator {
  private:
    Node<T> *current;

  public:
    Iterator(Node<T> *node) : current(node) {}

    T &operator*() { return current->value; }

    Iterator &operator++() {
      if (current != nullptr) {
        current = current->next;
      }
      return *this;
    }

    bool operator!=(const Iterator &other) const {
      return current != other.current;
    }

    bool operator==(const Iterator &other) const {
      return current == other.current;
    }
  };

  SimpleList() { head = nullptr; }

  void addBack(T value) {
    Node<T> *newNode = new Node<T>(value);
    if (head == nullptr) {
      head = newNode;
      return;
    }
    Node<T> *current = head;
    while (current->next != nullptr) {
      current = current->next;
    }
    current->next = newNode;
  }

  void addFront(T value) {
    Node<T> *newNode = new Node<T>(value);
    newNode->next = head;
    head = newNode;
  }

  void showFrontToBack() {
    if (head == nullptr) {
      std::cout << "Lista vacia." << std::endl;
      return;
    }
    Node<T> *current = head;
    while (current != nullptr) {
      current->value->show();
      current = current->next;
    }
  }

  template <typename Funcion> void filter(Funcion condition) {
    Node<T> *current = head;
    while (current != nullptr) {
      if (condition(current->value)) {
        current->value->show();
      }
      current = current->next;
    }
  }

  void deleteById(int id) {
    if (head == nullptr) {
      std::cout << "Lista vacia." << std::endl;
      return;
    }
    if (head->value->getId() == id) {
      Node<T> *temp = head;
      head = head->next;
      delete temp;
      return;
    }
    Node<T> *current = head;
    while (current->next != nullptr) {
      if (current->next->value->getId() == id) {
        Node<T> *temp = current->next;
        current->next = temp->next;
        delete temp;
        return;
      }
      current = current->next;
    }
    std::cout << "Elemento no encontrado." << std::endl;
  }

  int count() {
    int total = 0;
    Node<T> *current = head;
    while (current != nullptr) {
      total++;
      current = current->next;
    }
    return total;
  }

  int countRecursive(Node<T> *node) {
    if (node == nullptr)
      return 0;
    return 1 + countRecursive(node->next);
  }

  Iterator begin() { return Iterator(head); }

  Iterator end() { return Iterator(nullptr); }

  ~SimpleList() {
    Node<T> *current = head;
    while (current != nullptr) {
      Node<T> *temp = current;
      current = current->next;
      delete temp;
    }
  }
};
