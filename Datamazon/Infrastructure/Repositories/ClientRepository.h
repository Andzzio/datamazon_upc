#pragma once
#include "../../Domain/Repositories/IClientRepository.h"
#include "../Datasources/TextFileDatasource.h"

class ClientRepository : public IClientRepository {
private:
    DoubleList<Client*>* clients;

public:
    ClientRepository() {
        clients = new DoubleList<Client*>();
    }

    ~ClientRepository() {
        delete clients;
    }

    void loadClients() override {
        while (clients->head != nullptr) {
            clients->deleteById(clients->head->value->getId());
        }
        TextFileDatasource::loadClients(clients);
    }

    void saveClients() override {
        TextFileDatasource::saveClients(clients);
    }

    DoubleList<Client*>* getAllClients() override {
        return clients;
    }

    void addClient(Client* c) override {
        clients->addBack(c);
    }

    Client* getClientById(int id) override {
        for (auto it = clients->begin(); it != clients->end(); ++it) {
            if ((*it)->getId() == id) {
                return *it;
            }
        }
        return nullptr;
    }
};
