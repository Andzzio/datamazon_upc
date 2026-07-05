#pragma once
#include "../../Domain/Repositories/IProductRepository.h"
#include "../Datasources/TextFileDatasource.h"

class ProductRepository : public IProductRepository {
private:
    DoubleList<Product*>* products;
    HashTable<int, Product*>* productsHash;
    AVLTree<Product*, double>* productsAvlPrice;
    AVLTree<Product*, string>* productsAvlName;

public:
    ProductRepository() {
        products = new DoubleList<Product*>();
        productsHash = new HashTable<int, Product*>();
        productsAvlPrice = new AVLTree<Product*, double>();
        productsAvlName = new AVLTree<Product*, string>();
    }

    ~ProductRepository() {
        delete products;
        delete productsHash;
        delete productsAvlPrice;
        delete productsAvlName;
    }

    void loadProducts() override {
        while (products->head != nullptr) {
            products->deleteById(products->head->value->getId());
        }
        productsHash->clear();
        productsAvlPrice->clear();
        productsAvlName->clear();

        TextFileDatasource::loadProducts(products);

        for (auto it = products->begin(); it != products->end(); ++it) {
            productsHash->insertar((*it)->getId(), *it);
            productsAvlPrice->insert((*it)->getPrice(), *it);
            productsAvlName->insert((*it)->getName(), *it);
        }
    }

    void saveProducts() override {
        TextFileDatasource::saveProducts(products);
    }

    DoubleList<Product*>* getAllProducts() override {
        return products;
    }

    void addProduct(Product* p) override {
        products->addBack(p);
        productsHash->insertar(p->getId(), p);
        productsAvlPrice->insert(p->getPrice(), p);
        productsAvlName->insert(p->getName(), p);
    }

    void deleteProduct(int id) override {
        Product* p = getProductById(id);
        if (p != nullptr) {
            products->deleteById(id);
            productsHash->clear();
            productsAvlPrice->clear();
            productsAvlName->clear();
            for (auto it = products->begin(); it != products->end(); ++it) {
                productsHash->insertar((*it)->getId(), *it);
                productsAvlPrice->insert((*it)->getPrice(), *it);
                productsAvlName->insert((*it)->getName(), *it);
            }
        }
    }

    Product* getProductById(int id) override {
        Product** pRef = productsHash->buscar(id);
        if (pRef != nullptr) {
            return *pRef;
        }
        return nullptr;
    }

    HashTable<int, Product*>* getProductsHash() override {
        return productsHash;
    }

    AVLTree<Product*, double>* getProductsAvlPrice() override {
        return productsAvlPrice;
    }

    AVLTree<Product*, string>* getProductsAvlName() override {
        return productsAvlName;
    }
};
