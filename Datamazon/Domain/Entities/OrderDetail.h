#pragma once

#include <iostream>
#include <string>
#include "Product.h"
using namespace std;

class OrderDetail : public Entity {
private:
    Product* product;
    int quantity;
    double subtotal;

public:
    OrderDetail() {}
    OrderDetail(int id, Product* product, int quantity) : Entity(id) {
        this->product = product;
        this->quantity = quantity;
        this->subtotal = product->getPrice() * quantity;
    }

    Product* getProduct() { return product; }
    int getQuantity() { return quantity; }
    double getSubtotal() { return subtotal; }

    void show() override {
        cout << "  - " << product->getName()
            << " x" << quantity
            << " = S/." << subtotal << endl;
    }

    ~OrderDetail() {}
};
