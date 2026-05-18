#ifndef MENU_H
#define MENU_H

#include "Warehouse.h"

class Menu {
private:
    Warehouse warehouse;

    void addProduct();
    void editProduct();
    void deleteProduct();
    void searchProduct();
    void filterProducts();
    void sortProducts();
    void analytics();
    void saveData();

public:
    void run();
};

#endif