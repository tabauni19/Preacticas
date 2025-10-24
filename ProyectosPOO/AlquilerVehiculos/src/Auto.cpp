#include "Auto.h"
#include <iostream>
#include <iomanip>

Auto::Auto(const std::string& marca, const std::string& modelo, const std::string& placa,
           int capacidadPasajeros, int puertas, double capacidadMaletero, double tarifaPorDia, bool disponible)
    : Vehiculo(marca, modelo, placa, tarifaPorDia, disponible),
      capacidadPasajeros(capacidadPasajeros), puertas(puertas), capacidadMaletero(capacidadMaletero) {}

void Auto::mostrarInformacion(std::ostream& os) const {
    os << "[Auto] " << marca << " " << modelo
       << " | placa " << placa
       << " | " << capacidadPasajeros << " pax | " << puertas << " puertas"
       << " | maletero " << capacidadMaletero << " L"
       << " | tarifa/día $" << std::fixed << std::setprecision(2) << tarifaPorDia
       << " | " << (disponible ? "Disponible" : "Alquilado");
}
