#include "../include/trapezoid.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

template <typename T>
Trapezoid<T>::Trapezoid(const Point<T> &bottom_base_left, T bottom_base_length, T top_base_length)
    : bottom_base_length(bottom_base_length), top_base_length(top_base_length)
{
    if (bottom_base_length <= 0 || top_base_length <= 0)
    {
        throw std::invalid_argument("Длина основания должна быть положительной");
    }
    if (top_base_length >= bottom_base_length)
    {
        throw std::invalid_argument("Верхнее основание должно быть короче нижнего");
    }

    height = (bottom_base_length + top_base_length) / 2;
    calculate_geometry();
    calculate_vertices(bottom_base_left, bottom_base_length, top_base_length);
}

template <typename T>
Trapezoid<T>::Trapezoid(const Trapezoid &other)
    : bottom_base_length(other.bottom_base_length), top_base_length(other.top_base_length),
      height(other.height), side_length(other.side_length)
{
    for (size_t i = 0; i < 4; ++i)
    {
        vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
    }
}

template <typename T>
Trapezoid<T>::Trapezoid(Trapezoid<T> &&other) noexcept
    : bottom_base_length(other.bottom_base_length), top_base_length(other.top_base_length),
      height(other.height), side_length(other.side_length)
{
    for (size_t i = 0; i < 4; ++i)
    {
        vertices[i] = std::move(other.vertices[i]);
    }
    other.bottom_base_length = 0;
    other.top_base_length = 0;
    other.height = 0;
    other.side_length = 0;
}

template <typename T>
Point<T> Trapezoid<T>::center() const
{
    T center_x = 0, center_y = 0;
    for (const auto &vertex : vertices)
    {
        center_x += vertex->get_x();
        center_y += vertex->get_y();
    }
    return Point<T>(center_x / 4, center_y / 4);
}

template <typename T>
void Trapezoid<T>::print(std::ostream &os) const
{
    os << std::fixed << std::setprecision(2);
    for (size_t i = 0; i < 4; ++i)
    {
        os << "(" << vertices[i]->get_x() << ", " << vertices[i]->get_y() << ")";
        if (i < 3)
            os << " ";
    }
}

template <typename T>
void Trapezoid<T>::read(std::istream &is)
{
    T x, y, bottom_base, top_base;
    if (!(is >> x >> y >> bottom_base >> top_base))
    {
        throw std::runtime_error("Ошибка чтения аргументов трапеции");
    }

    if (bottom_base <= 0 || top_base <= 0)
    {
        throw std::invalid_argument("Длина основания должна быть положительной");
    }
    if (top_base >= bottom_base)
    {
        throw std::invalid_argument("Верхнее основание долэно быть короче нижнего");
    }

    calculate_vertices(Point<T>(x, y), bottom_base, top_base);
    bottom_base_length = bottom_base;
    top_base_length = top_base;
    calculate_geometry();
}

template <typename T>
Trapezoid<T> &Trapezoid<T>::operator=(const Trapezoid<T> &other)
{
    if (this != &other)
    {
        bottom_base_length = other.bottom_base_length;
        top_base_length = other.top_base_length;
        height = other.height;
        side_length = other.side_length;

        for (size_t i = 0; i < 4; ++i)
        {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
    }
    return *this;
}

template <typename T>
Trapezoid<T> &Trapezoid<T>::operator=(Trapezoid<T> &&other) noexcept
{
    if (this != &other)
    {
        for (size_t i = 0; i < 4; ++i)
        {
            vertices[i] = std::move(other.vertices[i]);
        }
        bottom_base_length = other.bottom_base_length;
        top_base_length = other.top_base_length;
        height = other.height;
        side_length = other.side_length;

        other.bottom_base_length = 0;
        other.top_base_length = 0;
        other.height = 0;
        other.side_length = 0;
    }
    return *this;
}

template <typename T>
bool Trapezoid<T>::operator==(const Figure<T> &other) const
{
    const auto *other_trapezoid = dynamic_cast<const Trapezoid<T> *>(&other);
    if (!other_trapezoid)
        return false;

    for (size_t i = 0; i < 4; ++i)
    {
        if (!(*vertices[i] == *other_trapezoid->vertices[i]))
        {
            return false;
        }
    }
    return true;
}

template <typename T>
std::unique_ptr<Figure<T>> Trapezoid<T>::clone() const
{
    return std::make_unique<Trapezoid<T>>(*this);
}

template <typename T>
Trapezoid<T>::operator double() const
{
    return 0.5 * (bottom_base_length + top_base_length) * height;
}

template <typename T>
void Trapezoid<T>::calculate_vertices(const Point<T> &bottom_base_left, T bottom_base_length, T top_base_length)
{
    T offset = (bottom_base_length - top_base_length) / 2;

    vertices[0] = std::make_unique<Point<T>>(bottom_base_left);
    vertices[1] = std::make_unique<Point<T>>(bottom_base_left.get_x() + bottom_base_length, bottom_base_left.get_y());
    vertices[2] = std::make_unique<Point<T>>(bottom_base_left.get_x() + offset + top_base_length, bottom_base_left.get_y() + height);
    vertices[3] = std::make_unique<Point<T>>(bottom_base_left.get_x() + offset, bottom_base_left.get_y() + height);
}

template <typename T>
void Trapezoid<T>::calculate_geometry()
{
    T base_diff = (bottom_base_length - top_base_length) / 2;
    side_length = std::sqrt(base_diff * base_diff + height * height);
}

template class Trapezoid<int>;
template class Trapezoid<double>;
template class Trapezoid<float>;