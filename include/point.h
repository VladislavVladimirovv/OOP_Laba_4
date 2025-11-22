#ifndef POINT_H
#define POINT_H

#include <type_traits>
#include <memory>
#include <concepts>

template <typename T>
concept Scalar = std::is_scalar_v<T>;

template <Scalar T>
class Point
{
public:
    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}

    T get_x() const { return x; }
    T get_y() const { return y; }
    void set_x(T newX) { x = newX; }
    void set_y(T newY) { y = newY; }

    bool operator==(const Point<T> &other) const
    {
        return x == other.x && y == other.y;
    }

private:
    T x, y;
};

#endif