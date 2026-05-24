#include <iostream>
#include <cmath>
#include "Geom.h"

const double PI_VAL = 3.141592653589793;

Point::Point(double x_coord, double y_coord) : x(x_coord), y(y_coord) {}

double dist(Point a, Point b) {
    return std::hypot(a.x - b.x, a.y - b.y);
}

Circle::Circle(Point center, double radius) : c(center), r(radius) {}

double Circle::calc_area() {
    return PI_VAL * r * r;
}

double Circle::calc_perimetr() {
    return 2.0 * PI_VAL * r;
}

void Circle::name() {
    std::cout << "Circle\n";
}

Ellipse::Ellipse(Point center, double radiusA, double radiusB) : c(center), a(radiusA), b(radiusB) {}

double Ellipse::calc_area() {
    return PI_VAL * a * b;
}

double Ellipse::calc_perimetr() {
    return 2.0 * PI_VAL * std::sqrt((a * a + b * b) / 2.0);
}

void Ellipse::name() {
    std::cout << "Ellipse\n";
}

Triangle::Triangle(double sideA, double sideB, double sideC) : a(sideA), b(sideB), c(sideC) {}

Triangle::Triangle(Point p1, Point p2, Point p3) {
    a = dist(p1, p2);
    b = dist(p2, p3);
    c = dist(p3, p1);
}

double Triangle::calc_area() {
    double semiP = calc_perimetr() / 2.0;
    return std::sqrt(semiP * (semiP - a) * (semiP - b) * (semiP - c));
}

double Triangle::calc_perimetr() {
    return a + b + c;
}

void Triangle::name() {
    std::cout << "Triangle\n";
}

Rectangle::Rectangle(double width, double height) : w(width), h(height) {}

Rectangle::Rectangle(Point p1, Point p2, Point p3, Point p4) {
    w = dist(p1, p2);
    h = dist(p2, p3);
}

double Rectangle::calc_area() {
    return w * h;
}

double Rectangle::calc_perimetr() {
    return 2.0 * (w + h);
}

void Rectangle::name() {
    std::cout << "Rectangle\n";
}

Polygon::Polygon(const std::vector<Point>& pts) : vertices(pts) {}

Polygon::Polygon(const std::string& filename) {
    std::ifstream file(filename);
    double x_coord, y_coord;
    while (file >> x_coord >> y_coord) {
        vertices.push_back(Point(x_coord, y_coord));
    }
}

double Polygon::calc_area() {
    double area = 0.0;
    size_t n = vertices.size();
    if (n < 3) return 0.0;
    
    for (size_t i = 0; i < n; ++i) {
        size_t j = (i + 1) % n;
        area += (vertices[i].x * vertices[j].y) - (vertices[j].x * vertices[i].y);
    }
    return std::abs(area) / 2.0;
}

double Polygon::calc_perimetr() {
    double p = 0.0;
    size_t n = vertices.size();
    if (n < 2) return 0.0;
    
    for (size_t i = 0; i < n; ++i) {
        size_t j = (i + 1) % n;
        p += dist(vertices[i], vertices[j]);
    }
    return p;
}

void Polygon::name() {
    std::cout << "Polygon\n";
}