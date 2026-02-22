/***************************************************************************************************
 * @file  Array2D.hpp
 * @brief Declaration of the Array2D class
 **************************************************************************************************/

#pragma once

#include <iostream>
#include "Array.hpp"

/**
 * @class Array2D
 * @brief A minimal dynamic array class that manually manages heap memory for a 2D sequence of
 * 'Type'.
 * @tparam Type The type of the array's data.
 */
template <typename Type>
class Array2D {
public:
    /**
     * @brief Default constructor. Does not allocate any data.
     */
    Array2D();

    /**
     * Constructs a 2D array with a given amount of rows and columns. Elements are
     * default-initialized (Type()).
     * @param height The number of rows.
     * @param width The number of columns.
     */
    Array2D(std::size_t height, std::size_t width);

    /**
     * Constructs a 2D array with a given amount of rows and columns. Elements are initialized with
     * a specified value.
     * @param height The number of rows.
     * @param width The number of columns.
     * @param default_value The value to fill the array with.
     */
    Array2D(std::size_t height, std::size_t width, Type default_value);

    /**
     * @brief Access a specific element by its row and column.
     * @param row The wanted element's row's index.
     * @param column The wanted element's column's index.
     * @note No bounds checking.
     * @return A reference to the wanted element.
     */
    Type& operator ()(std::size_t row, std::size_t column);

    /**
     * @brief Access a specific element by its row and column.
     * @param row The wanted element's row's index.
     * @param column The wanted element's column's index.
     * @note No bounds checking.
     * @return A const-reference to the wanted element.
     */
    const Type& operator ()(std::size_t row, std::size_t column) const;

    /**
     * @brief Access a specific row.
     * @param row The wanted row's index.
     * @note No bounds checking.
     * @return A reference to the wanted row.
     */
    Array<Type>& operator[](std::size_t row);

    /**
     * @brief Access a specific row.
     * @param row The wanted row's index.
     * @note No bounds checking.
     * @return A const-reference to the wanted row.
     */
    const Array<Type>& operator[](std::size_t row) const;

    /**
     * @return Current number of rows in the array.
     */
    std::size_t get_height() const;

    /**
     * @return Current number of columns in the array.
     */
    std::size_t get_width() const;

    /**
     * @return A reference to the internal Array.
     */
    Array<Array<Type>>& get_data();

    /**
     * @return A const-reference to the internal Array.
     */
    const Array<Array<Type>>& get_data() const;

    /**
     * @return True if the array has no elements.
     */
    bool empty() const;

    /**
     * @return An iterator to the beginning of the array.
     */
    Array<Type>* begin();

    /**
     * @return A const iterator to the beginning of the array.
     */
    const Array<Type>* begin() const;

    /**
     * @return An iterator to the row past the end of the array.
     */
    Array<Type>* end();

    /**
     * @return A const iterator to the row past the end of the array.
     */
    const Array<Type>* end() const;

    /**
     * @brief Resizes the array. If expanded, new elements are default-constructed. If shrunk,
     * extra elements are discarded.
     * @param new_height The new number of rows of the array.
     * @param new_width The new number of columns of the array.
     */
    void resize(std::size_t new_height, std::size_t new_width);

    /**
     * @brief Fills the array with a value.
     * @param value The value to fill the array with.
     */
    void fill(const Type& value);

    /**
     * @brief Assigns new content to the array, replacing its contents and modifying its size
     * accordingly.
     * @param new_height The new number of rows of the array.
     * @param new_width The new number of columns of the array.
     * @param value The value to fill the array with.
     */
    void assign(std::size_t new_height, std::size_t new_width, const Type& value);

protected:
    std::size_t height;      ///< Number of rows in the array.
    std::size_t width;       ///< Number of columns in the array.
    Array<Array<Type>> data; ///< Pointer to heap-allocated data.
};

/**
 * @brief Outputs an array to an output stream.
 * @param stream The stream to output to.
 * @param array The array to output.
 * @return A reference to the stream.
 */
template <typename Type>
std::ostream& operator <<(std::ostream& stream, const Array2D<Type>& array) {
    stream << '(';
    for(const Array<Type>& row : array) {
        if(&row > array.begin()) { stream << ' '; }
        stream << row;
        if(&row < array.end() - 1) { stream << ",\n"; }
    }
    stream << ')';

    return stream;
}

template <typename Type>
Array2D<Type>::Array2D() : height(0), width(0), data() { }

template <typename Type>
Array2D<Type>::Array2D(std::size_t height, std::size_t width)
    : height(height), width(width), data(height) {
    for(Array<Type>& row : data) { row.resize(width); }
}

template <typename Type>
Array2D<Type>::Array2D(std::size_t height, std::size_t width, Type default_value)
    : height(height), width(width), data(height) {
    for(Array<Type>& row : data) { row.assign(width, default_value); }
}

template <typename Type>
Type& Array2D<Type>::operator()(std::size_t row, std::size_t column) {
    return data[row][column];
}

template <typename Type>
const Type& Array2D<Type>::operator()(std::size_t row, std::size_t column) const {
    return data[row][column];
}

template <typename Type>
Array<Type>& Array2D<Type>::operator[](std::size_t row) {
    return data[row];
}

template <typename Type>
const Array<Type>& Array2D<Type>::operator[](std::size_t row) const {
    return data[row];
}

template <typename Type>
std::size_t Array2D<Type>::get_height() const {
    return height;
}

template <typename Type>
std::size_t Array2D<Type>::get_width() const {
    return width;
}

template <typename Type>
Array<Array<Type>>& Array2D<Type>::get_data() {
    return data;
}

template <typename Type>
const Array<Array<Type>>& Array2D<Type>::get_data() const {
    return data;
}

template <typename Type>
bool Array2D<Type>::empty() const {
    return height == 0 || width == 0;
}

template <typename Type>
Array<Type>* Array2D<Type>::begin() {
    return data.begin();
}

template <typename Type>
const Array<Type>* Array2D<Type>::begin() const {
    return data.begin();
}

template <typename Type>
Array<Type>* Array2D<Type>::end() {
    return data.end();
}

template <typename Type>
const Array<Type>* Array2D<Type>::end() const {
    return data.end();
}

template <typename Type>
void Array2D<Type>::resize(std::size_t new_height, std::size_t new_width) {
    width = new_width;
    height = new_height;
    data.resize(height);
    for(Array<Type>& row : data) { row.resize(width); }
}

template <typename Type>
void Array2D<Type>::fill(const Type& value) {
    for(Array<Type>& row : data) {
        for(Type& element : row) {
            element = value;
        }
    }
}

template <typename Type>
void Array2D<Type>::assign(std::size_t new_height, std::size_t new_width, const Type& value) {
    width = new_width;
    height = new_height;
    data.resize(height);
    for(Array<Type>& row : data) { row.assign(width, value); }
}
