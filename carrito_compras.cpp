#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <ctime>
#include <limits>

using namespace std;

// ==================== CLASE PRODUCTO ====================
class Producto {
private:
    int id;
    string nombre;
    string categoria;
    double precio;
    int stock;

public:
    Producto(int i, string nom, string cat, double prec, int stk) 
        : id(i), nombre(nom), categoria(cat), precio(prec), stock(stk) {}
    
    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getCategoria() const { return categoria; }
    double getPrecio() const { return precio; }
    int getStock() const { return stock; }
    
    bool tieneStock(int cantidad) const {
        return stock >= cantidad;
    }
    
    bool reducirStock(int cantidad) {
        if (tieneStock(cantidad)) {
            stock -= cantidad;
            return true;
        }
        return false;
    }
    
    void aumentarStock(int cantidad) {
        stock += cantidad;
    }
    
    void mostrar() const {
        cout << "[" << id << "] " << left << setw(25) << nombre 
             << " | $" << right << setw(7) << fixed << setprecision(2) << precio 
             << " | Stock: " << setw(3) << stock << " | " << categoria;
    }
};

// ==================== CLASE ITEM CARRITO ====================
class ItemCarrito {
private:
    shared_ptr<Producto> producto;
    int cantidad;

public:
    ItemCarrito(shared_ptr<Producto> prod, int cant) 
        : producto(prod), cantidad(cant) {}
    
    shared_ptr<Producto> getProducto() const { return producto; }
    int getCantidad() const { return cantidad; }
    void setCantidad(int cant) { cantidad = cant; }
    
    double calcularSubtotal() const {
        return producto->getPrecio() * cantidad;
    }
    
    void mostrar() const {
        cout << "  " << left << setw(25) << producto->getNombre() 
             << " x" << setw(3) << cantidad 
             << " = $" << fixed << setprecision(2) << calcularSubtotal();
    }
};

// ==================== CLASE COMPRA ====================
class Compra {
private:
    vector<ItemCarrito> items;
    double total;
    time_t fecha;

public:
    Compra(const vector<ItemCarrito>& its, double tot) 
        : items(its), total(tot) {
        fecha = time(nullptr);
    }
    
    void mostrar() const {
        char buffer[80];
        struct tm* timeinfo = localtime(&fecha);
        strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M", timeinfo);
        
        cout << "  Fecha: " << buffer << " - Total: $" 
             << fixed << setprecision(2) << total << endl;
        cout << "  Productos: ";
        for (size_t i = 0; i < items.size(); i++) {
            cout << items[i].getProducto()->getNombre() 
                 << " x" << items[i].getCantidad();
            if (i < items.size() - 1) cout << ", ";
        }
        cout << endl;
    }
};

// ==================== CLASE CARRITO COMPRAS ====================
class CarritoCompras {
private:
    vector<ItemCarrito> items;

public:
    bool agregarProducto(shared_ptr<Producto> producto, int cantidad = 1) {
        if (!producto->tieneStock(cantidad)) {
            cout << "\n❌ Stock insuficiente para " << producto->getNombre() << endl;
            return false;
        }
        
        for (auto& item : items) {
            if (item.getProducto() == producto) {
                int nuevaCantidad = item.getCantidad() + cantidad;
                if (producto->tieneStock(nuevaCantidad)) {
                    item.setCantidad(nuevaCantidad);
                    cout << "\n✅ Agregado " << cantidad << " más. Total: " 
                         << nuevaCantidad << " unidades" << endl;
                    return true;
                } else {
                    cout << "\n❌ Stock insuficiente para agregar más unidades" << endl;
                    return false;
                }
            }
        }
        
        items.push_back(ItemCarrito(producto, cantidad));
        cout << "\n✅ " << producto->getNombre() << " agregado al carrito (" 
             << cantidad << " unidades)" << endl;
        return true;
    }
    
    bool eliminarProducto(int indice) {
        if (indice >= 0 && indice < (int)items.size()) {
            cout << "\n🗑️ " << items[indice].getProducto()->getNombre() 
                 << " eliminado del carrito" << endl;
            items.erase(items.begin() + indice);
            return true;
        }
        return false;
    }
    
    bool modificarCantidad(int indice, int nuevaCantidad) {
        if (indice >= 0 && indice < (int)items.size()) {
            if (nuevaCantidad <= 0) {
                return eliminarProducto(indice);
            }
            
            if (items[indice].getProducto()->tieneStock(nuevaCantidad)) {
                items[indice].setCantidad(nuevaCantidad);
                cout << "\n✏️ Cantidad actualizada a " << nuevaCantidad << endl;
                return true;
            } else {
                cout << "\n❌ Stock insuficiente" << endl;
                return false;
            }
        }
        return false;
    }
    
    double calcularTotal() const {
        double total = 0;
        for (const auto& item : items) {
            total += item.calcularSubtotal();
        }
        return total;
    }
    
