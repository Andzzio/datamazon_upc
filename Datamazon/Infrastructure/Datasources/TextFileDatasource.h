#pragma once
#include <fstream>
#include <sstream>
#include "../../Domain/Structures/DoubleList.h"
#include "../../Domain/Entities/Product.h"
#include "../../Domain/Entities/Client.h"
#include "../../Domain/Entities/Supplier.h"
#include "../../Domain/Entities/Warehouse.h"

using namespace std;

class TextFileDatasource {
public:
    static string getDefaultImageForName(const string& name) {
        string type = name.substr(0, name.find(' '));
        if (type == "Laptop")       return "laptop.jpg";
        if (type == "Smartphone")   return "smartphone.jpg";
        if (type == "Teclado")      return "teclado.jpg";
        if (type == "Mouse")        return "mouse.jpg";
        if (type == "Monitor")      return "monitor.jpg";
        if (type == "Casaca")       return "casaca.jpg";
        if (type == "Jeans")        return "jean.jpg";
        if (type == "Zapatillas")   return "zapatilla.jpg";
        if (type == "Enciclopedia") return "enciclopedia.jpg";
        if (type == "Novela")       return "novela.jpg";
        return "default.jpg";
    }

    static void saveProducts(DoubleList<Product*>* products, string filename = "products.txt") {
        ofstream file(filename);
        if (!file.is_open()) return;
        Node<Product*>* current = products->head;
        while (current != nullptr) {
            Product* p = current->value;
            file << p->getId() << "," << p->getName() << ","
                 << p->getCategory() << "," << p->getPrice()
                 << "," << p->getStock() << "," << p->getImagePath() << "\n";
            current = current->next;
        }
        file.close();
    }

    static void loadProducts(DoubleList<Product*>* products, string filename = "products.txt") {
        ifstream file(filename);
        if (!file.is_open()) return;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            int id, stock; string name, category, imagePath; double price;
            getline(ss, token, ','); id = stoi(token);
            getline(ss, name, ',');
            getline(ss, category, ',');
            getline(ss, token, ','); price = stod(token);
            getline(ss, token, ','); stock = stoi(token);
            if (!getline(ss, imagePath, ',')) {
                imagePath = getDefaultImageForName(name);
            }
            if (imagePath.empty()) {
                imagePath = getDefaultImageForName(name);
            }
            products->addBack(new Product(id, name, category, price, stock, imagePath));
        }
        file.close();
    }

    static void saveClients(DoubleList<Client*>* clients, string filename = "clients.txt") {
        ofstream file(filename);
        if (!file.is_open()) return;
        Node<Client*>* current = clients->head;
        while (current != nullptr) {
            Client* c = current->value;
            file << c->getId() << "," << c->getName() << ","
                 << c->getEmail() << "," << c->getPhone() << "," << c->getAddress()
                 << "," << c->getMembership() << "\n";
            current = current->next;
        }
        file.close();
    }

    static void loadClients(DoubleList<Client*>* clients, string filename = "clients.txt") {
        ifstream file(filename);
        if (!file.is_open()) return;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            int id; string name, email, phone, address, membership;
            getline(ss, token, ','); id = stoi(token);
            getline(ss, name, ',');
            getline(ss, email, ',');
            getline(ss, phone, ',');
            getline(ss, address, ',');
            getline(ss, membership, ',');
            clients->addBack(new Client(id, name, email, phone, address, membership));
        }
        file.close();
    }

    static void saveSuppliers(DoubleList<Supplier*>* suppliers, string filename = "suppliers.txt") {
        ofstream file(filename);
        if (!file.is_open()) return;
        Node<Supplier*>* current = suppliers->head;
        while (current != nullptr) {
            Supplier* s = current->value;
            file << s->getId() << "," << s->getName() << ","
                 << s->getEmail() << "," << s->getPhone()
                 << "," << s->getCountry() << "," << s->getProductCategory() << "\n";
            current = current->next;
        }
        file.close();
    }

    static void loadSuppliers(DoubleList<Supplier*>* suppliers, string filename = "suppliers.txt") {
        ifstream file(filename);
        if (!file.is_open()) return;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            int id; string name, email, phone, country, category;
            getline(ss, token, ','); id = stoi(token);
            getline(ss, name, ',');
            getline(ss, email, ',');
            getline(ss, phone, ',');
            getline(ss, country, ',');
            getline(ss, category, ',');
            suppliers->addBack(new Supplier(id, name, email, phone, country, category));
        }
        file.close();
    }

    static void saveWarehouses(DoubleList<Warehouse*>* warehouses, string filename = "warehouses.txt") {
        ofstream file(filename);
        if (!file.is_open()) return;
        Node<Warehouse*>* current = warehouses->head;
        while (current != nullptr) {
            Warehouse* w = current->value;
            file << w->getId() << "," << w->getLocation() << "," << w->getCapacity() << "\n";
            current = current->next;
        }
        file.close();
    }

    static void loadWarehouses(DoubleList<Warehouse*>* warehouses, string filename = "warehouses.txt") {
        ifstream file(filename);
        if (!file.is_open()) return;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            int id; string location; int capacity;
            getline(ss, token, ','); id = stoi(token);
            getline(ss, location, ',');
            getline(ss, token, ','); capacity = stoi(token);
            warehouses->addBack(new Warehouse(id, location, capacity));
        }
        file.close();
    }
};
