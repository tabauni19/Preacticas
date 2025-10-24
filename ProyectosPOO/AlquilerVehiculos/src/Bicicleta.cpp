#include "Bicicleta.h"
#include <iostream>
#include <iomanip>

Bicicleta::Bicicleta(const std::string& marca, const std::string& modelo, const std::string& placa,
                     bool electrica, int marchas, const std::string& tipoFreno, double tarifaPorDia, bool disponible)
    : Vehiculo(marca, modelo, placa, tarifaPorDia, disponible),
      electrica(electrica), marchas(marchas), tipoFreno(tipoFreno) {}

void Bicicleta::mostrarInformacion(std::ostream& os) const {
    os << "[Bicicleta] " << marca << " " << modelo
       << " | id " << placa
       << " | " << (electrica ? "Eléctrica" : "Convencional")
       << " | " << marchas << " marchas"
       << " | freno " << tipoFreno
       << " | tarifa/día $" << std::fixed << std::setprecision(2) << tarifaPorDia
       << " | " << (disponible ? "Disponible" : "Alquilada");
}
