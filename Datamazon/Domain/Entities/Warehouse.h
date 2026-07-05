#pragma once
#include "Entity.h"

class Warehouse : public Entity {
private:
    string location;
    int capacity;
    int usedSpace;

public:
    Warehouse() {}
    Warehouse(int id, string location, int capacity)
        : Entity(id) {
        this->location = location;
        this->capacity = capacity;
        this->usedSpace = 0;
    }

    string getLocation() { return location; }
    int getCapacity() { return capacity; }
    int getUsedSpace() { return usedSpace; }
    int getAvailable() { return capacity - usedSpace; }

    bool addStock(int units) {
        if (usedSpace + units > capacity) return false;
        usedSpace += units;
        return true;
    }

    void show() override {
        cout << "================================" << endl;
        cout << "  Almacen    : " << id << endl;
        cout << "  Ubicacion  : " << location << endl;
        cout << "  Capacidad  : " << capacity << endl;
        cout << "  Usado      : " << usedSpace << endl;
        cout << "  Disponible : " << getAvailable() << endl;
        cout << "================================" << endl;
    }

    ~Warehouse() {}
};
