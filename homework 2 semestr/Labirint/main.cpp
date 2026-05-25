#include "Labirint.h"
#include <iostream>

int main() {
    string inputFile  = "ДНК_Лабиринт.bmp";
    string outputFile = "output.bmp";

    Labirint lab;

    if (!lab.loadBMP(inputFile)) {
        cerr << "Ошибка загрузки лабиринта" << endl;
        return 1;
    }

    if (lab.solve()) {
        lab.saveBMP(outputFile);
        cout << "Путь найден. Результат сохранён в " << outputFile << endl;
    } else {
        cout << "Путь не найден." << endl;
    }

    return 0;
}
