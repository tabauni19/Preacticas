#pragma once
#include "Libro.h"
#include "Usuario.h"
#include <vector>
#include <string>
#include <unordered_map>

struct Prestamo {
    std::string isbn;
    std::string usuario; // nombre del usuario
};

class Biblioteca {
private:
    std::vector<Libro> libros;
    // usuario -> lista de ISBN prestados
    std::unordered_map<std::string, std::vector<std::string>> prestamosPorUsuario;

    static std::string toLower(std::string s);
    Libro* encontrarLibroEditable(const std::string& isbn);

public:
    // Gestión de libros
    void agregarLibro(const Libro& libro);
    bool eliminarLibroPorISBN(const std::string& isbn);

    // Búsquedas (parciales, case-insensitive)
    std::vector<Libro> buscarPorTitulo(const std::string& titulo) const;
    std::vector<Libro> buscarPorAutor(const std::string& autor) const;

    // Disponibilidad y listado
    std::vector<Libro> obtenerDisponibles() const;
    void listarTodos() const;

    // Préstamos
    bool prestarLibro(const std::string& isbn, const Usuario& user, std::string& motivo);
    bool devolverLibro(const std::string& isbn, const std::string& nombreUsuario, std::string& motivo);
    std::vector<std::string> librosPrestadosPor(const std::string& nombreUsuario) const;
    int cantidadPrestamos(const std::string& nombreUsuario) const;
};
