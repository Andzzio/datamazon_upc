#pragma once
#include "../Entities/Coupon.h"
#include "../Structures/DoubleList.h"

class ICouponRepository {
public:
    virtual ~ICouponRepository() {}
    virtual void loadCoupons() = 0;
    virtual Coupon* getCouponByCode(string code) = 0;
    virtual void addCoupon(Coupon* c) = 0;
};
