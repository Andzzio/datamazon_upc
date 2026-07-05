#pragma once
#include "Entity.h"

class Person : public Entity {
protected:
  string name;
  string email;
  string phoneNumber;

public:
  Person() {}
  Person(int id, string name, string email, string phoneNumber) : Entity(id) {
    this->name = name;
    this->email = email;
    this->phoneNumber = phoneNumber;
  }

  string getName() { return name; }
  string getEmail() { return email; }
  string getPhone() { return phoneNumber; }
  ~Person() {}
};
