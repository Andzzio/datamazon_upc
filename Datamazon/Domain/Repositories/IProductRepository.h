#pragma once
#include "../Entities/Product.h"
#include "../Structures/DoubleList.h"
#include "../Structures/HashTable.h"
#include "../Structures/AVLTree.h"

class IProductRepository {
public:
    virtual ~IProductRepository() {}
    virtual void loadProducts() = 0;
    virtual void saveProducts() = 0;
    virtual DoubleList<Product*>* getAllProducts() = 0;
    virtual void addProduct(Product* p) = 0;
    virtual void deleteProduct(int id) = 0;
    virtual Product* getProductById(int id) = 0;
    virtual HashTable<int, Product*>* getProductsHash() = 0;
    virtual AVLTree<Product*, double>* getProductsAvlPrice() = 0;
    virtual AVLTree<Product*, string>* getProductsAvlName() = 0;
};
