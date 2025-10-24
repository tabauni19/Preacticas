#include "SistemaAlquiler.h"
#include "Auto.h"
#include "Bicicleta.h"
#include <iostream>
#include <memory>

int main() {
    SistemaAlquiler s;
    s.registrarVehiculo(std::make_unique<Auto>("Toyota", "Corolla", "ABC123", 5, 4, 470.0, 150000.0));
    s.registrarVehiculo(std::make_unique<Bicicleta>("GW", "AllTerra", "BICI-001", false, 18, "disco", 35000.0));
    s.registrarVehiculo(std::make_unique<Bicicleta>("Xiaomi", "Mi E-Bike", "BICI-EL-09", true, 7, "disco", 65000.0));

    s.listarFlota();

    std::string motivo;
    std::cout << "\n--- Alquilando ABC123 por 3 días a 'Teo' ---\n";
    std::cout << (s.alquilar("ABC123", "Teo", 3, motivo) ? "OK: " : "FALLO: ") << motivo << "\n";

    std::cout << "\n--- Disponibles ---\n";
    s.mostrarDisponibles();

    std::cout << "\n--- Devolviendo ABC123 de 'Teo' ---\n";
    std::cout << (s.devolver("ABC123", "Teo", motivo) ? "OK: " : "FALLO: ") << motivo << "\n";

    std::cout << "\n--- Registros ---\n";
    s.listarRegistros();
    return 0;
}
