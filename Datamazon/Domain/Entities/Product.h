#pragma once
#include "Entity.h"

class Product : public Entity {
protected:
  string name;
  string category;
  double price;
  int stock;
  string imagePath;

public:
  Product(int id, string name, string category, double price, int stock, string imagePath = "default.jpg")
      : Entity(id) {
    this->name = name;
    this->category = category;
    this->price = price;
    this->stock = stock;
    this->imagePath = imagePath;
  }
  string getName() { return name; }
  string getCategory() { return category; }
  double getPrice() { return price; }
  int getStock() { return stock; }
  string getImagePath() { return imagePath; }
  void setImagePath(string path) { imagePath = path; }
  void setStock(int s) { stock = s; }

  void show() override {
    cout << "ID: " << id << " | Nombre: " << name << " | Categoria: " << category << " | Precio: S/. " << price << " | Stock: " << stock << " | Imagen: " << imagePath << endl;
  }

  ~Product() {}
};
