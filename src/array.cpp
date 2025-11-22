#include "../include/array.h"
#include <utility>
#include <algorithm>

template <typename T>
Array<T>::Array() : capacity(10)
{
    data = std::shared_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[capacity]);
}

template <typename T>
Array<T>::Array(const Array &other) : size(other.size), capacity(other.capacity)
{
    data = std::shared_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[capacity]);
    for (size_t i = 0; i < size; ++i)
    {
        data[i] = other.data[i];
    }
}

template <typename T>
Array<T>::Array(Array &&other) noexcept
    : data(std::move(other.data)), size(other.size), capacity(other.capacity)
{
    other.size = 0;
    other.capacity = 0;
}

template <typename T>
Array<T>::~Array() = default;

template <typename T>
Array<T> &Array<T>::operator=(const Array &other)
{
    if (this != &other)
    {
        size = other.size;
        capacity = other.capacity;
        data = std::shared_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[capacity]); // ИСПРАВЛЕНО
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template <typename T>
Array<T> &Array<T>::operator=(Array &&other) noexcept
{
    if (this != &other)
    {
        data = std::move(other.data);
        size = other.size;
        capacity = other.capacity;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

template <typename T>
bool Array<T>::operator==(const Array &other) const
{
    if (size != other.size)
        return false;
    for (size_t i = 0; i < size; ++i)
    {
        if (data[i] && other.data[i])
        {
            if (!(*(data[i]) == *(other.data[i])))
            {
                return false;
            }
        }
        else if (data[i] != other.data[i])
        {
            return false;
        }
    }
    return true;
}

template <typename T>
void Array<T>::add(std::shared_ptr<T> element)
{
    if (size >= capacity)
    {
        resize();
    }
    data[size++] = element;
}

template <typename T>
std::shared_ptr<T> Array<T>::remove(size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }

    auto element = data[index];

    for (size_t i = index; i < size - 1; ++i)
    {
        data[i] = std::move(data[i + 1]);
    }
    --size;
    data[size].reset();

    return element;
}

template <typename T>
double Array<T>::total_area() const
{
    double total = 0.0;
    for (size_t i = 0; i < size; ++i)
        if (data[i])
            total += static_cast<double>(*data[i]);
    return total;
}

template <typename T>
size_t Array<T>::get_size() const
{
    return size;
}

template <typename T>
std::shared_ptr<T> &Array<T>::operator[](size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
const std::shared_ptr<T> &Array<T>::operator[](size_t index) const
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
void Array<T>::resize()
{
    capacity *= 2;
    auto new_data = std::shared_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[capacity]);
    for (size_t i = 0; i < size; ++i)
    {
        new_data[i] = std::move(data[i]);
    }
    data = std::move(new_data);
}

template class Array<Figure<int>>;
template class Array<Figure<double>>;
template class Array<Figure<float>>;