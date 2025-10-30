#ifndef ROMB_H
#define ROMB_H

#include "figure.h"

class Romb : public Figure {
private:
    double x1, y1, x2, y2, x3, y3, x4, y4;
    double center_x, center_y;
    double diagonal1, diagonal2;
    bool valid;

public:
    Romb(double x1 = 0, double y1 = 2, double x2 = 2, double y2 = 0, 
         double x3 = 0, double y3 = -2, double x4 = -2, double y4 = 0);
    
    double area() const override;
    std::pair<double, double> getCenter() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    std::unique_ptr<Figure> clone() const override;
    bool operator==(const Figure& other) const override;
    bool isValid() const override;

    double getDiagonal1() const { return diagonal1; }
    double getDiagonal2() const { return diagonal2; }
    bool isValidFigure() const { return valid; }

private:
    void calculateParameters();
    bool validateRomb() const;
};

#endif