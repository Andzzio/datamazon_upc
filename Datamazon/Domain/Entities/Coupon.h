#pragma once
#include <iostream>
#include <string>

using namespace std;

class Coupon {
private:
    string code;
    double discountPercent;

public:
    Coupon(string code, double discountPercent) {
        this->code = code;
        this->discountPercent = discountPercent;
    }

    string getCode() { return code; }
    double getDiscountPercent() { return discountPercent; }

    void show() {
        cout << "Cupon: " << code << " | Descuento: " << discountPercent << "%" << endl;
    }

    ~Coupon() {}
};
