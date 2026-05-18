#ifndef FILE_IO_H
#define FILE_IO_H

#include "Warehouse.h"

#include <string>

class FileIO {
public:
    static void saveToFile(const Warehouse& warehouse,
                           const std::string& filename);

    static void loadFromFile(Warehouse& warehouse,
                             const std::string& filename);
};

#endif