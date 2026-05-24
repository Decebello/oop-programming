#include <iostream>
#include <cmath>
#include "Geom.h"

int main() {
    int countRectangle = 0;
    int countCircle = 0;
    int countTriangle = 0;
    int countNoise = 0;

    double totalRectArea = 0.0;
    double totalCircleArea = 0.0;
    double totalTriangleArea = 0.0;

    Polygon plot("granitsy-uchastka2.txt");
    double plotArea = plot.calc_area();

    std::ifstream inputFile("input.txt"); 
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
        }
        inputFile.close();
    }

    std::ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        outputFile << "Rectangle = " << countRectangle << "\n";
        outputFile << "Circle = " << countCircle << "\n";
        outputFile << "Triangle = " << countTriangle << "\n";
        outputFile << "Noise = " << countNoise << "\n";
        outputFile.close();
    }

    std::cout << "Общая площадь прямоугольников: " << totalRectArea << "\n";
    std::cout << "Общая площадь кругов: " << totalCircleArea << "\n";
    std::cout << "Общая площадь треугольников: " << totalTriangleArea << "\n";
    std::cout << "Площадь участка (granitsy-uchastka2.txt): " << plotArea << "\n";

    return 0;
}