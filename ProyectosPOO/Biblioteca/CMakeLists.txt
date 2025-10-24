cmake_minimum_required(VERSION 3.16)
project(Biblioteca)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(Biblioteca
    src/main.cpp
    src/Libro.cpp
    src/Biblioteca.cpp
    src/Usuario.cpp
)
