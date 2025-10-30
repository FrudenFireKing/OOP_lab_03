#include <gtest/gtest.h>
#include "figure.h"
#include "rectangle.h"
#include "trapezoid.h"
#include "romb.h"

// ����� ��� Rectangle � ������������ ������
TEST(RectangleTest, AreaCalculation) {
    // �������������: (0,0), (4,0), (4,5), (0,5)
    Rectangle rect(0, 0, 4, 0, 4, 5, 0, 5);
    EXPECT_DOUBLE_EQ(rect.area(), 20.0); // 4 * 5 = 20
}

TEST(RectangleTest, Center) {
    // �������������: (0,0), (4,0), (4,6), (0,6)
    Rectangle rect(0, 0, 4, 0, 4, 6, 0, 6);
    auto center = rect.getCenter();
    EXPECT_DOUBLE_EQ(center.first, 2.0);  // (0+4+4+0)/4 = 2
    EXPECT_DOUBLE_EQ(center.second, 3.0); // (0+0+6+6)/4 = 3
}

TEST(RectangleTest, DoubleConversion) {
    // �������������: (0,0), (3,0), (3,4), (0,4)
    Rectangle rect(0, 0, 3, 0, 3, 4, 0, 4);
    double area = static_cast<double>(rect);
    EXPECT_DOUBLE_EQ(area, 12.0); // 3 * 4 = 12
}

// ����� ��� Trapezoid � ������������ ������
TEST(TrapezoidTest, AreaCalculation) {
    // ��������: (0,0), (4,0), (3,5), (1,5)
    Trapezoid trap(0, 0, 4, 0, 3, 5, 1, 5);
    // ������� = (4 + 2) * 5 / 2 = 15
    EXPECT_DOUBLE_EQ(trap.area(), 15.0);
}

TEST(TrapezoidTest, Center) {
    // ��������: (1,1), (4,1), (3,3), (2,3)
    Trapezoid trap(1, 1, 4, 1, 3, 3, 2, 3);
    auto center = trap.getCenter();
    // �����: (1+4+3+2)/4 = 2.5, (1+1+3+3)/4 = 2
    EXPECT_DOUBLE_EQ(center.first, 2.5);
    EXPECT_DOUBLE_EQ(center.second, 2.0);
}

// ����� ��� Romb � ������������ ������
TEST(RombTest, AreaCalculation) {
    // ����: (0,3), (4,0), (0,-3), (-4,0)
    Romb romb(0, 3, 4, 0, 0, -3, -4, 0);
    // ���������: 6 � 8, ������� = 6*8/2 = 24
    EXPECT_DOUBLE_EQ(romb.area(), 24.0);
}

TEST(RombTest, Center) {
    // ����: (1,4), (5,2), (3,0), (-1,2)
    Romb romb(1, 4, 5, 2, 3, 0, -1, 2);
    auto center = romb.getCenter();
    // �����: (1+5+3-1)/4 = 2, (4+2+0+2)/4 = 2
    EXPECT_DOUBLE_EQ(center.first, 2.0);
    EXPECT_DOUBLE_EQ(center.second, 2.0);
}

// ����� ���������� ���������
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

// ���� ��� �����
TEST(OperatorTest, RombEquality) {
    Romb romb1(0, 3, 4, 0, 0, -3, -4, 0);
    Romb romb2(0, 3, 4, 0, 0, -3, -4, 0);
    Romb romb3(1, 3, 5, 0, 1, -3, -3, 0);
    
    EXPECT_TRUE(romb1 == romb2);
    EXPECT_FALSE(romb1 == romb3);
}

// ����� ���������
TEST(ValidationTest, ValidRectangle) {
    Rectangle rect(0, 0, 4, 0, 4, 3, 0, 3); // ���������� �������������
    EXPECT_TRUE(rect.isValid());
}

TEST(ValidationTest, InvalidRectangle) {
    Rectangle rect(0, 0, 4, 0, 3, 3, 0, 3); // �� �������������
    EXPECT_FALSE(rect.isValid());
}

TEST(ValidationTest, ValidTrapezoid) {
    Trapezoid trap(0, 0, 4, 0, 3, 3, 1, 3); // ���������� ��������
    EXPECT_TRUE(trap.isValid());
}

TEST(ValidationTest, ValidRomb) {
    Romb romb(0, 2, 2, 0, 0, -2, -2, 0); // ���������� ����
    EXPECT_TRUE(romb.isValid());
}

TEST(ValidationTest, InvalidFigureArea) {
    Rectangle invalidRect(0, 0, 1, 0, 2, 1, 0, 1); // �� �������������
    EXPECT_DOUBLE_EQ(invalidRect.area(), 0.0); // ������� ������ ���� 0 ��� ���������� ������
}

// ������� ������� ��� ������� ������
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}