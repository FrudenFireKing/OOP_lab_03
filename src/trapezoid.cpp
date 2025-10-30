#include "../include/Trapezoid.h"
#include <iostream>
#include <cmath>

Trapezoid::Trapezoid(double x1, double y1, double x2, double y2, 
                     double x3, double y3, double x4, double y4) 
    : x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3), x4(x4), y4(y4), valid(false) {
    calculateParameters();
}

void Trapezoid::calculateParameters() {
    center_x = (x1 + x2 + x3 + x4) / 4.0;
    center_y = (y1 + y2 + y3 + y4) / 4.0;
    
    base1 = calculateDistance(x1, y1, x2, y2);
    base2 = calculateDistance(x3, y3, x4, y4);
    
    height = (std::abs(y3 - y1) + std::abs(y4 - y2)) / 2.0;
    
    valid = validateTrapezoid();
}

bool Trapezoid::validateTrapezoid() const {
    // 1. Проверяем, что все стороны существуют
    double side1 = calculateDistance(x1, y1, x2, y2); // основание 1
    double side2 = calculateDistance(x2, y2, x3, y3); // боковая 1
    double side3 = calculateDistance(x3, y3, x4, y4); // основание 2
    double side4 = calculateDistance(x4, y4, x1, y1); // боковая 2
    
    if (side1 < 1e-10 || side2 < 1e-10 || side3 < 1e-10 || side4 < 1e-10) {
        return false;
    }
    
    // 2. Проверяем, что хотя бы одна пара сторон параллельна (основания)
    bool basesParallel = areParallel(x1, y1, x2, y2, x3, y3, x4, y4) || 
                        areParallel(x1, y1, x2, y2, x4, y4, x3, y3);
    
    if (!basesParallel) {
        // Проверяем другую возможную пару оснований
        basesParallel = areParallel(x2, y2, x3, y3, x4, y4, x1, y1) || 
                       areParallel(x2, y2, x3, y3, x1, y1, x4, y4);
    }
    
    if (!basesParallel) {
        return false;
    }
    
    // 3. Проверяем, что фигура выпуклая
    // Вычисляем векторные произведения для проверки выпуклости
    double cross1 = (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);
    double cross2 = (x3 - x2) * (y4 - y3) - (y3 - y2) * (x4 - x3);
    double cross3 = (x4 - x3) * (y1 - y4) - (y4 - y3) * (x1 - x4);
    double cross4 = (x1 - x4) * (y2 - y1) - (y1 - y4) * (x2 - x1);
    
    // Все векторные произведения должны иметь одинаковый знак для выпуклости
    if (!((cross1 >= 0 && cross2 >= 0 && cross3 >= 0 && cross4 >= 0) ||
          (cross1 <= 0 && cross2 <= 0 && cross3 <= 0 && cross4 <= 0))) {
        return false;
    }
    
    return true;
}

bool Trapezoid::isValid() const {
    return valid;
}

double Trapezoid::area() const {
    if (!valid) return 0.0;
    return (base1 + base2) * height / 2.0;
}

std::pair<double, double> Trapezoid::getCenter() const {
    return {center_x, center_y};
}

void Trapezoid::print(std::ostream& os) const {
    os << "Trapezoid vertices: ";
    os << "(" << x1 << ", " << y1 << "), ";
    os << "(" << x2 << ", " << y2 << "), ";
    os << "(" << x3 << ", " << y3 << "), ";
    os << "(" << x4 << ", " << y4 << ")";
    if (!valid) {
        os << " [INVALID TRAPEZOID]";
    }
}

void Trapezoid::read(std::istream& is) {
    std::cout << "Enter trapezoid vertices (x1 y1 x2 y2 x3 y3 x4 y4): ";
    std::cout << "Enter vertices in order: bottom-left, bottom-right, top-right, top-left\n";
    is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    calculateParameters();
    
    if (!valid) {
        std::cout << "Warning: The entered coordinates do not form a valid trapezoid!\n";
    }
}

std::unique_ptr<Figure> Trapezoid::clone() const {
    return std::make_unique<Trapezoid>(*this);
}

bool Trapezoid::operator==(const Figure& other) const {
    if (const Trapezoid* trap = dynamic_cast<const Trapezoid*>(&other)) {
        return x1 == trap->x1 && y1 == trap->y1 &&
               x2 == trap->x2 && y2 == trap->y2 &&
               x3 == trap->x3 && y3 == trap->y3 &&
               x4 == trap->x4 && y4 == trap->y4;
    }
    return false;
}