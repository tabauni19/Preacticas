#include "SistemaAlquiler.h"

#include <iostream>

void SistemaAlquiler::registrarVehiculo(std::unique_ptr<Vehiculo> vehiculo) {
    vehiculos_.push_back(std::move(vehiculo));
}

bool SistemaAlquiler::alquilarVehiculo(const std::string& placa) {
    if (auto* vehiculo = encontrarVehiculo(placa)) {
        if (vehiculo->estaDisponible()) {
            vehiculo->establecerDisponibilidad(false);
            return true;
        }
    }
    return false;
}

bool SistemaAlquiler::devolverVehiculo(const std::string& placa) {
    if (auto* vehiculo = encontrarVehiculo(placa)) {
        if (!vehiculo->estaDisponible()) {
            vehiculo->establecerDisponibilidad(true);
            return true;
        }
    }
    return false;
}

void SistemaAlquiler::mostrarDisponibles(std::ostream& os) const {
    bool alguno = false;
    for (const auto& vehiculo : vehiculos_) {
        if (vehiculo->estaDisponible()) {
            vehiculo->mostrarInformacion(os);
            os << '\n';
            alguno = true;
        }
    }

    if (!alguno) {
        os << "No hay vehículos disponibles en este momento.\n";
    }
}

Vehiculo* SistemaAlquiler::encontrarVehiculo(const std::string& placa) {
    for (const auto& vehiculo : vehiculos_) {
        if (vehiculo->obtenerPlaca() == placa) {
            return vehiculo.get();
        }
    }
    return nullptr;
}

const Vehiculo* SistemaAlquiler::encontrarVehiculo(const std::string& placa) const {
    for (const auto& vehiculo : vehiculos_) {
        if (vehiculo->obtenerPlaca() == placa) {
            return vehiculo.get();
        }
    }
    return nullptr;
}
