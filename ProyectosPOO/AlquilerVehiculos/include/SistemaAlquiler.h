#pragma once
#include "Vehiculo.h"
#include <vector>
#include <memory>
#include <string>
#include <optional>

struct RegistroAlquiler {
    std::string placa;
    std::string cliente;
    int dias = 0;
    double costo = 0.0;
    bool activo = true;
};

class SistemaAlquiler {
private:
    std::vector<std::unique_ptr<Vehiculo>> flota;
    std::vector<RegistroAlquiler> registros;
    Vehiculo* encontrarEditable(const std::string& placa);
public:
    void registrarVehiculo(std::unique_ptr<Vehiculo> v);
    bool alquilar(const std::string& placa, const std::string& cliente, int dias, std::string& motivo);
    bool devolver(const std::string& placa, const std::string& cliente, std::string& motivo);
    void mostrarDisponibles() const;
    void listarFlota() const;
    void listarRegistros() const;
};
