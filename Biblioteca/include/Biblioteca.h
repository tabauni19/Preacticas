#pragma once

#include "Libro.h"

#include <ostream>
#include <string>
#include <vector>

class Biblioteca {
public:
    bool agregarLibro(const Libro& libro);
    bool eliminarLibro(const std::string& isbn);

    std::vector<Libro> buscarPorTitulo(const std::string& titulo) const;
    std::vector<Libro> buscarPorAutor(const std::string& autor) const;

    std::vector<Libro> obtenerDisponibles() const;
    void mostrarDisponibles(std::ostream& os) const;

private:
    std::vector<Libro> libros_;
};
