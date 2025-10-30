#include "Libro.h"

Libro::Libro(std::string titulo, std::string autor, std::string isbn, bool disponible)
    : titulo_(std::move(titulo)),
      autor_(std::move(autor)),
      isbn_(std::move(isbn)),
      disponible_(disponible) {}

const std::string& Libro::obtenerTitulo() const {
    return titulo_;
}

const std::string& Libro::obtenerAutor() const {
    return autor_;
}

const std::string& Libro::obtenerIsbn() const {
    return isbn_;
}

bool Libro::estaDisponible() const {
    return disponible_;
}

void Libro::establecerDisponibilidad(bool disponible) {
    disponible_ = disponible;
}
