#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "figure.h"
#include <array>
#include <memory>

template <typename T>
class Rhombus : public Figure<T>
{
public:
    Rhombus() = default;
    Rhombus(const Point<T> &bottom_point, T horizontal_diag, T vertical_diag);
    Rhombus(const Rhombus &other);
    Rhombus(Rhombus &&other) noexcept;
    ~Rhombus() = default;

    Point<T> center() const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;
    Rhombus &operator=(Rhombus &&other) noexcept;
    Rhombus &operator=(const Rhombus &other);
    bool operator==(const Figure<T> &other) const override;
    std::unique_ptr<Figure<T>> clone() const override;
    operator double() const override;

    T get_horizontal_diag() const { return horizontal_diag; }
    T get_vertical_diag() const { return vertical_diag; }

private:
    std::array<std::unique_ptr<Point<T>>, 4> vertices;
    T horizontal_diag{0};
    T vertical_diag{0};
    void calculate_vertices(const Point<T> &bottom_point, T horizontal_diag, T vertical_diag);
};

#endif