#pragma once
#include <iostream>
#include <string>

using namespace std;

class Invoice {
private:
    int invoiceId;
    int orderId;
    string date;
    double totalTax;
    double totalAmount;

public:
    Invoice(int invoiceId, int orderId, string date, double totalTax, double totalAmount) {
        this->invoiceId = invoiceId;
        this->orderId = orderId;
        this->date = date;
        this->totalTax = totalTax;
        this->totalAmount = totalAmount;
    }

    int getInvoiceId() { return invoiceId; }
    int getOrderId() { return orderId; }
    string getDate() { return date; }
    double getTotalTax() { return totalTax; }
    double getTotalAmount() { return totalAmount; }

    void show() {
        cout << "================================" << endl;
        cout << "  BOLETA DE VENTA" << endl;
        cout << "  Boleta Nro   : " << invoiceId << endl;
        cout << "  Pedido ID    : " << orderId << endl;
        cout << "  Fecha        : " << date << endl;
        cout << "  IGV (18%)    : S/. " << totalTax << endl;
        cout << "  Total Neto   : S/. " << totalAmount << endl;
        cout << "================================" << endl;
    }

    ~Invoice() {}
};
