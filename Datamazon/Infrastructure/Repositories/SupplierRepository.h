#pragma once
#include "../../Domain/Repositories/ISupplierRepository.h"
#include "../Datasources/TextFileDatasource.h"

class SupplierRepository : public ISupplierRepository {
private:
    DoubleList<Supplier*>* suppliers;

public:
    SupplierRepository() {
        suppliers = new DoubleList<Supplier*>();
    }

    ~SupplierRepository() {
        delete suppliers;
    }

    void loadSuppliers() override {
        while (suppliers->head != nullptr) {
            suppliers->deleteById(suppliers->head->value->getId());
        }
        TextFileDatasource::loadSuppliers(suppliers);
    }

    void saveSuppliers() override {
        TextFileDatasource::saveSuppliers(suppliers);
    }

    DoubleList<Supplier*>* getAllSuppliers() override {
        return suppliers;
    }

    void addSupplier(Supplier* s) override {
        suppliers->addBack(s);
    }
};
