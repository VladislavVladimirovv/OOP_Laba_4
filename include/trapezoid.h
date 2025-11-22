#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "figure.h"
#include <array>
#include <memory>

template <typename T>
class Trapezoid : public Figure<T>
{
public:
    Trapezoid() = default;
    Trapezoid(const Point<T> &bottom_base_left, T bottom_base_length, T top_base_length);
    Trapezoid(const Trapezoid &other);
    Trapezoid(Trapezoid &&other) noexcept;
    ~Trapezoid() override = default;

    Point<T> center() const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;
    Trapezoid &operator=(const Trapezoid &other);
    Trapezoid &operator=(Trapezoid &&other) noexcept;
    bool operator==(const Figure<T> &other) const override;
    std::unique_ptr<Figure<T>> clone() const override;
    operator double() const override;

    T get_bottom_base_length() const { return bottom_base_length; }
    T get_top_base_length() const { return top_base_length; }
    T get_height() const { return height; }
    T get_side_length() const { return side_length; }

private:
    std::array<std::unique_ptr<Point<T>>, 4> vertices;
    T bottom_base_length{0};
    T top_base_length{0};
    T height{0};
    T side_length{0};

    void calculate_vertices(const Point<T> &bottom_base_left, T bottom_base_length, T top_base_length);
    void calculate_geometry();
};

#endif