#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct StepDetail {
    char symbol = 'A';
    int digit = 1;
    long long previousTotal = 0;
    long long result = 0;
};

std::string trim(const std::string& value) {
    std::size_t begin = 0;
    std::size_t end = value.size();

    while (begin < end && std::isspace(static_cast<unsigned char>(value[begin]))) {
        ++begin;
    }
    while (end > begin && std::isspace(static_cast<unsigned char>(value[end - 1]))) {
        --end;
    }

    return value.substr(begin, end - begin);
}

bool normalizeTitle(const std::string& raw, std::string& normalized, std::string& error) {
    std::string trimmed = trim(raw);

    if (trimmed.empty()) {
        error = "El titulo no puede estar vacio.";
        return false;
    }

    if (trimmed.size() > 7) {
        error = "El titulo supera el limite de 7 caracteres permitido por Excel.";
        return false;
    }

    normalized.clear();
    normalized.reserve(trimmed.size());

    for (char c : trimmed) {
        if (!std::isalpha(static_cast<unsigned char>(c))) {
            error = "Solo se aceptan letras (A-Z).";
            return false;
        }
        normalized.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));
    }

    error.clear();
    return true;
}

std::vector<StepDetail> computeSteps(const std::string& title) {
    std::vector<StepDetail> steps;
    steps.reserve(title.size());

    long long total = 0;
    for (char c : title) {
        StepDetail detail;
        detail.symbol = c;
        detail.digit = (c - 'A') + 1;
        detail.previousTotal = total;
        detail.result = total * 26 + detail.digit;
        total = detail.result;
        steps.push_back(detail);
    }

    return steps;
}

bool readLine(const std::string& prompt, std::string& buffer) {
    std::cout << prompt << std::flush;
    return static_cast<bool>(std::getline(std::cin, buffer));
}

bool askToContinue() {
    std::string line;
    while (true) {
        if (!readLine("Desea convertir otro titulo? (s/n): ", line)) {
            return false;
        }
        if (line.empty()) {
            continue;
        }
        char c = static_cast<char>(std::tolower(static_cast<unsigned char>(line[0])));
        if (c == 's') {
            return true;
        }
        if (c == 'n') {
            return false;
        }
        std::cout << "Respuesta invalida. Indique s (si) o n (no).\n";
    }
}

int main() {
    std::cout
        << "===============================================\n"
        << " Convertidor de titulos de columna de Excel\n"
        << "===============================================\n"
        << "Instrucciones:\n"
        << "  * Ingrese un titulo compuesto solo por letras (A-Z).\n"
        << "  * Se aceptan hasta 7 caracteres (limite de Excel).\n"
        << "  * Se ignoran espacios al inicio o final.\n\n";

    while (true) {
        std::string input;
        if (!readLine("Titulo de la columna: ", input)) {
            std::cout << "\nEntrada finalizada. Hasta pronto.\n";
            return 0;
        }

        std::string title;
        std::string error;
        if (!normalizeTitle(input, title, error)) {
            std::cout << "Error: " << error << "\n\n";
            continue;
        }

        std::vector<StepDetail> steps = computeSteps(title);
        long long finalValue = steps.empty() ? 0 : steps.back().result;

        std::cout << "\nTitulo normalizado: " << title << '\n';
        std::cout << "Numero de columna calculado: " << finalValue << "\n\n";

        std::cout << "Detalle del calculo:\n";
        for (std::size_t i = 0; i < steps.size(); ++i) {
            const StepDetail& step = steps[i];
            std::cout
                << "  Paso " << (i + 1) << ": ("
                << step.previousTotal << " * 26) + "
                << step.digit << " [" << step.symbol << "] = "
                << step.result << '\n';
        }
        std::cout << '\n';

        if (!askToContinue()) {
            break;
        }

        std::cout << '\n';
    }

    std::cout << "Gracias por utilizar el convertidor.\n";
    return 0;
}
