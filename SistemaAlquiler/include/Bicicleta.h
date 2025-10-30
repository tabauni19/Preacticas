#pragma once

#include "Vehiculo.h"

class Bicicleta : public Vehiculo {
public:
    Bicicleta(std::string marca, std::string modelo, std::string placa, bool electrica);

    bool esElectrica() const;
    void mostrarInformacion(std::ostream& os) const override;

private:
    bool esElectrica_;
};
