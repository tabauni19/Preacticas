#include "Producto.h"
#include <sstream>
#include <iomanip>

Producto::Producto(const std::string& nombre, float precio, int stock, int descuento)
    : nombre_(nombre), precio_(precio), stock_(stock), descuento_(descuento) {
    if (precio < 0.0f) throw std::invalid_argument("Precio negativo.");
    if (stock < 0) throw std::invalid_argument("Stock negativo.");
    if (descuento < 0 || descuento > 100) throw std::invalid_argument("Descuento fuera de rango.");
}

std::string Producto::resumenProducto() const {
    std::ostringstream os;
    os << "Producto: " << nombre_
       << " | Precio: " << std::fixed << std::setprecision(2) << precio_
       << " | Stock: " << stock_
       << " | Descuento: " << descuento_ << "%";
    return os.str();
}

float Producto::vender(int cantidad) {
    if (cantidad <= 0) throw std::invalid_argument("Cantidad de venta invalida.");
    if (cantidad > stock_) {
        // No hay suficientes unidades: no vendemos.
        return 0.0f;
    }
    // Calcular valor con descuento
    float subtotal = precio_ * static_cast<float>(cantidad);
    float factor_desc = 1.0f - (static_cast<float>(descuento_) / 100.0f);
    float total = subtotal * factor_desc;

    stock_ -= cantidad;
    return total;
}

void Producto::reabastecer(int cantidad) {
    if (cantidad <= 0) throw std::invalid_argument("Cantidad de reabastecimiento invalida.");
    stock_ += cantidad;
}

float Producto::consultarValorInventario() const {
    return precio_ * static_cast<float>(stock_);
}

void Producto::setDescuento(int nuevoDescuento) {
    if (nuevoDescuento < 0 || nuevoDescuento > 100)
        throw std::invalid_argument("Descuento fuera de rango [0,100].");
    descuento_ = nuevoDescuento;
}