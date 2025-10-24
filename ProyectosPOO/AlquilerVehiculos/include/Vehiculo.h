#pragma once
#include <string>
#include <iostream>

class Vehiculo {
protected:
    std::string marca;
    std::string modelo;
    std::string placa;
    bool disponible;
    double tarifaPorDia;
public:
    Vehiculo(const std::string& marca, const std::string& modelo, const std::string& placa, double tarifaPorDia, bool disponible = true);
    virtual ~Vehiculo() = default;

    const std::string& getMarca() const;
    const std::string& getModelo() const;
    const std::string& getPlaca() const;
    bool estaDisponible() const;
    void setDisponible(bool d);
    double getTarifaPorDia() const;

    virtual void mostrarInformacion(std::ostream& os) const = 0;
};
