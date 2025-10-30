#include "Vehiculo.h"

Vehiculo::Vehiculo(std::string marca, std::string modelo, std::string placa)
    : marca_(std::move(marca)),
      modelo_(std::move(modelo)),
      placa_(std::move(placa)),
      disponible_(true) {}

const std::string& Vehiculo::obtenerMarca() const {
    return marca_;
}

const std::string& Vehiculo::obtenerModelo() const {
    return modelo_;
}

const std::string& Vehiculo::obtenerPlaca() const {
    return placa_;
}

bool Vehiculo::estaDisponible() const {
    return disponible_;
}

void Vehiculo::establecerDisponibilidad(bool disponible) {
    disponible_ = disponible;
}

void Vehiculo::mostrarInformacion(std::ostream& os) const {
    os << "Marca: " << marca_
       << " | Modelo: " << modelo_
       << " | Placa: " << placa_;
}
