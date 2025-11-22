#ifndef ARRAY_H
#define ARRAY_H

#include "figure.h"
#include <memory>
#include <cstddef>
#include <stdexcept>

template <typename T>
class Array
{
public:
    Array();
    Array(const Array &other);
    Array(Array &&other) noexcept;
    ~Array();

    Array &operator=(const Array &other);
    Array &operator=(Array &&other) noexcept;
    bool operator==(const Array &other) const;
    void add(std::shared_ptr<T> element);
    std::shared_ptr<T> remove(size_t index);
    double total_area() const;
    std::shared_ptr<T> &operator[](size_t index);
    const std::shared_ptr<T> &operator[](size_t index) const;

    size_t get_size() const;

private:
    std::shared_ptr<std::shared_ptr<T>[]> data;
    size_t size{0};
    size_t capacity{10};
    void resize();
};

#endif