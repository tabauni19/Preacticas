#include "Auto.h"

#include <ostream>

Auto::Auto(std::string marca, std::string modelo, std::string placa, int capacidadPasajeros)
    : Vehiculo(std::move(marca), std::move(modelo), std::move(placa)),
      capacidadPasajeros_(capacidadPasajeros) {}

int Auto::obtenerCapacidadPasajeros() const {
    return capacidadPasajeros_;
}

void Auto::mostrarInformacion(std::ostream& os) const {
    Vehiculo::mostrarInformacion(os);
    os << " | Pasajeros: " << capacidadPasajeros_;
}
