#include "Warehouse.h"

#include <algorithm>
#include <iostream>

namespace {
    std::string toLower(std::string str) {
        std::transform(str.begin(),
                       str.end(),
                       str.begin(),
                       [](unsigned char c) {
                           return static_cast<char>(std::tolower(c));
                       });

        return str;
    }
}

bool Warehouse::isUniqueId(int id) const {
    for (const auto& product : products) {
        if (product.getId() == id) {
            return false;
        }
    }

    return true;
}

void Warehouse::addProduct(const Product& product) {
    if (!isUniqueId(product.getId())) {
        std::cout << "Ошибка: ID уже существует.\n";
        return;
    }

    if (product.getPrice() < 0 || product.getQuantity() < 0) {
        std::cout << "Ошибка: цена и количество не могут быть отрицательными.\n";
        return;
    }

    if (product.getName().empty() || product.getCategory().empty()) {
        std::cout << "Ошибка: строки не могут быть пустыми.\n";
        return;
    }

    products.push_back(product);

    std::cout << "Товар успешно добавлен.\n";
}

bool Warehouse::editProduct(int id,
                            const std::string& newName,
                            const std::string& newCategory,
                            double newPrice,
                            int newQuantity) {
    for (auto& product : products) {
        if (product.getId() == id) {
            if (newPrice < 0 || newQuantity < 0) {
                return false;
            }

            product.setName(newName);
            product.setCategory(newCategory);
            product.setPrice(newPrice);
            product.setQuantity(newQuantity);

            return true;
        }
    }

    return false;
}

bool Warehouse::deleteProductById(int id) {
    auto it = std::remove_if(products.begin(),
                             products.end(),
                             [id](const Product& product) {
                                 return product.getId() == id;
                             });

    if (it != products.end()) {
        products.erase(it, products.end());
        return true;
    }

    return false;
}

std::vector<Product> Warehouse::searchByName(const std::string& name) const {
    std::vector<Product> result;

    std::string search = toLower(name);

    for (const auto& product : products) {
        std::string productName = toLower(product.getName());

        if (productName.find(search) != std::string::npos) {
            result.push_back(product);
        }
    }

    return result;
}

std::vector<Product> Warehouse::filterByCategory(const std::string& category) const {
    std::vector<Product> result;

    for (const auto& product : products) {
        if (toLower(product.getCategory()) == toLower(category)) {
            result.push_back(product);
        }
    }

    return result;
}

std::vector<Product> Warehouse::filterByPrice(double minPrice,
                                              double maxPrice) const {
    std::vector<Product> result;

    for (const auto& product : products) {
        if (product.getPrice() >= minPrice &&
            product.getPrice() <= maxPrice) {
            result.push_back(product);
        }
    }

    return result;
}

void Warehouse::sortByPrice(bool ascending) {
    std::sort(products.begin(),
              products.end(),
              [ascending](const Product& a, const Product& b) {
                  if (ascending) {
                      return a.getPrice() < b.getPrice();
                  }

                  return a.getPrice() > b.getPrice();
              });
}

void Warehouse::sortByQuantity() {
    std::sort(products.begin(),
              products.end(),
              [](const Product& a, const Product& b) {
                  return a.getQuantity() < b.getQuantity();
              });
}

void Warehouse::sortByName() {
    std::sort(products.begin(),
              products.end(),
              [](const Product& a, const Product& b) {
                  return a.getName() < b.getName();
              });
}

double Warehouse::getTotalValue() const {
    double total = 0;

    for (const auto& product : products) {
        total += product.getPrice() * product.getQuantity();
    }

    return total;
}

std::vector<Product> Warehouse::getLowStockProducts() const {
    std::vector<Product> result;

    for (const auto& product : products) {
        if (product.getQuantity() <= 5) {
            result.push_back(product);
        }
    }

    return result;
}

std::vector<Product> Warehouse::getTopExpensiveProducts() const {
    std::vector<Product> result = products;

    std::sort(result.begin(),
              result.end(),
              [](const Product& a, const Product& b) {
                  return a.getPrice() > b.getPrice();
              });

    if (result.size() > 3) {
        result.resize(3);
    }

    return result;
}

std::vector<Product>& Warehouse::getProducts() {
    return products;
}

const std::vector<Product>& Warehouse::getProductsConst() const {
    return products;
}

void Warehouse::displayAllProducts() const {
    if (products.empty()) {
        std::cout << "Склад пуст.\n";
        return;
    }

    for (const auto& product : products) {
        std::cout << product.toString() << '\n';
    }
}