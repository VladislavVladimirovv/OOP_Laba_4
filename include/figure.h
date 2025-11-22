#ifndef FIGURE_H
#define FIGURE_H

#include "point.h"
#include <iostream>
#include <memory>

template <typename T>
class Figure
{
public:
    virtual ~Figure() = default;

    virtual Point<T> center() const = 0;
    virtual void print(std::ostream &os) const = 0;
    virtual void read(std::istream &is) = 0;
    virtual bool operator==(const Figure &other) const = 0;
    virtual std::unique_ptr<Figure<T>> clone() const = 0;
    virtual operator double() const = 0;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Figure<T> &figure)
{
    figure.print(os);
    return os;
}

template <typename T>
std::istream &operator>>(std::istream &is, Figure<T> &figure)
{
    figure.read(is);
    return is;
}

#endif