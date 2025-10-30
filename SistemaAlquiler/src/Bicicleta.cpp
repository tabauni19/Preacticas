#include "Bicicleta.h"

Bicicleta::Bicicleta(std::string marca, std::string modelo, std::string placa, bool electrica)
    : Vehiculo(std::move(marca), std::move(modelo), std::move(placa)),
      esElectrica_(electrica) {}

bool Bicicleta::esElectrica() const {
    return esElectrica_;
}

void Bicicleta::mostrarInformacion(std::ostream& os) const {
    Vehiculo::mostrarInformacion(os);
    os << " | Tipo: " << (esElectrica_ ? "Eléctrica" : "Convencional");
}
