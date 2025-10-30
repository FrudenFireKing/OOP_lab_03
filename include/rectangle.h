#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figure.h"

class Rectangle : public Figure {
private:
    double x1, y1, x2, y2, x3, y3, x4, y4;
    double center_x, center_y;
    double width, height;
    bool valid;

public:
    Rectangle(double x1 = 0, double y1 = 0, double x2 = 1, double y2 = 0, 
              double x3 = 1, double y3 = 1, double x4 = 0, double y4 = 1);
    
    double area() const override;
    std::pair<double, double> getCenter() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    std::unique_ptr<Figure> clone() const override;
    bool operator==(const Figure& other) const override;
    bool isValid() const override;

    double getWidth() const { return width; }
    double getHeight() const { return height; }
    bool isValidFigure() const { return valid; }

private:
    void calculateParameters();
    bool validateRectangle() const;
};

#endif