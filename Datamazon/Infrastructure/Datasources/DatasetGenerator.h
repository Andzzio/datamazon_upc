#pragma once
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "TextFileDatasource.h"

class DatasetGenerator {
public:
    static void generateAndSave(int numProducts, int numClients, int numSuppliers) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        const int numNames = 10;
        std::string prodNames[numNames] = { "Laptop", "Smartphone", "Teclado", "Mouse", "Monitor", "Casaca", "Jeans", "Zapatillas", "Enciclopedia", "Novela" };
        std::string prodBrands[numNames] = { "Pro", "Ultra", "Max", "Lite", "Plus", "Gamer", "Style", "Classic", "Premium", "Basic" };
        std::string categories[3] = { "Tecnologia", "Ropa", "Educacion" };

        std::ofstream prodFile("products.txt");
        if (prodFile.is_open()) {
            for (int i = 1; i <= numProducts; ++i) {
                std::string name = prodNames[std::rand() % numNames] + " " + prodBrands[std::rand() % numNames];
                std::string cat = categories[std::rand() % 3];
                double price = 10.0 + (std::rand() % 4990) + (std::rand() % 100) / 100.0;
                int stock = 5 + (std::rand() % 95);
                std::string image = TextFileDatasource::getDefaultImageForName(name);
                prodFile << i << "," << name << "," << cat << "," << price << "," << stock << "," << image << "\n";
            }
            prodFile.close();
        }

        std::string clientFirst[numNames] = { "Andres", "Juan", "Maria", "Pedro", "Ana", "Luis", "Lucia", "Jose", "Carmen", "Sofia" };
        std::string clientLast[numNames] = { "Sanchez", "Gomez", "Perez", "Rodriguez", "Torres", "Flores", "Quispe", "Ramos", "Diaz", "Mendoza" };
        std::string memberships[2] = { "normal", "prime" };

        std::ofstream clientFile("clients.txt");
        if (clientFile.is_open()) {
            for (int i = 1; i <= numClients; ++i) {
                std::string name = clientFirst[std::rand() % numNames] + " " + clientLast[std::rand() % numNames];
                std::string email = clientFirst[std::rand() % numNames] + std::to_string(i) + "@datamazon.com";
                std::string address = "Av. Principal " + std::to_string(100 + (std::rand() % 900));
                std::string mem = memberships[std::rand() % 2];
                clientFile << i << "," << name << "," << email << "," << address << "," << mem << "\n";
            }
            clientFile.close();
        }

        std::string supplierNames[numNames] = { "TechSupplier", "GlobalImport", "FashionFactory", "BookDistributor", "EduWorld", "OmegaCorp", "AlfaLogistics", "DeltaTrade", "SigmaSource", "PrimeGoods" };
        std::ofstream suppFile("suppliers.txt");
        if (suppFile.is_open()) {
            for (int i = 1; i <= numSuppliers; ++i) {
                std::string name = supplierNames[std::rand() % numNames] + " " + std::to_string(i);
                std::string email = "contact@" + supplierNames[std::rand() % numNames] + std::to_string(i) + ".com";
                std::string phone = "9" + std::to_string(10000000 + (std::rand() % 90000000));
                std::string country = (std::rand() % 2 == 0) ? "USA" : "Peru";
                std::string cat = categories[std::rand() % 3];
                suppFile << i << "," << name << "," << email << "," << phone << "," << country << "," << cat << "\n";
            }
            suppFile.close();
        }
    }
};
