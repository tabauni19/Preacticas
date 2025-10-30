#pragma once

#include <ostream>
#include <string>

class Vehiculo {
public:
    Vehiculo(std::string marca, std::string modelo, std::string placa);
    virtual ~Vehiculo() = default;

    const std::string& obtenerMarca() const;
    const std::string& obtenerModelo() const;
    const std::string& obtenerPlaca() const;

    bool estaDisponible() const;
    void establecerDisponibilidad(bool disponible);

    virtual void mostrarInformacion(std::ostream& os) const;

protected:
    std::string marca_;
    std::string modelo_;
    std::string placa_;
    bool disponible_;
};
