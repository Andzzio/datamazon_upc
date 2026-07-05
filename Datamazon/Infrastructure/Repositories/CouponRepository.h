#pragma once
#include "../../Domain/Repositories/ICouponRepository.h"

class CouponRepository : public ICouponRepository {
private:
    DoubleList<Coupon*>* coupons;

public:
    CouponRepository() {
        coupons = new DoubleList<Coupon*>();
    }

    ~CouponRepository() {
        Node<Coupon*>* curr = coupons->head;
        while (curr != nullptr) {
            Node<Coupon*>* temp = curr;
            curr = curr->next;
            delete temp->value;
            delete temp;
        }
        delete coupons;
    }

    void loadCoupons() override {
        Node<Coupon*>* curr = coupons->head;
        while (curr != nullptr) {
            Node<Coupon*>* temp = curr;
            curr = curr->next;
            delete temp->value;
            delete temp;
        }
        coupons->head = nullptr;
        coupons->tail = nullptr;

        coupons->addBack(new Coupon("UPC20", 20.0));
        coupons->addBack(new Coupon("DATAMAZON", 15.0));
        coupons->addBack(new Coupon("PRO10", 10.0));
        coupons->addBack(new Coupon("SAVE5", 5.0));
    }

    Coupon* getCouponByCode(string code) override {
        Node<Coupon*>* curr = coupons->head;
        while (curr != nullptr) {
            if (curr->value->getCode() == code) {
                return curr->value;
            }
            curr = curr->next;
        }
        return nullptr;
    }

    void addCoupon(Coupon* c) override {
        coupons->addBack(c);
    }
};
