#pragma once
#include "Person.h"

class Client: public Person
{
private:
	string address;
	string membership;
public:
	Client(int id, string name, string email, string phoneNumber, string address, string membership) : Person(id,name,email,phoneNumber){
		this->address = address;
		this->membership = membership;
	}

	string getAddress() { return address; }
	string getMembership() { return membership; }

	void show() override {
		cout << "Cliente: " << name << " | Email: " << email
			<< " | Membresia: " << membership << endl;
	}
	~Client(){}
};
