#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

int main() {
    int rows;
    if (!(std::cin >> rows)) {
        return 1;
    }

    if (rows <= 0) {
        return 0;
    }

    std::vector<long long> current(1, 1);

    for (int i = 0; i < rows; ++i) {
        std::cout << std::string((rows - i - 1) * 2, ' ');
        for (std::size_t j = 0; j < current.size(); ++j) {
            std::cout << std::setw(4) << current[j];
        }
        std::cout << '\n';

        std::vector<long long> next(i + 2, 1);
        for (std::size_t j = 1; j < current.size(); ++j) {
            next[j] = current[j - 1] + current[j];
        }
        current.swap(next);
    }

    return 0;
}
