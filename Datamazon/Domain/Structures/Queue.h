#pragma once
#include "Node.h"
#include <iostream>
using namespace std;

template <typename T> class Queue {
private:
  Node<T> *front;
  Node<T> *back;

public:
  Queue() { front = back = nullptr; }

  Node<T>* getFront() const { return front; }

  void enqueue(T value) {
    Node<T> *newNode = new Node<T>(value);
    if (back == nullptr) {
      front = back = newNode;
      return;
    }
    back->next = newNode;
    back = newNode;
  }

  void dequeue() {
    if (front == nullptr) {
      cout << "No hay pedidos en cola." << endl;
      return;
    }
    Node<T> *temp = front;
    front = front->next;
    if (front == nullptr)
      back = nullptr;
    delete temp;
  }

  T peek() {
    if (front == nullptr) {
      cout << "No hay pedidos en cola." << endl;
      return T();
    }
    return front->value;
  }

  bool isEmpty() { return front == nullptr; }

  void showAll() {
    if (front == nullptr) {
      cout << "No hay pedidos en cola." << endl;
      return;
    }
    Node<T> *current = front;
    int pos = 1;
    cout << "\n==== COLA DE PEDIDOS ====" << endl;
    while (current != nullptr) {
      cout << "Posicion #" << pos++ << ":" << endl;
      current->value->show();
      current = current->next;
    }
  }

  int count() {
    int total = 0;
    Node<T> *current = front;
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

  bool contains(int id) {
    Node<T> *current = front;
    while (current != nullptr) {
      if (current->value->getId() == id)
        return true;
      current = current->next;
    }
    return false;
  }

  double getTotalRevenue() {
    double total = 0;
    Node<T> *current = front;
    while (current != nullptr) {
      total += current->value->getTotal();
      current = current->next;
    }
    return total;
  }

  template <typename Funcion> void filter(Funcion condition) {
    Node<T> *current = front;
    while (current != nullptr) {
      if (condition(current->value))
        current->value->show();
      current = current->next;
    }
  }

  void clearAll() {
    while (!isEmpty())
      dequeue();
    cout << "Cola vaciada." << endl;
  }

  ~Queue() {}
};
