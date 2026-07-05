#pragma once
#include "../../Domain/Entities/Product.h"
#include "../../Domain/Structures/Stack.h"
#include "../../Domain/Entities/Order.h"

class ManageCartUseCase {
private:
    Stack<Product*>* cart;

public:
    ManageCartUseCase() {
        cart = new Stack<Product*>();
    }

    ~ManageCartUseCase() {
        delete cart;
    }

    void addToCart(Product* p) {
        cart->push(p);
    }

    void removeFromCart() {
        if (!cart->isEmpty()) {
            cart->pop();
        }
    }

    Stack<Product*>* getCart() {
        return cart;
    }

    double getCartTotal() {
        return cart->getTotalPrice();
    }

    void clearCart() {
        cart->clearAll();
    }

    Order* checkout(int orderId, int clientId) {
        if (cart->isEmpty()) return nullptr;

        Order* order = new Order(orderId, clientId);
        DoubleList<Product*>* tempProducts = new DoubleList<Product*>();
        Node<Product*>* current = cart->getTop();
        while (current != nullptr) {
            tempProducts->addFront(current->value);
            current = current->next;
        }

        int detailId = 1;
        for (auto it = tempProducts->begin(); it != tempProducts->end(); ++it) {
            OrderDetail* detail = new OrderDetail(detailId++, *it, 1);
            order->addDetail(detail);
        }

        delete tempProducts;
        return order;
    }
};
