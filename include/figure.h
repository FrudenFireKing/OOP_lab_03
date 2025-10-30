#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

class Figure {
public:
    virtual ~Figure() = default;

    // Виртуальные методы
    virtual double area() const = 0;
    virtual std::pair<double, double> getCenter() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    
    // Виртуальное клонирование
    virtual std::unique_ptr<Figure> clone() const = 0;
    
    // Операторы
    virtual bool operator==(const Figure& other) const = 0;
    virtual operator double() const;

    // Валидация
    virtual bool isValid() const = 0;

protected:
    // Вспомогательные методы для вычислений
    double calculateDistance(double x1, double y1, double x2, double y2) const;
    double calculateTriangleArea(double x1, double y1, double x2, double y2, double x3, double y3) const;
    bool areParallel(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) const;
    bool arePerpendicular(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) const;
    double dotProduct(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) const;
};

std::ostream& operator<<(std::ostream& os, const Figure& fig);
std::istream& operator>>(std::istream& is, Figure& fig);

#endif