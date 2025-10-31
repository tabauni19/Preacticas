# ProductoTienda-CPP

Solución (puntos 3 y 4) del parcial: clase `Producto`, su implementación y una app de consola que simula flujo de productos en una tienda en línea.

## Estructura

```
ProductoTienda-CPP/
├─ CMakeLists.txt
├─ include/
│  └─ Producto.h
├─ src/
│  └─ Producto.cpp
├─ app/
│  └─ main.cpp
└─ docs/
   └─ Doxyfile
```

## Compilación y ejecución

```bash
# Dentro de ProductoTienda-CPP
mkdir build && cd build
cmake ..
cmake --build .
./tienda_app   # en Windows: .\Debug\tienda_app.exe o .\tienda_app.exe
```

Al correr, se imprime el estado inicial/final, ingresos por ventas, y se genera `reporte_inventario.txt` (BONO).

## Doxygen (opcional)

Si tiene Doxygen instalado:
```bash
doxygen docs/Doxyfile
```
Los comentarios Doxygen están en `include/Producto.h`.