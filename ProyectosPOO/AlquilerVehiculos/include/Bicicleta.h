#pragma once
#include "Vehiculo.h"

class Bicicleta : public Vehiculo {
private:
    bool electrica;
    int marchas;
    std::string tipoFreno; // disco, zapata
public:
    Bicicleta(const std::string& marca, const std::string& modelo, const std::string& placa,
              bool electrica, int marchas, const std::string& tipoFreno, double tarifaPorDia, bool disponible = true);
    void mostrarInformacion(std::ostream& os) const override;
};