    bool estaVacio() const {
        return items.empty();
    }
    
    void vaciar() {
        items.clear();
    }
    
    void mostrar() const {
        if (estaVacio()) {
            cout << "\n🛒 El carrito está vacío" << endl;
            return;
        }
        
        cout << "\n" << string(70, '=') << endl;
        cout << "🛒 MI CARRITO DE COMPRAS" << endl;
        cout << string(70, '=') << endl;
        for (size_t i = 0; i < items.size(); i++) {
            cout << "[" << i << "] ";
            items[i].mostrar();
            cout << endl;
        }
        cout << string(70, '-') << endl;
        cout << "  " << left << setw(30) << "TOTAL A PAGAR:" 
             << " $" << fixed << setprecision(2) << calcularTotal() << endl;
        cout << string(70, '=') << endl;
    }
    
    const vector<ItemCarrito>& getItems() const {
        return items;
    }
};

// ==================== CLASE USUARIO ====================
class Usuario {
private:
    string nombre;
    CarritoCompras carrito;
    vector<Compra> historialCompras;

public:
    Usuario(string nom) : nombre(nom) {}
    
    string getNombre() const { return nombre; }
    CarritoCompras& getCarrito() { return carrito; }
    
    bool finalizarCompra() {
        if (carrito.estaVacio()) {
            cout << "\n❌ No se puede finalizar: el carrito está vacío" << endl;
            return false;
        }
        
        for (const auto& item : carrito.getItems()) {
            if (!item.getProducto()->tieneStock(item.getCantidad())) {
                cout << "\n❌ Compra cancelada: stock insuficiente de " 
                     << item.getProducto()->getNombre() << endl;
                return false;
            }
        }
        
        for (const auto& item : carrito.getItems()) {
            item.getProducto()->reducirStock(item.getCantidad());
        }
        
        double total = carrito.calcularTotal();
        historialCompras.push_back(Compra(carrito.getItems(), total));
        
        cout << "\n" << string(50, '=') << endl;
        cout << "✅ ¡COMPRA FINALIZADA EXITOSAMENTE!" << endl;
        cout << string(50, '=') << endl;
        cout << "💰 Total pagado: $" << fixed << setprecision(2) << total << endl;
        cout << "🎉 ¡Gracias por su compra, " << nombre << "!" << endl;
        cout << string(50, '=') << endl;
        
        carrito.vaciar();
        return true;
    }
    
    void mostrarHistorial() const {
        if (historialCompras.empty()) {
            cout << "\n📋 No tienes compras registradas aún" << endl;
            return;
        }
        
        cout << "\n" << string(70, '=') << endl;
        cout << "📋 HISTORIAL DE COMPRAS - " << nombre << endl;
        cout << string(70, '=') << endl;
        for (size_t i = 0; i < historialCompras.size(); i++) {
            cout << "\nCompra #" << (i + 1) << ":" << endl;
            historialCompras[i].mostrar();
        }
        cout << string(70, '=') << endl;
    }
};

// ==================== CLASE SUPERMERCADO ====================
class Supermercado {
private:
    vector<shared_ptr<Producto>> productos;
    Usuario* usuarioActual;

    void limpiarBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void pausar() {
        cout << "\nPresiona ENTER para continuar...";
        cin.get();
    }

public:
    Supermercado() : usuarioActual(nullptr) {
        inicializarProductos();
    }
    
    void inicializarProductos() {
        productos.push_back(make_shared<Producto>(1, "Leche Entera 1L", "Lácteos", 2.50, 30));
        productos.push_back(make_shared<Producto>(2, "Pan Integral", "Panadería", 1.20, 50));
        productos.push_back(make_shared<Producto>(3, "Huevos x12", "Lácteos", 3.80, 25));
        productos.push_back(make_shared<Producto>(4, "Arroz 1kg", "Granos", 1.90, 40));
        productos.push_back(make_shared<Producto>(5, "Aceite de Oliva 500ml", "Aceites", 8.50, 15));
        productos.push_back(make_shared<Producto>(6, "Manzanas 1kg", "Frutas", 2.80, 35));
        productos.push_back(make_shared<Producto>(7, "Tomates 1kg", "Verduras", 2.20, 28));
        productos.push_back(make_shared<Producto>(8, "Pollo Entero", "Carnes", 6.50, 20));
        productos.push_back(make_shared<Producto>(9, "Pasta 500g", "Granos", 1.50, 45));
        productos.push_back(make_shared<Producto>(10, "Yogurt Natural", "Lácteos", 1.80, 32));
        productos.push_back(make_shared<Producto>(11, "Café 250g", "Bebidas", 5.20, 18));
        productos.push_back(make_shared<Producto>(12, "Atún en Lata", "Enlatados", 2.10, 40));
    }
    
