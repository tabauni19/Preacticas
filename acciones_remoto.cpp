#include <iostream>
#include <vector>
#include <limits>

int maxProfit(const std::vector<int>& prices) {
    int minPrice = std::numeric_limits<int>::max();
    int best = 0;

    for (int price : prices) {
        if (price < minPrice) {
            minPrice = price;
        } else {
            int candidate = price - minPrice;
            if (candidate > best) {
                best = candidate;
            }
        }
    }

    return best;
}

int main() {
    int n;
    if (!(std::cin >> n)) {
        return 1;
    }

    if (n <= 0) {
        std::cout << 0 << '\n';
        return 0;
    }

    std::vector<int> prices(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> prices[i];
    }

    std::cout << maxProfit(prices) << '\n';
    return 0;
}
