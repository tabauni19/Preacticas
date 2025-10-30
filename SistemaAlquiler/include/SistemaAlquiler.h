#pragma once

#include "Vehiculo.h"

#include <memory>
#include <ostream>
#include <string>
#include <vector>

class SistemaAlquiler {
public:
    void registrarVehiculo(std::unique_ptr<Vehiculo> vehiculo);
    bool alquilarVehiculo(const std::string& placa);
    bool devolverVehiculo(const std::string& placa);

    void mostrarDisponibles(std::ostream& os) const;

private:
    Vehiculo* encontrarVehiculo(const std::string& placa);
    const Vehiculo* encontrarVehiculo(const std::string& placa) const;

    std::vector<std::unique_ptr<Vehiculo>> vehiculos_;
};
