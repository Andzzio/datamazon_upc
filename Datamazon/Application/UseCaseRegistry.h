#pragma once
#include "../Infrastructure/Repositories/ProductRepository.h"
#include "../Infrastructure/Repositories/ClientRepository.h"
#include "../Infrastructure/Repositories/SupplierRepository.h"
#include "../Infrastructure/Repositories/WarehouseRepository.h"
#include "../Infrastructure/Repositories/CouponRepository.h"
#include "UseCases/SearchProductUseCase.h"
#include "UseCases/ManageCartUseCase.h"
#include "UseCases/ProcessOrderUseCase.h"
#include "UseCases/RunBenchmarksUseCase.h"

class UseCaseRegistry {
private:
    IProductRepository* productRepo;
    IClientRepository* clientRepo;
    ISupplierRepository* supplierRepo;
    IWarehouseRepository* warehouseRepo;
    ICouponRepository* couponRepo;

    SearchProductUseCase* searchProductUseCase;
    ManageCartUseCase* manageCartUseCase;
    ProcessOrderUseCase* processOrderUseCase;
    RunBenchmarksUseCase* runBenchmarksUseCase;

    UseCaseRegistry() {
        productRepo = new ProductRepository();
        clientRepo = new ClientRepository();
        supplierRepo = new SupplierRepository();
        warehouseRepo = new WarehouseRepository();
        couponRepo = new CouponRepository();

        productRepo->loadProducts();
        clientRepo->loadClients();
        supplierRepo->loadSuppliers();
        warehouseRepo->loadWarehouses();
        couponRepo->loadCoupons();

        searchProductUseCase = new SearchProductUseCase(productRepo);
        manageCartUseCase = new ManageCartUseCase();
        processOrderUseCase = new ProcessOrderUseCase();
        runBenchmarksUseCase = new RunBenchmarksUseCase(productRepo);
    }

    static UseCaseRegistry* instance;

public:
    static UseCaseRegistry* getInstance() {
        if (instance == nullptr) {
            instance = new UseCaseRegistry();
        }
        return instance;
    }

    ~UseCaseRegistry() {
        delete searchProductUseCase;
        delete manageCartUseCase;
        delete processOrderUseCase;
        delete runBenchmarksUseCase;
        delete productRepo;
        delete clientRepo;
        delete supplierRepo;
        delete warehouseRepo;
        delete couponRepo;
    }

    IProductRepository* getProductRepository() { return productRepo; }
    IClientRepository* getClientRepository() { return clientRepo; }
    ISupplierRepository* getSupplierRepository() { return supplierRepo; }
    IWarehouseRepository* getWarehouseRepository() { return warehouseRepo; }
    ICouponRepository* getCouponRepository() { return couponRepo; }

    SearchProductUseCase* getSearchProductUseCase() { return searchProductUseCase; }
    ManageCartUseCase* getManageCartUseCase() { return manageCartUseCase; }
    ProcessOrderUseCase* getProcessOrderUseCase() { return processOrderUseCase; }
    RunBenchmarksUseCase* getRunBenchmarksUseCase() { return runBenchmarksUseCase; }
};
