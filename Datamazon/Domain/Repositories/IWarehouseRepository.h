#pragma once
#include "../Entities/Warehouse.h"
#include "../Structures/DoubleList.h"

class IWarehouseRepository {
public:
    virtual ~IWarehouseRepository() {}
    virtual void loadWarehouses() = 0;
    virtual void saveWarehouses() = 0;
    virtual DoubleList<Warehouse*>* getAllWarehouses() = 0;
    virtual void addWarehouse(Warehouse* w) = 0;
};
