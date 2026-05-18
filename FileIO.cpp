#include "FileIO.h"

#include <fstream>
#include <iostream>
#include <sstream>

void FileIO::saveToFile(const Warehouse& warehouse,
                        const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла для записи.\n";
        return;
    }

    for (const auto& product : warehouse.getProductsConst()) {
        file << product.getId() << ','
             << product.getName() << ','
             << product.getCategory() << ','
             << product.getPrice() << ','
             << product.getQuantity() << '\n';
    }

    file.close();

    std::cout << "Данные успешно сохранены.\n";
}

void FileIO::loadFromFile(Warehouse& warehouse,
                          const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Файл не найден. Будет создан новый.\n";
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);

        std::string idStr;
        std::string name;
        std::string category;
        std::string priceStr;
        std::string quantityStr;

        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, category, ',');
        std::getline(ss, priceStr, ',');
        std::getline(ss, quantityStr, ',');

        try {
            int id = std::stoi(idStr);
            double price = std::stod(priceStr);
            int quantity = std::stoi(quantityStr);

            Product product(id,
                            name,
                            category,
                            price,
                            quantity);

            warehouse.getProducts().push_back(product);
        }
        catch (...) {
            std::cout << "Ошибка чтения строки: " << line << '\n';
        }
    }

    file.close();

    std::cout << "Данные успешно загружены.\n";
}