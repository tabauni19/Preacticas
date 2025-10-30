cmake_minimum_required(VERSION 3.16)
project(SistemaAlquiler VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(sistema_alquiler
    src/main.cpp
    src/Vehiculo.cpp
    src/Auto.cpp
    src/Bicicleta.cpp
    src/SistemaAlquiler.cpp
)

target_include_directories(sistema_alquiler
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
