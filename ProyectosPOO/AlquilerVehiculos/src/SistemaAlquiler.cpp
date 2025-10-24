#include "SistemaAlquiler.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

Vehiculo* SistemaAlquiler::encontrarEditable(const std::string& placa) {
    for (auto& v : flota) {
        if (v->getPlaca() == placa) return v.get();
    }
    return nullptr;
}

void SistemaAlquiler::registrarVehiculo(std::unique_ptr<Vehiculo> v) {
    flota.push_back(std::move(v));
}

bool SistemaAlquiler::alquilar(const std::string& placa, const std::string& cliente, int dias, std::string& motivo) {
    if (dias <= 0) { motivo = "Los días deben ser > 0."; return false; }
    Vehiculo* v = encontrarEditable(placa);
    if (!v) { motivo = "Vehículo no existe."; return false; }
    if (!v->estaDisponible()) { motivo = "No disponible."; return false; }

    double costo = v->getTarifaPorDia() * dias;
    v->setDisponible(false);
    registros.push_back(RegistroAlquiler{placa, cliente, dias, costo, true});
    motivo = "Alquiler registrado. Costo $" + std::to_string(costo);
    return true;
}

bool SistemaAlquiler::devolver(const std::string& placa, const std::string& cliente, std::string& motivo) {
    Vehiculo* v = encontrarEditable(placa);
    if (!v) { motivo = "Vehículo no existe."; return false; }
    if (v->estaDisponible()) { motivo = "El vehículo ya está disponible."; return false; }

    // Buscamos el último alquiler activo de este cliente/placa
    for (auto it = registros.rbegin(); it != registros.rend(); ++it) {
        if (it->placa == placa && it->cliente == cliente && it->activo) {
            it->activo = false;
            v->setDisponible(true);
            motivo = "Devolución OK. Costo final $" + std::to_string(it->costo);
            return true;
        }
    }
    motivo = "No se encontró un alquiler activo para ese cliente y placa.";
    return false;
}

void SistemaAlquiler::mostrarDisponibles() const {
    std::cout << "Vehículos disponibles:\n";
    for (const auto& v : flota) {
        if (v->estaDisponible()) {
            v->mostrarInformacion(std::cout);
            std::cout << "\n";
        }
    }
}

void SistemaAlquiler::listarFlota() const {
    std::cout << "Flota completa:\n";
    for (const auto& v : flota) {
        v->mostrarInformacion(std::cout);
        std::cout << "\n";
    }
}

void SistemaAlquiler::listarRegistros() const {
    std::cout << "Registros de alquiler:\n";
    for (const auto& r : registros) {
        std::cout << " - " << r.cliente << " | " << r.placa
                  << " | " << r.dias << " días | $" << std::fixed << std::setprecision(2) << r.costo
                  << " | " << (r.activo ? "ACTIVO" : "CERRADO") << "\n";
    }
}
