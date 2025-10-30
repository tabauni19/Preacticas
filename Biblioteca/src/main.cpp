#include "Biblioteca.h"
#include "Libro.h"

#include <iostream>

int main() {
    Biblioteca biblioteca;

    biblioteca.agregarLibro(Libro("Cien años de soledad", "Gabriel García Márquez", "9780060883287"));
    biblioteca.agregarLibro(Libro("Ficciones", "Jorge Luis Borges", "9780670840908"));
    biblioteca.agregarLibro(Libro("La ciudad y los perros", "Mario Vargas Llosa", "9788432220194", false));

    biblioteca.mostrarDisponibles(std::cout);

    std::cout << "\nBuscando por autor 'Borges':\n";
    for (const auto& libro : biblioteca.buscarPorAutor("Borges")) {
        std::cout << " - " << libro.obtenerTitulo() << '\n';
    }

    biblioteca.eliminarLibro("9780060883287");
    std::cout << "\nDespués de eliminar un libro:\n";
    biblioteca.mostrarDisponibles(std::cout);

    return 0;
}
