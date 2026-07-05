#pragma once
#include "../Entities/Client.h"
#include "../Structures/DoubleList.h"

class IClientRepository {
public:
    virtual ~IClientRepository() {}
    virtual void loadClients() = 0;
    virtual void saveClients() = 0;
    virtual DoubleList<Client*>* getAllClients() = 0;
    virtual void addClient(Client* c) = 0;
    virtual Client* getClientById(int id) = 0;
};
