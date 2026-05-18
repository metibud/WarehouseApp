#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "Product.h"

#include <vector>

class Warehouse {
private:
    std::vector<Product> products;

    bool isUniqueId(int id) const;

public:
    void addProduct(const Product& product);

    bool editProduct(int id,
                     const std::string& newName,
                     const std::string& newCategory,
                     double newPrice,
                     int newQuantity);

    bool deleteProductById(int id);

    std::vector<Product> searchByName(const std::string& name) const;

    std::vector<Product> filterByCategory(const std::string& category) const;

    std::vector<Product> filterByPrice(double minPrice,
                                       double maxPrice) const;

    void sortByPrice(bool ascending = true);
    void sortByQuantity();
    void sortByName();

    double getTotalValue() const;

    std::vector<Product> getLowStockProducts() const;

    std::vector<Product> getTopExpensiveProducts() const;

    std::vector<Product>& getProducts();

    const std::vector<Product>& getProductsConst() const;

    void displayAllProducts() const;
};

#endif