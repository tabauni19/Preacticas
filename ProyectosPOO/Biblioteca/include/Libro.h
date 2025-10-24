#pragma once
#include <string>

class Libro {
private:
    std::string titulo;
    std::string autor;
    std::string isbn;
    bool disponible;
public:
    Libro(const std::string& titulo, const std::string& autor, const std::string& isbn, bool disponible = true);

    const std::string& getTitulo() const;
    const std::string& getAutor() const;
    const std::string& getISBN() const;
    bool estaDisponible() const;

    void setDisponible(bool estado);
};
