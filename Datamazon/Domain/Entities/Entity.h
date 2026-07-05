#pragma once
#include <iostream>
#include <string>
using namespace std;

class Entity {
protected:
    int id;
    string creationDate;

public:
    Entity() {
        id = 0;
        creationDate = "";
    }
    Entity(int id) {
        this->id = id;
    }

    int getId() { return id; }
    virtual void show() = 0;
    virtual ~Entity() {}
};
