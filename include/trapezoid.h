#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "figure.h"

class Trapezoid : public Figure {
private:
    double x1, y1, x2, y2, x3, y3, x4, y4;
    double center_x, center_y;
    double base1, base2, height;
    bool valid;

public:
    Trapezoid(double x1 = 0, double y1 = 0, double x2 = 2, double y2 = 0, 
              double x3 = 3, double y3 = 2, double x4 = 1, double y4 = 2);
    
    double area() const override;
    std::pair<double, double> getCenter() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    std::unique_ptr<Figure> clone() const override;
    bool operator==(const Figure& other) const override;
    bool isValid() const override;

    double getBase1() const { return base1; }
    double getBase2() const { return base2; }
    double getHeight() const { return height; }
    bool isValidFigure() const { return valid; }

private:
    void calculateParameters();
    bool validateTrapezoid() const;
};

#endif