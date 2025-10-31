cmake_minimum_required(VERSION 3.12)
project(ProductoTiendaCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Library
add_library(producto STATIC
    src/Producto.cpp
)
target_include_directories(producto PUBLIC include)

# App
add_executable(tienda_app app/main.cpp)
target_link_libraries(tienda_app PRIVATE producto)

# Doxygen (optional)
find_package(Doxygen QUIET)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/docs)
    file(MAKE_DIRECTORY ${DOXYGEN_OUT})
    add_custom_target(doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
endif()