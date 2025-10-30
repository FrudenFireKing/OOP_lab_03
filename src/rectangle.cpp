#include "../include/rectangle.h"
#include <iostream>
#include <cmath>

Rectangle::Rectangle(double x1, double y1, double x2, double y2, 
                     double x3, double y3, double x4, double y4) 
    : x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3), x4(x4), y4(y4), valid(false) {
    calculateParameters();
}

void Rectangle::calculateParameters() {
    center_x = (x1 + x2 + x3 + x4) / 4.0;
    center_y = (y1 + y2 + y3 + y4) / 4.0;
    
    width = calculateDistance(x1, y1, x2, y2);
    height = calculateDistance(x2, y2, x3, y3);
    
    valid = validateRectangle();
}

bool Rectangle::validateRectangle() const {
    // 1. Проверяем, что все стороны существуют (ненулевые)
    double side1 = calculateDistance(x1, y1, x2, y2);
    double side2 = calculateDistance(x2, y2, x3, y3);
    double side3 = calculateDistance(x3, y3, x4, y4);
    double side4 = calculateDistance(x4, y4, x1, y1);
    
    if (side1 < 1e-10 || side2 < 1e-10 || side3 < 1e-10 || side4 < 1e-10) {
        return false;
    }
    
    // 2. Проверяем, что противоположные стороны равны
    if (std::abs(side1 - side3) > 1e-10 || std::abs(side2 - side4) > 1e-10) {
        return false;
    }
    
    // 3. Проверяем, что все углы прямые (90 градусов)
    // Угол между сторонами AB и BC
    if (!arePerpendicular(x1, y1, x2, y2, x2, y2, x3, y3)) {
        return false;
    }
    
    // Угол между сторонами BC и CD
    if (!arePerpendicular(x2, y2, x3, y3, x3, y3, x4, y4)) {
        return false;
    }
    
    // Угол между сторонами CD и DA
    if (!arePerpendicular(x3, y3, x4, y4, x4, y4, x1, y1)) {
        return false;
    }
    
    // 4. Проверяем, что диагонали равны
    double diag1 = calculateDistance(x1, y1, x3, y3);
    double diag2 = calculateDistance(x2, y2, x4, y4);
    
    if (std::abs(diag1 - diag2) > 1e-10) {
        return false;
    }
    
    return true;
}

bool Rectangle::isValid() const {
    return valid;
}

double Rectangle::area() const {
    if (!valid) return 0.0;
    return width * height;
}

std::pair<double, double> Rectangle::getCenter() const {
    return {center_x, center_y};
}

void Rectangle::print(std::ostream& os) const {
    os << "Rectangle vertices: ";
    os << "(" << x1 << ", " << y1 << "), ";
    os << "(" << x2 << ", " << y2 << "), ";
    os << "(" << x3 << ", " << y3 << "), ";
    os << "(" << x4 << ", " << y4 << ")";
    if (!valid) {
        os << " [INVALID RECTANGLE]";
    }
}

void Rectangle::read(std::istream& is) {
    std::cout << "Enter rectangle vertices (x1 y1 x2 y2 x3 y3 x4 y4): ";
    is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    calculateParameters();
    
    if (!valid) {
        std::cout << "Warning: The entered coordinates do not form a valid rectangle!\n";
    }
}

std::unique_ptr<Figure> Rectangle::clone() const {
    return std::make_unique<Rectangle>(*this);
}

bool Rectangle::operator==(const Figure& other) const {
    if (const Rectangle* rect = dynamic_cast<const Rectangle*>(&other)) {
        return x1 == rect->x1 && y1 == rect->y1 &&
               x2 == rect->x2 && y2 == rect->y2 &&
               x3 == rect->x3 && y3 == rect->y3 &&
               x4 == rect->x4 && y4 == rect->y4;
    }
    return false;
}