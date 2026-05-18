cmake_minimum_required(VERSION 3.10)

project(WarehouseApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(WarehouseApp
    src/main.cpp
    src/Product.cpp
    src/Warehouse.cpp
    src/FileIO.cpp
    src/Menu.cpp
)