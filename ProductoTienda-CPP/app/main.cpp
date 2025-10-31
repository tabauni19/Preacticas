#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>
#include "Producto.h"

int main() {
    try {
        std::vector<Producto> catalogo;
        catalogo.emplace_back("Audifonos Inalambricos", 149900.0f, 30, 10);
        catalogo.emplace_back("Teclado Mecanico", 239900.0f, 12, 0);
        catalogo.emplace_back("Mouse Gamer", 99900.0f, 25, 5);
        catalogo.emplace_back("Monitor 24\"", 799900.0f, 8, 15);

        // Mostrar estado inicial
        std::cout << "== Estado inicial ==\n";
        for (const auto& p : catalogo) {
            std::cout << p.resumenProducto() << "\n";
        }

        // Simulaciones: ventas, reabastecimiento y actualizaciones de precio
        float totalIngresos = 0.0f;

        // Venta 1: 3 audifonos
        totalIngresos += catalogo[0].vender(3);
        // Venta 2: 2 teclados
        totalIngresos += catalogo[1].vender(2);
        // Venta 3: 30 mouse (esta puede fallar si no hay stock suficiente)
        totalIngresos += catalogo[2].vender(30); // probablemente retorna 0

        // Reabastecer mouse y vender luego
        catalogo[2].reabastecer(10);
        totalIngresos += catalogo[2].vender(20);

        // Actualizar precio del monitor
        catalogo[3].actualizarPrecio(749900.0f);

        // Ajustar descuento del teclado
        catalogo[1].setDescuento(20);

        // Venta extra
        totalIngresos += catalogo[3].vender(1);

        // Valor total de inventario
        float valorInventario = 0.0f;
        for (const auto& p : catalogo) {
            valorInventario += p.consultarValorInventario();
        }

        std::cout << "\n== Estado final ==\n";
        for (const auto& p : catalogo) {
            std::cout << p.resumenProducto() << "\n";
        }
        std::cout << "\nIngresos totales por ventas: " << totalIngresos << "\n";
        std::cout << "Valor total del inventario: " << valorInventario << "\n";

        // BONO: Reporte .txt
        std::ofstream reporte("reporte_inventario.txt");
        if (reporte) {
            reporte << "Nombre\tPrecio\tValorInventario\n";
            for (const auto& p : catalogo) {
                reporte << p.nombre() << "\t" << p.precio()
                        << "\t" << p.consultarValorInventario() << "\n";
            }
            reporte << "TOTAL\t-\t" << valorInventario << "\n";
            std::cout << "Reporte generado: reporte_inventario.txt\n";
        } else {
            std::cerr << "No se pudo crear el reporte.\n";
        }

        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }
}