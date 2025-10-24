#include "Biblioteca.h"
#include <iostream>

int main() {
    Biblioteca b;
    // Alta de libros
    b.agregarLibro(Libro("Cien años de soledad", "Gabriel Garcia Marquez", "978-0307474728"));
    b.agregarLibro(Libro("El Principito", "Antoine de Saint-Exupery", "978-0156012195"));
    b.agregarLibro(Libro("Clean Code", "Robert C. Martin", "978-0132350884"));
    b.agregarLibro(Libro("Introducción a la Programación", "Teo Tabares", "TEO-001"));

    std::cout << "== TODOS ==\n";
    b.listarTodos();

    // Búsqueda parcial (case-insensitive)
    std::cout << "\n== BUSCAR POR TITULO: 'clean' ==\n";
    for (const auto& l : b.buscarPorTitulo("clean")) {
        std::cout << l.getTitulo() << " (" << l.getISBN() << ")\n";
    }

    // Préstamos con límites
    Estudiante e("Teo");
    Profesor p("Profe Adriana");

    std::string motivo;
    std::cout << "\n== PRESTAMOS (Estudiante limite 3) ==\n";
    for (auto isbn : {"978-0307474728", "978-0156012195", "978-0132350884", "TEO-001"}) {
        bool ok = b.prestarLibro(isbn, e, motivo);
        std::cout << "Prestando " << isbn << ": " << (ok ? "OK" : "FALLO") << " -> " << motivo << "\n";
    }
    std::cout << "Prestamos actuales de " << e.getNombre() << ": " << b.cantidadPrestamos(e.getNombre()) << "\n";

    // Devolución
    bool dev = b.devolverLibro("978-0156012195", e.getNombre(), motivo);
    std::cout << "Devolver 978-0156012195: " << (dev ? "OK" : "FALLO") << " -> " << motivo << "\n";

    // Profesor con mayor límite
    bool okp = b.prestarLibro("TEO-001", p, motivo);
    std::cout << "Prestando TEO-001 a profesor: " << (okp ? "OK" : "FALLO") << " -> " << motivo << "\n";

    std::cout << "\n== DISPONIBLES ==\n";
    for (const auto& l : b.obtenerDisponibles()) {
        std::cout << l.getTitulo() << " - " << l.getAutor() << "\n";
    }
    return 0;
}
