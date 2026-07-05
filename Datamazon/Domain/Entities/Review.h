#pragma once
#include "Entity.h"

class Review : public Entity {
private:
    int productId;
    int clientId;
    int rating;
    string comment;

public:
    Review() {}
    Review(int id, int productId, int clientId, int rating, string comment)
        : Entity(id) {
        this->productId = productId;
        this->clientId = clientId;
        this->rating = (rating < 1) ? 1 : (rating > 5) ? 5 : rating;
        this->comment = comment;
    }

    int getProductId() { return productId; }
    int getClientId() { return clientId; }
    int getRating() { return rating; }
    string getComment() { return comment; }

    void show() override {
        cout << "--------------------------------" << endl;
        cout << "  Resena ID  : " << id << endl;
        cout << "  Producto   : " << productId << endl;
        cout << "  Cliente    : " << clientId << endl;
        cout << "  Rating     : ";
        for (int i = 0; i < rating; i++) cout << "*";
        for (int i = rating; i < 5; i++) cout << "-";
        cout << " (" << rating << "/5)" << endl;
        cout << "  Comentario : " << comment << endl;
        cout << "--------------------------------" << endl;
    }

    ~Review() {}
};
