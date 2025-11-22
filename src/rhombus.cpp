#include "../include/rhombus.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

template <typename T>
Rhombus<T>::Rhombus(const Point<T> &bottom_point, T horizontal_diag, T vertical_diag)
    : horizontal_diag(horizontal_diag), vertical_diag(vertical_diag)
{
    if (horizontal_diag <= 0 || vertical_diag <= 0)
    {
        throw std::invalid_argument("Диагонали должны быть положительными");
    }
    calculate_vertices(bottom_point, horizontal_diag, vertical_diag);
}

template <typename T>
Rhombus<T>::Rhombus(const Rhombus &other)
    : horizontal_diag(other.horizontal_diag), vertical_diag(other.vertical_diag)
{
    for (size_t i = 0; i < 4; ++i)
    {
        vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
    }
}

template <typename T>
Rhombus<T>::Rhombus(Rhombus<T> &&other) noexcept
    : horizontal_diag(other.horizontal_diag), vertical_diag(other.vertical_diag)
{
    for (size_t i = 0; i < 4; ++i)
    {
        vertices[i] = std::move(other.vertices[i]);
    }
    other.horizontal_diag = 0;
    other.vertical_diag = 0;
}

template <typename T>
Rhombus<T> &Rhombus<T>::operator=(Rhombus<T> &&other) noexcept
{
    if (this != &other)
    {
        for (size_t i = 0; i < 4; ++i)
        {
            vertices[i] = std::move(other.vertices[i]);
        }
        horizontal_diag = other.horizontal_diag;
        vertical_diag = other.vertical_diag;
        other.horizontal_diag = 0;
        other.vertical_diag = 0;
    }
    return *this;
}

template <typename T>
Rhombus<T> &Rhombus<T>::operator=(const Rhombus<T> &other)
{
    if (this != &other)
    {
        horizontal_diag = other.horizontal_diag;
        vertical_diag = other.vertical_diag;
        for (size_t i = 0; i < 4; ++i)
        {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
    }
    return *this;
}

template <typename T>
Point<T> Rhombus<T>::center() const
{
    T center_x = (vertices[0]->get_x() + vertices[2]->get_x()) / 2;
    T center_y = (vertices[0]->get_y() + vertices[2]->get_y()) / 2;
    return Point<T>(center_x, center_y);
}

template <typename T>
void Rhombus<T>::print(std::ostream &os) const
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
void Rhombus<T>::read(std::istream &is)
{
    T x, y, h_diag, v_diag;
    if (!(is >> x >> y >> h_diag >> v_diag))
    {
        throw std::runtime_error("Ошибка чтения аргументов ромба");
    }

    if (h_diag <= 0 || v_diag <= 0)
    {
        throw std::invalid_argument("Диагонали должны быть положительными");
    }

    calculate_vertices(Point<T>(x, y), h_diag, v_diag);
    horizontal_diag = h_diag;
    vertical_diag = v_diag;
}

template <typename T>
bool Rhombus<T>::operator==(const Figure<T> &other) const
{
    const auto *other_rhombus = dynamic_cast<const Rhombus<T> *>(&other);
    if (!other_rhombus)
        return false;

    for (size_t i = 0; i < 4; ++i)
    {
        if (!(*vertices[i] == *other_rhombus->vertices[i]))
        {
            return false;
        }
    }
    return true;
}

template <typename T>
std::unique_ptr<Figure<T>> Rhombus<T>::clone() const
{
    return std::make_unique<Rhombus<T>>(*this);
}

template <typename T>
Rhombus<T>::operator double() const
{
    return 0.5 * static_cast<double>(horizontal_diag) * static_cast<double>(vertical_diag);
}

template <typename T>
void Rhombus<T>::calculate_vertices(const Point<T> &bottom_point, T horizontal_diag, T vertical_diag)
{
    T center_x = bottom_point.get_x();
    T center_y = bottom_point.get_y() + vertical_diag / 2;

    vertices[0] = std::make_unique<Point<T>>(center_x, center_y - vertical_diag / 2);
    vertices[1] = std::make_unique<Point<T>>(center_x + horizontal_diag / 2, center_y);
    vertices[2] = std::make_unique<Point<T>>(center_x, center_y + vertical_diag / 2);
    vertices[3] = std::make_unique<Point<T>>(center_x - horizontal_diag / 2, center_y);
}

template class Rhombus<int>;
template class Rhombus<double>;
template class Rhombus<float>;