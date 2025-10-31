#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>
#include <stdexcept>

/**
 * @brief Representa un producto dentro del inventario de una tienda en línea.
 *
 * La clase mantiene información del nombre, precio, unidades en inventario (stock)
 * y un descuento entero en porcentaje (0-100). Provee operaciones para vender,
 * reabastecer, actualizar precio, consultar valor de inventario y obtener un resumen
 * del producto.
 */
class Producto {
private:
    std::string nombre_;   /**< Nombre del producto. */
    float precio_;         /**< Precio unitario en moneda local. */
    int stock_;            /**< Unidades disponibles en inventario. */
    int descuento_;        /**< Descuento aplicado en porcentaje (0-100). */

public:
    /**
     * @brief Constructor que inicializa todos los atributos.
     * @param nombre Nombre del producto.
     * @param precio Precio unitario. Debe ser >= 0.
     * @param stock Unidades iniciales. Debe ser >= 0.
     * @param descuento Descuento en porcentaje (0-100).
     * @throw std::invalid_argument si algún parámetro es inválido.
     */
    Producto(const std::string& nombre, float precio, int stock, int descuento);

    /**
     * @brief Actualiza el precio del producto. (Implementado en el .h como ejemplo)
     * @param nuevoPrecio Nuevo precio unitario. Debe ser >= 0.
     * @throw std::invalid_argument si el nuevo precio es negativo.
     */
    inline void actualizarPrecio(float nuevoPrecio) {
        if (nuevoPrecio < 0.0f) {
            throw std::invalid_argument("El precio no puede ser negativo.");
        }
        precio_ = nuevoPrecio;
    }

    /**
     * @brief Retorna un resumen legible del estado del producto.
     * @return Cadena con nombre, precio, stock y descuento.
     */
    std::string resumenProducto() const;

    /**
     * @brief Intenta vender cierta cantidad de unidades.
     *
     * Si hay stock suficiente, descuenta del inventario y calcula el valor
     * de la venta considerando el descuento.
     *
     * @param cantidad Unidades a vender. Debe ser > 0.
     * @return Valor total de la venta. Si no hay stock suficiente retorna 0 y no modifica el inventario.
     * @throw std::invalid_argument si la cantidad es <= 0.
     */
    float vender(int cantidad);

    /**
     * @brief Incrementa el inventario en la cantidad indicada.
     * @param cantidad Unidades a añadir. Debe ser > 0.
     * @throw std::invalid_argument si la cantidad es <= 0.
     */
    void reabastecer(int cantidad);

    /**
     * @brief Calcula el valor total de inventario del producto.
     * @return precio × stock.
     */
    float consultarValorInventario() const;

    // --- Getters básicos ---
    /// @return Nombre del producto.
    const std::string& nombre() const { return nombre_; }
    /// @return Precio unitario actual.
    float precio() const { return precio_; }
    /// @return Unidades disponibles.
    int stock() const { return stock_; }
    /// @return Descuento (%) aplicado.
    int descuento() const { return descuento_; }

    // --- Setters seguros ---
    /**
     * @brief Cambia el porcentaje de descuento.
     * @param nuevoDescuento Porcentaje en [0,100].
     * @throw std::invalid_argument si está fuera de rango.
     */
    void setDescuento(int nuevoDescuento);
};

#endif // PRODUCTO_H