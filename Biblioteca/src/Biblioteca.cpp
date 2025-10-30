#include "Biblioteca.h"

#include <algorithm>
#include <iostream>

bool Biblioteca::agregarLibro(const Libro& libro) {
    const auto coincideIsbn = [&libro](const Libro& existente) {
        return existente.obtenerIsbn() == libro.obtenerIsbn();
    };

    if (std::any_of(libros_.begin(), libros_.end(), coincideIsbn)) {
        return false;
    }

    libros_.push_back(libro);
    return true;
}

bool Biblioteca::eliminarLibro(const std::string& isbn) {
    const auto original = libros_.size();

    libros_.erase(
        std::remove_if(libros_.begin(), libros_.end(), [&isbn](const Libro& libro) {
            return libro.obtenerIsbn() == isbn;
        }),
        libros_.end());

    return libros_.size() != original;
}

std::vector<Libro> Biblioteca::buscarPorTitulo(const std::string& titulo) const {
    std::vector<Libro> resultados;
    for (const auto& libro : libros_) {
        if (libro.obtenerTitulo().find(titulo) != std::string::npos) {
            resultados.push_back(libro);
        }
    }
    return resultados;
}

std::vector<Libro> Biblioteca::buscarPorAutor(const std::string& autor) const {
    std::vector<Libro> resultados;
    for (const auto& libro : libros_) {
        if (libro.obtenerAutor().find(autor) != std::string::npos) {
            resultados.push_back(libro);
        }
    }
    return resultados;
}

std::vector<Libro> Biblioteca::obtenerDisponibles() const {
    std::vector<Libro> disponibles;
    for (const auto& libro : libros_) {
        if (libro.estaDisponible()) {
            disponibles.push_back(libro);
        }
    }
    return disponibles;
}

void Biblioteca::mostrarDisponibles(std::ostream& os) const {
    const auto disponibles = obtenerDisponibles();
    if (disponibles.empty()) {
        os << "No hay libros disponibles por ahora.\n";
        return;
    }

    os << "Libros disponibles:\n";
    for (const auto& libro : disponibles) {
        os << " - " << libro.obtenerTitulo()
           << " | Autor: " << libro.obtenerAutor()
           << " | ISBN: " << libro.obtenerIsbn()
           << '\n';
    }
}
