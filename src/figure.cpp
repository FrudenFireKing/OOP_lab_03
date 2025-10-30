#include "../include/figure.h"
#include <cmath>
#include <algorithm>

Figure::operator double() const {
    return area();
}

std::ostream& operator<<(std::ostream& os, const Figure& fig) {
    fig.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Figure& fig) {
    fig.read(is);
    return is;
}

double Figure::calculateDistance(double x1, double y1, double x2, double y2) const {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double Figure::calculateTriangleArea(double x1, double y1, double x2, double y2, double x3, double y3) const {
    return std::abs((x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)) / 2.0);
}

bool Figure::areParallel(double x1, double y1, double x2, double y2, 
                        double x3, double y3, double x4, double y4) const {
    double dx1 = x2 - x1, dy1 = y2 - y1;
    double dx2 = x4 - x3, dy2 = y4 - y3;
    
    // Векторы параллельны если их координаты пропорциональны
    return std::abs(dx1 * dy2 - dx2 * dy1) < 1e-10;
}

bool Figure::arePerpendicular(double x1, double y1, double x2, double y2,
                             double x3, double y3, double x4, double y4) const {
    double dx1 = x2 - x1, dy1 = y2 - y1;
    double dx2 = x4 - x3, dy2 = y4 - y3;
    
    // Векторы перпендикулярны если их скалярное произведение равно 0
    return std::abs(dx1 * dx2 + dy1 * dy2) < 1e-10;
}

double Figure::dotProduct(double x1, double y1, double x2, double y2,
                         double x3, double y3, double x4, double y4) const {
    double dx1 = x2 - x1, dy1 = y2 - y1;
    double dx2 = x4 - x3, dy2 = y4 - y3;
    return dx1 * dx2 + dy1 * dy2;
}