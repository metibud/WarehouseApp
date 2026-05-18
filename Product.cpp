#include "Product.h"

#include <sstream>

Product::Product()
    : id(0), price(0.0), quantity(0) {}

Product::Product(int id,
                 const std::string& name,
                 const std::string& category,
                 double price,
                 int quantity)
    : id(id),
      name(name),
      category(category),
      price(price),
      quantity(quantity) {}

int Product::getId() const {
    return id;
}

std::string Product::getName() const {
    return name;
}

std::string Product::getCategory() const {
    return category;
}

double Product::getPrice() const {
    return price;
}

int Product::getQuantity() const {
    return quantity;
}

void Product::setName(const std::string& name) {
    this->name = name;
}

void Product::setCategory(const std::string& category) {
    this->category = category;
}

void Product::setPrice(double price) {
    this->price = price;
}

void Product::setQuantity(int quantity) {
    this->quantity = quantity;
}

std::string Product::toString() const {
    std::ostringstream oss;

    oss << "ID: " << id
        << " | Название: " << name
        << " | Категория: " << category
        << " | Цена: " << price
        << " | Количество: " << quantity;

    return oss.str();
}