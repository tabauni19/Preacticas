cmake_minimum_required(VERSION 3.16)
project(Biblioteca VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(biblioteca
    src/main.cpp
    src/Libro.cpp
    src/Biblioteca.cpp
)

target_include_directories(biblioteca
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
