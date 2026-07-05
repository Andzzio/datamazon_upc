#pragma once
#include "../Infrastructure/Repositories/ProductRepository.h"
#include "../Infrastructure/Repositories/ClientRepository.h"
#include "../Infrastructure/Repositories/SupplierRepository.h"
#include "UseCases/SearchProductUseCase.h"
#include "UseCases/ManageCartUseCase.h"
#include "UseCases/ProcessOrderUseCase.h"
#include "UseCases/RunBenchmarksUseCase.h"

class UseCaseRegistry {
private:
    IProductRepository* productRepo;
    IClientRepository* clientRepo;
    ISupplierRepository* supplierRepo;

    SearchProductUseCase* searchProductUseCase;
    ManageCartUseCase* manageCartUseCase;
    ProcessOrderUseCase* processOrderUseCase;
    RunBenchmarksUseCase* runBenchmarksUseCase;

    UseCaseRegistry() {
        productRepo = new ProductRepository();
        clientRepo = new ClientRepository();
        supplierRepo = new SupplierRepository();

        productRepo->loadProducts();
        clientRepo->loadClients();
        supplierRepo->loadSuppliers();

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
    }

    IProductRepository* getProductRepository() { return productRepo; }
    IClientRepository* getClientRepository() { return clientRepo; }
    ISupplierRepository* getSupplierRepository() { return supplierRepo; }

    SearchProductUseCase* getSearchProductUseCase() { return searchProductUseCase; }
    ManageCartUseCase* getManageCartUseCase() { return manageCartUseCase; }
    ProcessOrderUseCase* getProcessOrderUseCase() { return processOrderUseCase; }
    RunBenchmarksUseCase* getRunBenchmarksUseCase() { return runBenchmarksUseCase; }
};
