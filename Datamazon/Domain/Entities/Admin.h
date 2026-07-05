#pragma once
#include "Person.h"

class Admin : public Person {
private:
    string password;
    string accessLevel;

public:
    Admin() {}
    Admin(int id, string name, string email, string phoneNumber,
        string password, string accessLevel)
        : Person(id, name, email, phoneNumber) {
        this->password = password;
        this->accessLevel = accessLevel;
    }

    string getAccessLevel() { return accessLevel; }

    bool authenticate(string pass) {
        return this->password == pass;
    }

    void show() override {
        cout << "================================" << endl;
        cout << "  Admin    : " << name << endl;
        cout << "  Email    : " << email << endl;
        cout << "  Nivel    : " << accessLevel << endl;
        cout << "================================" << endl;
    }

    ~Admin() {}
};
