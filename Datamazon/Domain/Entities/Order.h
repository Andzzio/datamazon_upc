#pragma once
#include <iostream>
#include <string>
#include "Entity.h"
#include "OrderDetail.h"
#include "../Structures/DoubleList.h"
#include "Payment.h"
using namespace std;

class Order : public Entity {
private:
    int clientId;
    string status;
    double total;
    Payment* payment;
    DoubleList<OrderDetail*>* details;

public:
    Order() {}
    Order(int id, int clientId) : Entity(id) {
        this->clientId = clientId;
        this->status = "pendiente";
        this->total = 0;
        this->payment = nullptr;
        this->details = new DoubleList<OrderDetail*>();
    }

    int    getClientId() { return clientId; }
    string getStatus() { return status; }
    double getTotal() { return total; }
    void   setTotal(double t) { total = t; }
    void   setStatus(string s) { status = s; }
    Payment* getPayment() { return payment; }
    void   setPayment(Payment* p) { payment = p; }
    DoubleList<OrderDetail*>* getDetails() { return details; }

    void addDetail(OrderDetail* detail) {
        details->addBack(detail);
        total += detail->getSubtotal();
    }

    void show() override {
        cout << "================================" << endl;
        cout << "  PEDIDO ID  : " << id << endl;
        cout << "  Cliente ID : " << clientId << endl;
        cout << "  Estado     : " << status << endl;
        cout << "  Total      : S/. " << total << endl;
        cout << "================================" << endl;
        
        cout << "\n[ Detalle del Pedido ]" << endl;
        details->showFrontToBack();

        if (payment != nullptr) {
            cout << "\n[ Info de Pago ]" << endl;
            payment->show();
        }
    }

    ~Order() {}
};
