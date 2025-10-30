#include "../include/romb.h"
#include <iostream>
#include <cmath>

Romb::Romb(double x1, double y1, double x2, double y2, 
           double x3, double y3, double x4, double y4) 
    : x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3), x4(x4), y4(y4), valid(false) {
    calculateParameters();
}

void Romb::calculateParameters() {
    center_x = (x1 + x2 + x3 + x4) / 4.0;
    center_y = (y1 + y2 + y3 + y4) / 4.0;
    
    diagonal1 = calculateDistance(x1, y1, x3, y3);
    diagonal2 = calculateDistance(x2, y2, x4, y4);
    
    valid = validateRomb();
}

bool Romb::validateRomb() const {
    // 1. Проверяем, что все стороны равны
    double side1 = calculateDistance(x1, y1, x2, y2);
    double side2 = calculateDistance(x2, y2, x3, y3);
    double side3 = calculateDistance(x3, y3, x4, y4);
    double side4 = calculateDistance(x4, y4, x1, y1);
    
    if (side1 < 1e-10) return false;
    
    if (std::abs(side1 - side2) > 1e-10 || 
        std::abs(side2 - side3) > 1e-10 || 
        std::abs(side3 - side4) > 1e-10) {
        return false;
    }
    
    // 2. Проверяем, что диагонали перпендикулярны
    if (!arePerpendicular(x1, y1, x3, y3, x2, y2, x4, y4)) {
        return false;
    }
    
    // 3. Проверяем, что диагонали делятся пополам
    double mid_diag1_x = (x1 + x3) / 2.0;
    double mid_diag1_y = (y1 + y3) / 2.0;
    double mid_diag2_x = (x2 + x4) / 2.0;
    double mid_diag2_y = (y2 + y4) / 2.0;
    
    if (std::abs(mid_diag1_x - mid_diag2_x) > 1e-10 || 
        std::abs(mid_diag1_y - mid_diag2_y) > 1e-10) {
        return false;
    }
    
    // 4. Проверяем выпуклость
    double cross1 = (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);
    double cross2 = (x3 - x2) * (y4 - y3) - (y3 - y2) * (x4 - x3);
    double cross3 = (x4 - x3) * (y1 - y4) - (y4 - y3) * (x1 - x4);
    double cross4 = (x1 - x4) * (y2 - y1) - (y1 - y4) * (x2 - x1);
    
    if (!((cross1 >= 0 && cross2 >= 0 && cross3 >= 0 && cross4 >= 0) ||
          (cross1 <= 0 && cross2 <= 0 && cross3 <= 0 && cross4 <= 0))) {
        return false;
    }
    
    return true;
}

bool Romb::isValid() const {
    return valid;
}

double Romb::area() const {
    if (!valid) return 0.0;
    return (diagonal1 * diagonal2) / 2.0;
}

std::pair<double, double> Romb::getCenter() const {
    return {center_x, center_y};
}

void Romb::print(std::ostream& os) const {
    os << "Romb vertices: ";
    os << "(" << x1 << ", " << y1 << "), ";
    os << "(" << x2 << ", " << y2 << "), ";
    os << "(" << x3 << ", " << y3 << "), ";
    os << "(" << x4 << ", " << y4 << ")";
    if (!valid) {
        os << " [INVALID ROMB]";
    }
}

void Romb::read(std::istream& is) {
    std::cout << "Enter romb vertices (x1 y1 x2 y2 x3 y3 x4 y4): ";
    std::cout << "Enter vertices in order: top, right, bottom, left\n";
    is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    calculateParameters();
    
    if (!valid) {
        std::cout << "Warning: The entered coordinates do not form a valid romb!\n";
    }
}

std::unique_ptr<Figure> Romb::clone() const {
    return std::make_unique<Romb>(*this);
}

bool Romb::operator==(const Figure& other) const {
    if (const Romb* rhomb = dynamic_cast<const Romb*>(&other)) {
        return x1 == rhomb->x1 && y1 == rhomb->y1 &&
               x2 == rhomb->x2 && y2 == rhomb->y2 &&
               x3 == rhomb->x3 && y3 == rhomb->y3 &&
               x4 == rhomb->x4 && y4 == rhomb->y4;
    }
    return false;
}