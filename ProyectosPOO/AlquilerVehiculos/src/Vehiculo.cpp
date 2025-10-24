#include "Vehiculo.h"

Vehiculo::Vehiculo(const std::string& marca, const std::string& modelo, const std::string& placa, double tarifaPorDia, bool disponible)
    : marca(marca), modelo(modelo), placa(placa), disponible(disponible), tarifaPorDia(tarifaPorDia) {}

const std::string& Vehiculo::getMarca() const { return marca; }
const std::string& Vehiculo::getModelo() const { return modelo; }
const std::string& Vehiculo::getPlaca() const { return placa; }
bool Vehiculo::estaDisponible() const { return disponible; }
void Vehiculo::setDisponible(bool d) { disponible = d; }
double Vehiculo::getTarifaPorDia() const { return tarifaPorDia; }
