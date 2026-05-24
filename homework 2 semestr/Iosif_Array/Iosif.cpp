#include <iostream>
#include <ctime>
#include "Array.h"

int main() {
    int totalElements, step;
    
    std::cout << "Кол-во элементов (N): ";
    std::cin >> totalElements;
    std::cout << "Шаг выбывания (k): ";
    std::cin >> step;

    std::clock_t runTimer = std::clock();

    Array josephusContainer(totalElements);
    for (int i = 1; i <= totalElements; ++i) {
        josephusContainer.insert(i);
    }

    int eliminationIndex = 0;
    while (josephusContainer.getSize() > 1) {
        eliminationIndex = (eliminationIndex + step - 1) % josephusContainer.getSize();
        josephusContainer.remove(eliminationIndex);
    }

    std::clock_t stopTimer = std::clock();
    double calculationTime = double(stopTimer - runTimer) / CLOCKS_PER_SEC;

    std::cout << "Ответ: " << josephusContainer[0] << std::endl;
    std::cout << "Время расчета (сек): " << calculationTime << std::endl;

    return 0;
}