#include "Menu.h"
#include "FileIO.h"

#include <iostream>

void Menu::addProduct() {
    int id;
    std::string name;
    std::string category;
    double price;
    int quantity;

    std::cout << "Введите ID: ";
    std::cin >> id;

    std::cin.ignore();

    std::cout << "Введите название: ";
    std::getline(std::cin, name);

    std::cout << "Введите категорию: ";
    std::getline(std::cin, category);

    std::cout << "Введите цену: ";
    std::cin >> price;

    std::cout << "Введите количество: ";
    std::cin >> quantity;

    Product product(id, name, category, price, quantity);

    warehouse.addProduct(product);
}

void Menu::editProduct() {
    int id;

    std::cout << "Введите ID товара: ";
    std::cin >> id;

    std::cin.ignore();

    std::string name;
    std::string category;
    double price;
    int quantity;

    std::cout << "Введите новое название: ";
    std::getline(std::cin, name);

    std::cout << "Введите новую категорию: ";
    std::getline(std::cin, category);

    std::cout << "Введите новую цену: ";
    std::cin >> price;

    std::cout << "Введите новое количество: ";
    std::cin >> quantity;

    if (warehouse.editProduct(id,
                              name,
                              category,
                              price,
                              quantity)) {
        std::cout << "Товар обновлён.\n";
    }
    else {
        std::cout << "Ошибка обновления товара.\n";
    }
}

void Menu::deleteProduct() {
    int id;

    std::cout << "Введите ID товара: ";
    std::cin >> id;

    if (warehouse.deleteProductById(id)) {
        std::cout << "Товар удалён.\n";
    }
    else {
        std::cout << "Товар не найден.\n";
    }
}

void Menu::searchProduct() {
    std::cin.ignore();

    std::string name;

    std::cout << "Введите название: ";
    std::getline(std::cin, name);

    auto result = warehouse.searchByName(name);

    for (const auto& product : result) {
        std::cout << product.toString() << '\n';
    }
}

void Menu::filterProducts() {
    int choice;

    std::cout << "1. По категории\n";
    std::cout << "2. По диапазону цен\n";
    std::cout << "Выбор: ";

    std::cin >> choice;

    if (choice == 1) {
        std::cin.ignore();

        std::string category;

        std::cout << "Введите категорию: ";
        std::getline(std::cin, category);

        auto result = warehouse.filterByCategory(category);

        for (const auto& product : result) {
            std::cout << product.toString() << '\n';
        }
    }
    else if (choice == 2) {
        double minPrice;
        double maxPrice;

        std::cout << "Минимальная цена: ";
        std::cin >> minPrice;

        std::cout << "Максимальная цена: ";
        std::cin >> maxPrice;

        auto result = warehouse.filterByPrice(minPrice,
                                              maxPrice);

        for (const auto& product : result) {
            std::cout << product.toString() << '\n';
        }
    }
}

void Menu::sortProducts() {
    int choice;

    std::cout << "1. По цене (возрастание)\n";
    std::cout << "2. По цене (убывание)\n";
    std::cout << "3. По количеству\n";
    std::cout << "4. По названию\n";
    std::cout << "Выбор: ";

    std::cin >> choice;

    switch (choice) {
        case 1:
            warehouse.sortByPrice(true);
            break;

        case 2:
            warehouse.sortByPrice(false);
            break;

        case 3:
            warehouse.sortByQuantity();
            break;

        case 4:
            warehouse.sortByName();
            break;

        default:
            std::cout << "Неверный выбор.\n";
            return;
    }

    warehouse.displayAllProducts();
}

void Menu::analytics() {
    std::cout << "\nОбщая стоимость склада: "
              << warehouse.getTotalValue()
              << "\n\n";

    std::cout << "Товары с остатком <= 5:\n";

    auto lowStock = warehouse.getLowStockProducts();

    for (const auto& product : lowStock) {
        std::cout << product.toString() << '\n';
    }

    std::cout << "\nТоп-3 дорогих товара:\n";

    auto expensive = warehouse.getTopExpensiveProducts();

    for (const auto& product : expensive) {
        std::cout << product.toString() << '\n';
    }
}

void Menu::saveData() {
    FileIO::saveToFile(warehouse,
                       "data/products.txt");
}

void Menu::run() {
    FileIO::loadFromFile(warehouse,
                         "data/products.txt");

    int choice;

    do {
        std::cout << "\n========== СКЛАД ==========" << '\n';
        std::cout << "1. Добавить товар\n";
        std::cout << "2. Редактировать товар\n";
        std::cout << "3. Удалить товар\n";
        std::cout << "4. Показать все товары\n";
        std::cout << "5. Поиск товара\n";
        std::cout << "6. Фильтрация\n";
        std::cout << "7. Сортировка\n";
        std::cout << "8. Аналитика\n";
        std::cout << "9. Сохранить\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите пункт: ";

        std::cin >> choice;

        switch (choice) {
            case 1:
                addProduct();
                break;

            case 2:
                editProduct();
                break;

            case 3:
                deleteProduct();
                break;

            case 4:
                warehouse.displayAllProducts();
                break;

            case 5:
                searchProduct();
                break;

            case 6:
                filterProducts();
                break;

            case 7:
                sortProducts();
                break;

            case 8:
                analytics();
                break;

            case 9:
                saveData();
                break;

            case 0:
                std::cout << "Выход из программы.\n";
                break;

            default:
                std::cout << "Неверный выбор.\n";
        }

    } while (choice != 0);
}