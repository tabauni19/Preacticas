#pragma once

#include "Vehiculo.h"

class Auto : public Vehiculo {
public:
    Auto(std::string marca, std::string modelo, std::string placa, int capacidadPasajeros);

    int obtenerCapacidadPasajeros() const;
    void mostrarInformacion(std::ostream& os) const override;

private:
    int capacidadPasajeros_;
};
