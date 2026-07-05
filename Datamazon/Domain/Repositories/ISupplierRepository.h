#pragma once
#include "../Entities/Supplier.h"
#include "../Structures/DoubleList.h"

class ISupplierRepository {
public:
    virtual ~ISupplierRepository() {}
    virtual void loadSuppliers() = 0;
    virtual void saveSuppliers() = 0;
    virtual DoubleList<Supplier*>* getAllSuppliers() = 0;
    virtual void addSupplier(Supplier* s) = 0;
};
