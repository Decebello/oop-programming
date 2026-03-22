#include <iostream>
#include <vector>

int josephus(int n, int k) {
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        res = (res + k) % i;
    }
    return res + 1;
}

int main() {
	setlocale(LC_ALL, "Russian");
    std::vector<int> n_values = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };
    int k = 3;

    std::cout << "N\t\tОтвет" << std::endl;
    std::cout << "--------------------" << std::endl;

    for (int n : n_values) {
        int result = josephus(n, k);
        std::cout << n << "\t\t" << result << std::endl;
    }

    return 0;
}