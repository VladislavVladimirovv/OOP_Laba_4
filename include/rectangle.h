#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figure.h"
#include <array>
#include <memory>

template <typename T>
class Rectangle : public Figure<T>
{
public:
    Rectangle() = default;
    Rectangle(const Point<T> &bottom_left, T width, T height);
    Rectangle(const Rectangle &other);
    Rectangle(Rectangle &&other) noexcept;
    ~Rectangle() = default;

    Point<T> center() const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;
    std::unique_ptr<Figure<T>> clone() const override;
    bool operator==(const Figure<T> &other) const override;
    Rectangle &operator=(Rectangle &&other) noexcept;
    Rectangle &operator=(const Rectangle &other);
    operator double() const override;

private:
    std::array<std::unique_ptr<Point<T>>, 4> vertices;
    T width{0};
    T height{0};
    void calculate_vertices(const Point<T> &bottom_left, T width, T height);
};

#endif