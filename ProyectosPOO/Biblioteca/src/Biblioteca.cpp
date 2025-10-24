#include "Biblioteca.h"
#include <iostream>
#include <algorithm>
#include <cctype>

std::string Biblioteca::toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::tolower(c); });
    return s;
}

Libro* Biblioteca::encontrarLibroEditable(const std::string& isbn) {
    for (auto& l : libros) {
        if (l.getISBN() == isbn) return &l;
    }
    return nullptr;
}

void Biblioteca::agregarLibro(const Libro& libro) {
    libros.push_back(libro);
}

bool Biblioteca::eliminarLibroPorISBN(const std::string& isbn) {
    auto it = std::remove_if(libros.begin(), libros.end(), [&](const Libro& l){
        return l.getISBN() == isbn;
    });
    bool eliminado = (it != libros.end());
    libros.erase(it, libros.end());
    return eliminado;
}

std::vector<Libro> Biblioteca::buscarPorTitulo(const std::string& titulo) const {
    std::vector<Libro> resultado;
    std::string filtro = toLower(titulo);
    for (const auto& l : libros) {
        if (toLower(l.getTitulo()).find(filtro) != std::string::npos) {
            resultado.push_back(l);
        }
    }
    return resultado;
}

std::vector<Libro> Biblioteca::buscarPorAutor(const std::string& autor) const {
    std::vector<Libro> resultado;
    std::string filtro = toLower(autor);
    for (const auto& l : libros) {
        if (toLower(l.getAutor()).find(filtro) != std::string::npos) {
            resultado.push_back(l);
        }
    }
    return resultado;
}

std::vector<Libro> Biblioteca::obtenerDisponibles() const {
    std::vector<Libro> disp;
    for (const auto& l : libros) {
        if (l.estaDisponible()) disp.push_back(l);
    }
    return disp;
}

void Biblioteca::listarTodos() const {
    std::cout << "Listado de libros (" << libros.size() << "):\n";
    for (const auto& l : libros) {
        std::cout << " - " << l.getTitulo() << " | " << l.getAutor()
                  << " | ISBN: " << l.getISBN()
                  << " | " << (l.estaDisponible() ? "Disponible" : "Prestado") << "\n";
    }
}

bool Biblioteca::prestarLibro(const std::string& isbn, const Usuario& user, std::string& motivo) {
    Libro* l = encontrarLibroEditable(isbn);
    if (!l) { motivo = "ISBN no encontrado."; return false; }
    if (!l->estaDisponible()) { motivo = "El libro ya está prestado."; return false; }

    auto& lista = prestamosPorUsuario[user.getNombre()];
    if ((int)lista.size() >= user.getLimitePrestamos()) {
        motivo = "Se alcanzó el límite de préstamos para el usuario.";
        return false;
    }

    l->setDisponible(false);
    lista.push_back(isbn);
    motivo = "Préstamo exitoso.";
    return true;
}

bool Biblioteca::devolverLibro(const std::string& isbn, const std::string& nombreUsuario, std::string& motivo) {
    Libro* l = encontrarLibroEditable(isbn);
    if (!l) { motivo = "ISBN no encontrado."; return false; }

    auto itUser = prestamosPorUsuario.find(nombreUsuario);
    if (itUser == prestamosPorUsuario.end()) { motivo = "El usuario no tiene préstamos registrados."; return false; }

    auto& lista = itUser->second;
    auto it = std::find(lista.begin(), lista.end(), isbn);
    if (it == lista.end()) { motivo = "Ese usuario no tiene este ISBN prestado."; return false; }

    lista.erase(it);
    l->setDisponible(true);
    motivo = "Devolución registrada.";
    return true;
}

std::vector<std::string> Biblioteca::librosPrestadosPor(const std::string& nombreUsuario) const {
    auto it = prestamosPorUsuario.find(nombreUsuario);
    if (it == prestamosPorUsuario.end()) return {};
    return it->second;
}

int Biblioteca::cantidadPrestamos(const std::string& nombreUsuario) const {
    auto it = prestamosPorUsuario.find(nombreUsuario);
    if (it == prestamosPorUsuario.end()) return 0;
    return (int)it->second.size();
}
