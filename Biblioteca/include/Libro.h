#pragma once

#include <string>

class Libro {
public:
    Libro(std::string titulo, std::string autor, std::string isbn, bool disponible = true);

    const std::string& obtenerTitulo() const;
    const std::string& obtenerAutor() const;
    const std::string& obtenerIsbn() const;

    bool estaDisponible() const;
    void establecerDisponibilidad(bool disponible);

private:
    std::string titulo_;
    std::string autor_;
    std::string isbn_;
    bool disponible_;
};
