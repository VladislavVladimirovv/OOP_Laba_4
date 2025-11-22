#include <gtest/gtest.h>
#include "../include/array.h"
#include "../include/rectangle.h"
#include "../include/rhombus.h"
#include "../include/trapezoid.h"
#include "../include/point.h"
#include <memory>
#include <cmath>

// Тесты для Point
TEST(PointTest, DefaultConstructor)
{
    Point<int> p;
    EXPECT_EQ(p.get_x(), 0);
    EXPECT_EQ(p.get_y(), 0);
}

TEST(PointTest, ParameterizedConstructor)
{
    Point<double> p(3.5, 4.2);
    EXPECT_DOUBLE_EQ(p.get_x(), 3.5);
    EXPECT_DOUBLE_EQ(p.get_y(), 4.2);
}

TEST(PointTest, EqualityOperator)
{
    Point<int> p1(1, 2);
    Point<int> p2(1, 2);
    Point<int> p3(3, 4);
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

// Тесты для Rectangle
TEST(RectangleTest, ConstructorAndArea)
{
    Rectangle<double> rect(Point<double>(0, 0), 4.0, 3.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(rect), 12.0);
}

TEST(RectangleTest, CenterCalculation)
{
    Rectangle<double> rect(Point<double>(1, 1), 4.0, 4.0);
    auto center = rect.center();
    EXPECT_DOUBLE_EQ(center.get_x(), 3.0);
    EXPECT_DOUBLE_EQ(center.get_y(), 3.0);
}

TEST(RectangleTest, CopyConstructor)
{
    Rectangle<double> rect1(Point<double>(0, 0), 5.0, 3.0);
    Rectangle<double> rect2(rect1);
    EXPECT_TRUE(rect1 == rect2);
}

// Тесты для Rhombus
TEST(RhombusTest, ConstructorAndArea)
{
    Rhombus<double> rhombus(Point<double>(0, 0), 6.0, 8.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(rhombus), 24.0);
}

TEST(RhombusTest, CenterCalculation)
{
    Rhombus<double> rhombus(Point<double>(1, 1), 4.0, 6.0);
    auto center = rhombus.center();
    EXPECT_DOUBLE_EQ(center.get_x(), 1.0);
    EXPECT_DOUBLE_EQ(center.get_y(), 4.0);
}

// Тесты для Trapezoid
TEST(TrapezoidTest, ConstructorAndArea)
{
    Trapezoid<double> trapezoid(Point<double>(0, 0), 10.0, 6.0);
    EXPECT_GT(static_cast<double>(trapezoid), 0.0);
}

TEST(TrapezoidTest, CenterCalculation)
{
    Trapezoid<double> trapezoid(Point<double>(0, 0), 8.0, 4.0);
    auto center = trapezoid.center();
    EXPECT_GT(center.get_x(), 0.0);
    EXPECT_GT(center.get_y(), 0.0);
}

// Тесты для Array
TEST(ArrayTest, DefaultConstructor)
{
    Array<Figure<double>> arr;
    EXPECT_EQ(arr.get_size(), 0);
}

TEST(ArrayTest, AddElements)
{
    Array<Figure<double>> arr;
    auto rect = std::make_shared<Rectangle<double>>(Point<double>(0, 0), 2.0, 3.0);

    arr.add(rect);
    EXPECT_EQ(arr.get_size(), 1);

    auto rhombus = std::make_shared<Rhombus<double>>(Point<double>(0, 0), 4.0, 6.0);
    arr.add(rhombus);
    EXPECT_EQ(arr.get_size(), 2);
}

TEST(ArrayTest, RemoveElement)
{
    Array<Figure<double>> arr;
    auto fig1 = std::make_shared<Rectangle<double>>(Point<double>(0, 0), 2.0, 3.0);
    auto fig2 = std::make_shared<Rhombus<double>>(Point<double>(0, 0), 4.0, 6.0);

    arr.add(fig1);
    arr.add(fig2);

    auto removed = arr.remove(0);
    EXPECT_EQ(arr.get_size(), 1);
    EXPECT_TRUE(removed == fig1);
}

TEST(ArrayTest, TotalAreaCalculation)
{
    Array<Figure<double>> arr;
    auto rect = std::make_shared<Rectangle<double>>(Point<double>(0, 0), 2.0, 3.0);  // площадь = 6
    auto rhombus = std::make_shared<Rhombus<double>>(Point<double>(0, 0), 4.0, 6.0); // площадь = 12

    arr.add(rect);
    arr.add(rhombus);

    EXPECT_DOUBLE_EQ(arr.total_area(), 18.0);
}

TEST(ArrayTest, IndexOperator)
{
    Array<Figure<double>> arr;
    auto rect = std::make_shared<Rectangle<double>>(Point<double>(0, 0), 2.0, 3.0);

    arr.add(rect);

    EXPECT_NO_THROW(arr[0]);
    EXPECT_THROW(arr[1], std::out_of_range);
}

TEST(ArrayTest, CopyConstructor)
{
    Array<Figure<double>> arr1;
    auto rect = std::make_shared<Rectangle<double>>(Point<double>(0, 0), 2.0, 3.0);
    arr1.add(rect);

    Array<Figure<double>> arr2(arr1);
    EXPECT_EQ(arr1.get_size(), arr2.get_size());
    EXPECT_TRUE(arr1 == arr2);
}

TEST(ArrayTest, MoveConstructor)
{
    Array<Figure<double>> arr1;
    auto rect = std::make_shared<Rectangle<double>>(Point<double>(0, 0), 2.0, 3.0);
    arr1.add(rect);

    size_t original_size = arr1.get_size();
    Array<Figure<double>> arr2(std::move(arr1));

    EXPECT_EQ(arr2.get_size(), original_size);
    EXPECT_EQ(arr1.get_size(), 0); // После перемещения исходный массив пуст
}

TEST(ArrayTest, AssignmentOperator)
{
    Array<Figure<double>> arr1;
    auto rect = std::make_shared<Rectangle<double>>(Point<double>(0, 0), 2.0, 3.0);
    arr1.add(rect);

    Array<Figure<double>> arr2;
    arr2 = arr1;

    EXPECT_EQ(arr1.get_size(), arr2.get_size());
    EXPECT_TRUE(arr1 == arr2);
}

TEST(ArrayTest, ResizeWithMove)
{
    Array<Figure<double>> arr;

    // Добавляем больше элементов, чем начальная емкость (10)
    for (int i = 0; i < 15; ++i)
    {
        auto rect = std::make_shared<Rectangle<double>>(Point<double>(i, i), 1.0, 1.0);
        arr.add(rect);
    }

    EXPECT_EQ(arr.get_size(), 15);
    // Все элементы должны быть доступны после resize
    for (int i = 0; i < 15; ++i)
    {
        EXPECT_NO_THROW(arr[i]);
    }
}

// Тесты полиморфизма
TEST(PolymorphismTest, FigureBaseClass)
{
    std::shared_ptr<Figure<double>> fig1 = std::make_shared<Rectangle<double>>(Point<double>(0, 0), 4.0, 3.0);
    std::shared_ptr<Figure<double>> fig2 = std::make_shared<Rhombus<double>>(Point<double>(0, 0), 6.0, 4.0);

    EXPECT_DOUBLE_EQ(static_cast<double>(*fig1), 12.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(*fig2), 12.0);

    auto center1 = fig1->center();
    auto center2 = fig2->center();

    EXPECT_TRUE(center1.get_x() >= 0);
    EXPECT_TRUE(center2.get_x() >= 0);
}

// Тесты для различных типов данных
TEST(TemplateTest, DifferentDataTypes)
{
    // int
    Rectangle<int> rect_int(Point<int>(0, 0), 4, 3);
    EXPECT_EQ(static_cast<double>(rect_int), 12.0);

    // float
    Rectangle<float> rect_float(Point<float>(0, 0), 4.0f, 3.0f);
    EXPECT_FLOAT_EQ(static_cast<double>(rect_float), 12.0f);

    // double
    Rectangle<double> rect_double(Point<double>(0, 0), 4.0, 3.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(rect_double), 12.0);
}

// Тесты исключений
TEST(ExceptionTest, InvalidParameters)
{
    // Отрицательные параметры
    EXPECT_THROW(Rectangle<double>(Point<double>(0, 0), -1.0, 2.0), std::invalid_argument);
    EXPECT_THROW(Rhombus<double>(Point<double>(0, 0), -1.0, 2.0), std::invalid_argument);
    EXPECT_THROW(Trapezoid<double>(Point<double>(0, 0), -1.0, 2.0), std::invalid_argument);
    EXPECT_THROW(Trapezoid<double>(Point<double>(0, 0), 5.0, 10.0), std::invalid_argument);
}

TEST(ExceptionTest, ArrayBounds)
{
    Array<Figure<double>> arr;
    auto rect = std::make_shared<Rectangle<double>>(Point<double>(0, 0), 2.0, 3.0);
    arr.add(rect);

    EXPECT_NO_THROW(arr[0]);
    EXPECT_THROW(arr[1], std::out_of_range);
    EXPECT_THROW(arr.remove(1), std::out_of_range);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}