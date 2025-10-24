#include "Usuario.h"

Usuario::Usuario(const std::string& nombre, int limite) : nombre(nombre), limitePrestamos(limite) {}
const std::string& Usuario::getNombre() const { return nombre; }
int Usuario::getLimitePrestamos() const { return limitePrestamos; }

Estudiante::Estudiante(const std::string& nombre) : Usuario(nombre, 3) {}
Profesor::Profesor(const std::string& nombre) : Usuario(nombre, 5) {}
