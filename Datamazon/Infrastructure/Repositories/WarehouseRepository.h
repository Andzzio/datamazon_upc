#pragma once
#include "../../Domain/Repositories/IWarehouseRepository.h"
#include "../Datasources/TextFileDatasource.h"

class WarehouseRepository : public IWarehouseRepository {
private:
    DoubleList<Warehouse*>* warehouses;

public:
    WarehouseRepository() {
        warehouses = new DoubleList<Warehouse*>();
    }

    ~WarehouseRepository() {
        delete warehouses;
    }

    void loadWarehouses() override {
        while (warehouses->head != nullptr) {
            warehouses->deleteById(warehouses->head->value->getId());
        }
        TextFileDatasource::loadWarehouses(warehouses);
    }

    void saveWarehouses() override {
        TextFileDatasource::saveWarehouses(warehouses);
    }

    DoubleList<Warehouse*>* getAllWarehouses() override {
        return warehouses;
    }

    void addWarehouse(Warehouse* w) override {
        warehouses->addBack(w);
    }
};
