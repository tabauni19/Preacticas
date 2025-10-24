# Sistema de Gestión de Biblioteca (completo)

## Características
- **Libro**: título, autor, ISBN, estado `disponible`.
- **Biblioteca**:
  - Alta/baja de libros
  - Búsqueda parcial **case-insensitive** por título/autor
  - Listado de disponibles y de todos
  - **Préstamos y devoluciones** con verificación de límite por tipo de usuario
  - Consulta de libros prestados por usuario
- **Usuarios**: `Estudiante` (límite 3), `Profesor` (límite 5).

## Compilación y ejecución
```bash
mkdir build && cd build
cmake ..
cmake --build .
./Biblioteca
```

## Próximas mejoras sugeridas
- Persistencia (CSV/JSON) de inventario y préstamos.
- Fechas de préstamo y cálculo de mora.
- Reportes (top usuarios, libros más demandados).
