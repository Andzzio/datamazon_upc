#pragma once
#include "../../Domain/Repositories/IProductRepository.h"
#include <algorithm>
#include <cctype>

using namespace std;

class SearchProductUseCase {
private:
    IProductRepository* productRepo;

public:
    SearchProductUseCase(IProductRepository* repo) {
        this->productRepo = repo;
    }

    Product* searchById(int id) {
        return productRepo->getProductById(id);
    }

    Product* searchByName(string name) {
        Product** pRef = productRepo->getProductsAvlName()->search(name);
        if (pRef != nullptr) {
            return *pRef;
        }
        return nullptr;
    }

    DoubleList<Product*>* searchFuzzy(string query) {
        DoubleList<Product*>* filtered = new DoubleList<Product*>();
        DoubleList<Product*>* allProducts = productRepo->getAllProducts();
        
        string lowerQuery = query;
        transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

        for (auto it = allProducts->begin(); it != allProducts->end(); ++it) {
            string pName = (*it)->getName();
            transform(pName.begin(), pName.end(), pName.begin(), ::tolower);
            if (lowerQuery.empty() || pName.find(lowerQuery) != string::npos) {
                filtered->addBack(*it);
            }
        }
        return filtered;
    }

    DoubleList<Product*>* filterByPriceRange(double minPrice, double maxPrice) {
        DoubleList<Product*>* filtered = new DoubleList<Product*>();
        productRepo->getProductsAvlPrice()->rangeSearch(minPrice, maxPrice, [filtered](Product* p) {
            filtered->addBack(p);
        });
        return filtered;
    }
};
