#include "Auto.h"
#include "Bicicleta.h"
#include "SistemaAlquiler.h"

#include <iostream>
#include <memory>

int main() {
    SistemaAlquiler sistema;

    sistema.registrarVehiculo(std::make_unique<Auto>("Toyota", "Corolla", "ABC-123", 5));
    sistema.registrarVehiculo(std::make_unique<Bicicleta>("Giant", "Escape 3", "BIKE-001", false));
    sistema.registrarVehiculo(std::make_unique<Bicicleta>("Specialized", "Turbo Vado", "BIKE-002", true));

    std::cout << "Vehículos disponibles inicialmente:\n";
    sistema.mostrarDisponibles(std::cout);

    sistema.alquilarVehiculo("ABC-123");
    std::cout << "\nDespués de alquilar el auto ABC-123:\n";
    sistema.mostrarDisponibles(std::cout);

    sistema.devolverVehiculo("ABC-123");
    std::cout << "\nTras devolver el auto ABC-123:\n";
    sistema.mostrarDisponibles(std::cout);

    return 0;
}
