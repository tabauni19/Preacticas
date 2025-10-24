#include "Libro.h"

Libro::Libro(const std::string& titulo, const std::string& autor, const std::string& isbn, bool disponible)
    : titulo(titulo), autor(autor), isbn(isbn), disponible(disponible) {}

const std::string& Libro::getTitulo() const { return titulo; }
const std::string& Libro::getAutor() const { return autor; }
const std::string& Libro::getISBN() const { return isbn; }
bool Libro::estaDisponible() const { return disponible; }

void Libro::setDisponible(bool estado) { disponible = estado; }
