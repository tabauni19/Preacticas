#pragma once
#include "Vehiculo.h"

class Auto : public Vehiculo {
private:
    int capacidadPasajeros;
    int puertas;
    double capacidadMaletero; // litros
public:
    Auto(const std::string& marca, const std::string& modelo, const std::string& placa,
         int capacidadPasajeros, int puertas, double capacidadMaletero, double tarifaPorDia, bool disponible = true);
    void mostrarInformacion(std::ostream& os) const override;
};
