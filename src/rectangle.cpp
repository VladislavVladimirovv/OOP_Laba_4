#include "../include/rectangle.h"
#include "../include/figure.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

template <typename T>
Rectangle<T>::Rectangle(const Point<T> &bottom_left, T width, T height)
    : width(width), height(height)
{
    if (width <= 0 || height <= 0)
    {
        throw std::invalid_argument("Длина и ширина строн должны быть положительными");
    }
    calculate_vertices(bottom_left, width, height);
}

template <typename T>
Rectangle<T>::Rectangle(const Rectangle &other) : width(other.width), height(other.height)
{
    for (size_t i = 0; i < 4; ++i)
    {
        vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
    }
}

template <typename T>
Rectangle<T>::Rectangle(Rectangle<T> &&other) noexcept
    : width(other.width), height(other.height)
{
    for (size_t i = 0; i < 4; ++i)
    {
        vertices[i] = std::move(other.vertices[i]);
    }
    other.width = 0;
    other.height = 0;
}

template <typename T>
Point<T> Rectangle<T>::center() const
{
    T center_x = (vertices[0]->get_x() + vertices[2]->get_x()) / 2;
    T center_y = (vertices[0]->get_y() + vertices[2]->get_y()) / 2;
    return Point<T>(center_x, center_y);
}

template <typename T>
void Rectangle<T>::print(std::ostream &os) const
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
void Rectangle<T>::read(std::istream &is)
{
    T x, y, w, h;
    if (!(is >> x >> y >> w >> h))
    {
        throw std::runtime_error("Ошибка чтения аргументов прямоугольника");
    }

    if (w <= 0 || h <= 0)
    {
        throw std::invalid_argument("Длина и ширина должны быть положительными");
    }

    calculate_vertices(Point<T>(x, y), w, h);
    width = w;
    height = h;
}

template <typename T>
Rectangle<T> &Rectangle<T>::operator=(Rectangle<T> &&other) noexcept
{
    if (this != &other)
    {
        for (size_t i = 0; i < 4; ++i)
        {
            vertices[i] = std::move(other.vertices[i]);
        }
        width = other.width;
        height = other.height;
        other.width = 0;
        other.height = 0;
    }
    return *this;
}

template <typename T>
bool Rectangle<T>::operator==(const Figure<T> &other) const
{
    const auto *other_rect = dynamic_cast<const Rectangle<T> *>(&other);
    if (!other_rect)
        return false;

    for (size_t i = 0; i < 4; ++i)
    {
        if (!(*vertices[i] == *other_rect->vertices[i]))
        {
            return false;
        }
    }
    return true;
}

template <typename T>
Rectangle<T> &Rectangle<T>::operator=(const Rectangle<T> &other)
{
    if (this != &other)
    {
        width = other.width;
        height = other.height;
        for (size_t i = 0; i < 4; ++i)
        {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
    }
    return *this;
}

template <typename T>
std::unique_ptr<Figure<T>> Rectangle<T>::clone() const
{
    return std::make_unique<Rectangle<T>>(*this);
}

template <typename T>
Rectangle<T>::operator double() const
{
    return static_cast<double>(width) * static_cast<double>(height);
}

template <typename T>
void Rectangle<T>::calculate_vertices(const Point<T> &bottom_left, T width, T height)
{
    vertices[0] = std::make_unique<Point<T>>(bottom_left);
    vertices[1] = std::make_unique<Point<T>>(bottom_left.get_x() + width, bottom_left.get_y());
    vertices[2] = std::make_unique<Point<T>>(bottom_left.get_x() + width, bottom_left.get_y() + height);
    vertices[3] = std::make_unique<Point<T>>(bottom_left.get_x(), bottom_left.get_y() + height);
}

template class Rectangle<int>;
template class Rectangle<double>;
template class Rectangle<float>;