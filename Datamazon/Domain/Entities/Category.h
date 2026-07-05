#pragma once
#include "Entity.h"

class Category : public Entity {
private:
    string name;
    string description;
    int productCount;

public:
    Category() {}
    Category(int id, string name, string description)
        : Entity(id) {
        this->name = name;
        this->description = description;
        this->productCount = 0;
    }

    string getName() { return name; }
    string getDescription() { return description; }
    int getProductCount() { return productCount; }
    void incrementCount() { productCount++; }

    void show() override {
        cout << "================================" << endl;
        cout << "  Categoria  : " << name << endl;
        cout << "  Descripcion: " << description << endl;
        cout << "  Productos  : " << productCount << endl;
        cout << "================================" << endl;
    }

    ~Category() {}
};
