#pragma once
#include <string>

class Usuario {
protected:
    std::string nombre;
    int limitePrestamos;
public:
    Usuario(const std::string& nombre, int limite);
    virtual ~Usuario() = default;

    const std::string& getNombre() const;
    int getLimitePrestamos() const;
};

class Estudiante : public Usuario {
public:
    Estudiante(const std::string& nombre);
};

class Profesor : public Usuario {
public:
    Profesor(const std::string& nombre);
};
