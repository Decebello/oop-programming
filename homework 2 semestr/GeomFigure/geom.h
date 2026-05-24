#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream> 

class Point {
public:
    double x, y;
    Point(double x = 0, double y = 0);
};

double dist(Point a, Point b);

class Shape {
public:
    virtual double calc_area() = 0;
    virtual double calc_perimetr() = 0;
    virtual void name() = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    Point c;
    double r;
public:
    Circle(Point c, double r);
    double calc_area() override;
    double calc_perimetr() override;
    void name() override;
};

class Ellipse : public Shape {
private:
    Point c;
    double a, b;
public:
    Ellipse(Point c, double a, double b);
    double calc_area() override;
    double calc_perimetr() override;
    void name() override;
};

class Triangle : public Shape {
private:
    double a, b, c;
public:
    Triangle(double a, double b, double c);
    Triangle(Point p1, Point p2, Point p3);
    double calc_area() override;
    double calc_perimetr() override;
    void name() override;
};

class Rectangle : public Shape {
private:
    double w, h;
public:
    Rectangle(double w, double h);
    Rectangle(Point p1, Point p2, Point p3, Point p4);
    double calc_area() override;
    double calc_perimetr() override;
    void name() override;
};

class Polygon : public Shape {
private:
    std::vector<Point> vertices;
public:
    Polygon(const std::vector<Point>& pts);
    Polygon(const std::string& filename);
    double calc_area() override;
    double calc_perimetr() override;
    void name() override;
};