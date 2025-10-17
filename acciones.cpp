#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct ProfitInfo {
    int profit = 0;
    int buyDay = -1;
    int sellDay = -1;
};

ProfitInfo maxProfitInfo(const std::vector<int>& prices) {
    ProfitInfo info;

    if (prices.size() < 2) {
        return info;
    }

    int minPrice = prices[0];
    int minIndex = 0;

    for (std::size_t i = 1; i < prices.size(); ++i) {
        int price = prices[i];
        int candidate = price - minPrice;

        if (candidate > info.profit) {
            info.profit = candidate;
            info.buyDay = minIndex;
            info.sellDay = static_cast<int>(i);
        }

        if (price < minPrice) {
            minPrice = price;
            minIndex = static_cast<int>(i);
        }
    }

    if (info.profit <= 0) {
        info.profit = 0;
        info.buyDay = -1;
        info.sellDay = -1;
    }

    return info;
}

bool parseStrictInt(const std::string& text, int& value) {
    std::stringstream ss(text);
    char extra = '\0';

    if (ss >> value) {
        if (ss >> extra) {
            return false;
        }
        return true;
    }

    return false;
}

bool readLine(const std::string& prompt, std::string& line) {
    std::cout << prompt << std::flush;
    return static_cast<bool>(std::getline(std::cin, line));
}

bool requestPositiveInt(const std::string& prompt, int& value) {
    std::string line;

    while (true) {
        if (!readLine(prompt, line)) {
            return false;
        }

        if (parseStrictInt(line, value) && value > 0) {
            return true;
        }

        std::cout << "Entrada invalida. Necesito un entero mayor que 0.\n";
    }
}

bool requestNonNegativeInt(const std::string& prompt, int& value) {
    std::string line;

    while (true) {
        if (!readLine(prompt, line)) {
            return false;
        }

        if (parseStrictInt(line, value) && value >= 0) {
            return true;
        }

        std::cout << "Entrada invalida. Necesito un entero mayor o igual a 0.\n";
    }
}

bool askToContinue() {
    std::string line;

    while (true) {
        if (!readLine("Desea realizar otro calculo? (s/n): ", line)) {
            return false;
        }

        if (line.empty()) {
            continue;
        }

        char answer = line[0];
        if (answer == 's' || answer == 'S') {
            return true;
        }
        if (answer == 'n' || answer == 'N') {
            return false;
        }

        std::cout << "Por favor responda con s (si) o n (no).\n";
    }
}

int main() {
    std::cout
        << "===============================================\n"
        << " Calculadora del mejor momento para comerciar\n"
        << "===============================================\n"
        << "Ingrese los precios diarios de la accion.\n"
        << "El programa analizara la mejor ganancia posible\n"
        << "manteniendo la compra antes que la venta.\n\n";

    while (true) {
        int days = 0;
        if (!requestPositiveInt("Cantidad de dias con precio: ", days)) {
            std::cout << "\nNo se recibieron mas datos. Fin del programa.\n";
            return 0;
        }

        std::vector<int> prices;
        prices.reserve(days);

        for (int i = 0; i < days; ++i) {
            int price = 0;
            std::string prompt = "Valor de la accion en el dia " + std::to_string(i + 1) + ": ";
            if (!requestNonNegativeInt(prompt, price)) {
                std::cout << "\nNo se recibieron mas datos. Fin del programa.\n";
                return 0;
            }
            prices.push_back(price);
        }

        ProfitInfo info = maxProfitInfo(prices);

        std::cout << "\nSerie de precios ingresada: ";
        for (std::size_t i = 0; i < prices.size(); ++i) {
            std::cout << prices[i];
            if (i + 1 < prices.size()) {
                std::cout << ' ';
            }
        }
        std::cout << "\n\n";

        std::cout
            << "Como se calcula:\n"
            << "- Recorremos la lista una sola vez.\n"
            << "- Guardamos el precio minimo visto hasta el momento.\n"
            << "- Comparamos la ganancia si vendieramos en el dia actual con la mejor previa.\n"
            << "- Actualizamos la respuesta solo si la ganancia mejora.\n\n";

        if (info.profit > 0) {
            std::cout
                << "Mejor estrategia encontrada:\n"
                << "  * Comprar en el dia " << (info.buyDay + 1)
                << " con precio " << prices[info.buyDay] << ".\n"
                << "  * Vender en el dia " << (info.sellDay + 1)
                << " con precio " << prices[info.sellDay] << ".\n"
                << "Ganancia maxima: " << info.profit << "\n\n";
        } else {
            std::cout
                << "En esta serie no existe una venta posterior que genere ganancia.\n"
                << "Ganancia maxima: 0\n\n";
        }

        if (!askToContinue()) {
            break;
        }

        std::cout << '\n';
    }

    std::cout << "Gracias por usar la calculadora. Hasta pronto.\n";
    return 0;
}