    void mostrarProductos() {
        cout << "\n" << string(90, '=') << endl;
        cout << "🏪 PRODUCTOS DISPONIBLES EN EL SUPERMERCADO" << endl;
        cout << string(90, '=') << endl;
        for (const auto& prod : productos) {
            prod->mostrar();
            cout << endl;
        }
        cout << string(90, '=') << endl;
    }
    
    void mostrarProductosPorCategoria(const string& categoria) {
        cout << "\n📦 Productos en categoría: " << categoria << endl;
        cout << string(90, '-') << endl;
        bool encontrado = false;
        for (const auto& prod : productos) {
            if (prod->getCategoria() == categoria) {
                prod->mostrar();
                cout << endl;
                encontrado = true;
            }
        }
        if (!encontrado) {
            cout << "No hay productos en esta categoría" << endl;
        }
    }
    
    shared_ptr<Producto> buscarProductoPorId(int id) {
        for (auto& prod : productos) {
            if (prod->getId() == id) {
                return prod;
            }
        }
        return nullptr;
    }
    
    void menuAgregarProducto() {
        mostrarProductos();
        
        int id, cantidad;
        cout << "\nIngresa el ID del producto (0 para cancelar): ";
        cin >> id;
        
        if (id == 0) return;
        
        auto producto = buscarProductoPorId(id);
        if (!producto) {
            cout << "\n❌ Producto no encontrado" << endl;
            limpiarBuffer();
            pausar();
            return;
        }
        
        cout << "Ingresa la cantidad: ";
        cin >> cantidad;
        
        if (cantidad <= 0) {
            cout << "\n❌ Cantidad inválida" << endl;
        } else {
            usuarioActual->getCarrito().agregarProducto(producto, cantidad);
        }
        
        limpiarBuffer();
        pausar();
    }
    
    void menuModificarCarrito() {
        usuarioActual->getCarrito().mostrar();
        
        if (usuarioActual->getCarrito().estaVacio()) {
            pausar();
            return;
        }
        
        cout << "\n¿Qué deseas hacer?" << endl;
        cout << "1. Modificar cantidad de un producto" << endl;
        cout << "2. Eliminar un producto" << endl;
        cout << "0. Volver" << endl;
        cout << "Opción: ";
        
        int opcion;
        cin >> opcion;
        
        if (opcion == 0) return;
        
        int indice;
        cout << "Ingresa el número del producto [0-n]: ";
        cin >> indice;
        
        if (opcion == 1) {
            int cantidad;
            cout << "Nueva cantidad: ";
            cin >> cantidad;
            usuarioActual->getCarrito().modificarCantidad(indice, cantidad);
        } else if (opcion == 2) {
            usuarioActual->getCarrito().eliminarProducto(indice);
        }
        
        limpiarBuffer();
        pausar();
    }
    
    void menuPrincipal() {
        string nombre;
        cout << "\n🏪 BIENVENIDO AL SUPERMERCADO VIRTUAL 🏪" << endl;
        cout << "\nPor favor, ingresa tu nombre: ";
        getline(cin, nombre);
        
        usuarioActual = new Usuario(nombre);
        
        int opcion;
        do {
            cout << "\n" << string(50, '=') << endl;
            cout << "👤 Usuario: " << usuarioActual->getNombre() << endl;
            cout << string(50, '=') << endl;
            cout << "1. Ver todos los productos" << endl;
            cout << "2. Agregar producto al carrito" << endl;
            cout << "3. Ver mi carrito" << endl;
            cout << "4. Modificar carrito" << endl;
            cout << "5. Finalizar compra" << endl;
            cout << "6. Ver historial de compras" << endl;
            cout << "0. Salir" << endl;
            cout << string(50, '=') << endl;
            cout << "Opción: ";
            cin >> opcion;
            limpiarBuffer();
            
            switch(opcion) {
                case 1:
                    mostrarProductos();
                    pausar();
                    break;
                case 2:
                    menuAgregarProducto();
                    break;
                case 3:
                    usuarioActual->getCarrito().mostrar();
                    pausar();
                    break;
                case 4:
                    menuModificarCarrito();
                    break;
                case 5:
                    usuarioActual->getCarrito().mostrar();
                    if (!usuarioActual->getCarrito().estaVacio()) {
                        cout << "\n¿Confirmas la compra? (S/N): ";
                        char confirm;
                        cin >> confirm;
                        if (confirm == 'S' || confirm == 's') {
                            usuarioActual->finalizarCompra();
                        }
                    }
                    limpiarBuffer();
                    pausar();
                    break;
                case 6:
                    usuarioActual->mostrarHistorial();
                    pausar();
                    break;
                case 0:
                    cout << "\n👋 ¡Gracias por visitar nuestro supermercado!" << endl;
                    break;
                default:
                    cout << "\n❌ Opción inválida" << endl;
                    pausar();
            }
        } while(opcion != 0);
        
        delete usuarioActual;
    }
};

// ==================== FUNCIÓN PRINCIPAL ====================
int main() {
    Supermercado super;
    super.menuPrincipal();
    return 0;
}