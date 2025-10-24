# Sistema de Alquiler de Vehículos (completo)

## Características
- **Vehiculo** base con `tarifaPorDia` y método virtual `mostrarInformacion`.
- **Auto**: pasajeros, puertas, maletero (L).
- **Bicicleta**: eléctrica/convencional, marchas, tipo de freno.
- **SistemaAlquiler**:
  - Registro de vehículos (`std::unique_ptr`)
  - Alquiler con cálculo de costo (tarifa × días)
  - Devolución (cierra alquiler activo)
  - Listado de disponibles, flota completa y registros de alquiler.

## Compilación y ejecución
```bash
mkdir build && cd build
cmake ..
cmake --build .
./AlquilerVehiculos
```

## Posibles mejoras
- Tarifas variables por temporada o promociones.
- Multas por retraso y cálculo por horas.
- Persistencia (CSV/JSON) de flota y registros.
