#include <gtest/gtest.h>
#include "figure.h"
#include "rectangle.h"
#include "trapezoid.h"
#include "romb.h"

// Тесты для Rectangle с координатами вершин
TEST(RectangleTest, AreaCalculation) {
    // Прямоугольник: (0,0), (4,0), (4,5), (0,5)
    Rectangle rect(0, 0, 4, 0, 4, 5, 0, 5);
    EXPECT_DOUBLE_EQ(rect.area(), 20.0); // 4 * 5 = 20
}

TEST(RectangleTest, Center) {
    // Прямоугольник: (0,0), (4,0), (4,6), (0,6)
    Rectangle rect(0, 0, 4, 0, 4, 6, 0, 6);
    auto center = rect.getCenter();
    EXPECT_DOUBLE_EQ(center.first, 2.0);  // (0+4+4+0)/4 = 2
    EXPECT_DOUBLE_EQ(center.second, 3.0); // (0+0+6+6)/4 = 3
}

TEST(RectangleTest, DoubleConversion) {
    // Прямоугольник: (0,0), (3,0), (3,4), (0,4)
    Rectangle rect(0, 0, 3, 0, 3, 4, 0, 4);
    double area = static_cast<double>(rect);
    EXPECT_DOUBLE_EQ(area, 12.0); // 3 * 4 = 12
}

// Тесты для Trapezoid с координатами вершин
TEST(TrapezoidTest, AreaCalculation) {
    // Трапеция: (0,0), (4,0), (3,5), (1,5)
    Trapezoid trap(0, 0, 4, 0, 3, 5, 1, 5);
    // Площадь = (4 + 2) * 5 / 2 = 15
    EXPECT_DOUBLE_EQ(trap.area(), 15.0);
}

TEST(TrapezoidTest, Center) {
    // Трапеция: (1,1), (4,1), (3,3), (2,3)
    Trapezoid trap(1, 1, 4, 1, 3, 3, 2, 3);
    auto center = trap.getCenter();
    // Центр: (1+4+3+2)/4 = 2.5, (1+1+3+3)/4 = 2
    EXPECT_DOUBLE_EQ(center.first, 2.5);
    EXPECT_DOUBLE_EQ(center.second, 2.0);
}

// Тесты для Romb с координатами вершин
TEST(RombTest, AreaCalculation) {
    // Ромб: (0,3), (4,0), (0,-3), (-4,0)
    Romb romb(0, 3, 4, 0, 0, -3, -4, 0);
    // Диагонали: 6 и 8, площадь = 6*8/2 = 24
    EXPECT_DOUBLE_EQ(romb.area(), 24.0);
}

TEST(RombTest, Center) {
    // Ромб: (1,4), (5,2), (3,0), (-1,2)
    Romb romb(1, 4, 5, 2, 3, 0, -1, 2);
    auto center = romb.getCenter();
    // Центр: (1+5+3-1)/4 = 2, (4+2+0+2)/4 = 2
    EXPECT_DOUBLE_EQ(center.first, 2.0);
    EXPECT_DOUBLE_EQ(center.second, 2.0);
}

// Тесты операторов сравнения
TEST(OperatorTest, RectangleEquality) {
    Rectangle rect1(0, 0, 4, 0, 4, 5, 0, 5);
    Rectangle rect2(0, 0, 4, 0, 4, 5, 0, 5);
    Rectangle rect3(1, 1, 5, 1, 5, 6, 1, 6);
    
    EXPECT_TRUE(rect1 == rect2);
    EXPECT_FALSE(rect1 == rect3);
}

TEST(OperatorTest, TrapezoidEquality) {
    Trapezoid trap1(0, 0, 4, 0, 3, 5, 1, 5);
    Trapezoid trap2(0, 0, 4, 0, 3, 5, 1, 5);
    Trapezoid trap3(0, 0, 3, 0, 2, 5, 1, 5);
    
    EXPECT_TRUE(trap1 == trap2);
    EXPECT_FALSE(trap1 == trap3);
}

// Тест для ромба
TEST(OperatorTest, RombEquality) {
    Romb romb1(0, 3, 4, 0, 0, -3, -4, 0);
    Romb romb2(0, 3, 4, 0, 0, -3, -4, 0);
    Romb romb3(1, 3, 5, 0, 1, -3, -3, 0);
    
    EXPECT_TRUE(romb1 == romb2);
    EXPECT_FALSE(romb1 == romb3);
}

// Тесты валидации
TEST(ValidationTest, ValidRectangle) {
    Rectangle rect(0, 0, 4, 0, 4, 3, 0, 3); // Правильный прямоугольник
    EXPECT_TRUE(rect.isValid());
}

TEST(ValidationTest, InvalidRectangle) {
    Rectangle rect(0, 0, 4, 0, 3, 3, 0, 3); // Не прямоугольник
    EXPECT_FALSE(rect.isValid());
}

TEST(ValidationTest, ValidTrapezoid) {
    Trapezoid trap(0, 0, 4, 0, 3, 3, 1, 3); // Правильная трапеция
    EXPECT_TRUE(trap.isValid());
}

TEST(ValidationTest, ValidRomb) {
    Romb romb(0, 2, 2, 0, 0, -2, -2, 0); // Правильный ромб
    EXPECT_TRUE(romb.isValid());
}

TEST(ValidationTest, InvalidFigureArea) {
    Rectangle invalidRect(0, 0, 1, 0, 2, 1, 0, 1); // Не прямоугольник
    EXPECT_DOUBLE_EQ(invalidRect.area(), 0.0); // Площадь должна быть 0 для невалидной фигуры
}

// Главная функция для запуска тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}