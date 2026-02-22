/***************************************************************************************************
 * @file  Array.hpp
 * @brief Declaration of the Array class
 **************************************************************************************************/

#pragma once

#include <initializer_list>
#include <iostream>

/**
 * @class Array
 * @brief A minimal dynamic array class that manually manages heap memory for a sequence of 'Type'.
 * @tparam Type The type of the array's data.
 */
template <typename Type>
class Array {
public:
    /**
     * @brief Default constructor. Does not allocate any data.
     */
    Array();

    /**
     * @brief Constructs an array with a given size. Elements are default-initialized (Type()).
     * @param size The number of elements.
     */
    explicit Array(std::size_t size);

    /**
    * @brief Constructs an array with a given size. Elements are initialized with a specified value.
     * @param size The number of elements.
     * @param default_value The value to fill the array with.
     */
    Array(std::size_t size, const Type& default_value);

    /**
     * @brief Constructs an array from an initializer_list.
     * @param values The values to fill the array with.
     */
    Array(const std::initializer_list<Type>& values);

    /**
     * @brief Copy constructor. Performs a deep copy.
     * @param other The array to copy.
     */
    Array(const Array& other);

    /**
     * @brief Destructor. Releases allocated memory.
     */
    ~Array();

    /**
     * @brief Copy assignment operator. Performs a deep copy.
     * @param other The array to copy.
     * @return A reference to the array.
     */
    Array& operator=(const Array& other);

    /**
     * @brief Access element at 'index'.
     * @param index The index of the wanted element.
     * @note No bounds checking.
     * @return A reference to the wanted element.
     */
    Type& operator[](std::size_t index);

    /**
     * @brief Access element at 'index'.
     * @param index The index of the wanted element.
     * @note No bounds checking.
     * @return A const-reference to the wanted element.
     */
    const Type& operator[](std::size_t index) const;

    /**
     * @return Current number of elements in the array.
     */
    std::size_t get_size() const;

    /**
     * @return A pointer to the first element in the internal array.
     * @note Will return nullptr if the array is empty.
     */
    Type* get_data();

    /**
     * @return A const pointer to the first element in the internal array.
     * @note Will return nullptr if the array is empty.
     */
    const Type* get_data() const;

    /**
     * @return True if the array has no elements.
     */
    bool empty() const;

    /**
     * @return An iterator to the beginning of the array.
     */
    Type* begin();

    /**
     * @return A const iterator to the beginning of the array.
     */
    const Type* begin() const;

    /**
     * @return An iterator to the element past the end of the array.
     */
    Type* end();

    /**
     * @return A const iterator to the element past the end of the array.
     */
    const Type* end() const;

    /**
     * @brief Resizes the array. If expanded, new elements are default-constructed. If shrunk,
     * extra elements are discarded.
     * @param new_size The new size of the array.
     */
    void resize(std::size_t new_size);

    /**
     * @brief Fills the array with a value.
     * @param value The value to fill the array with.
     */
    void fill(const Type& value);

    /**
     * @brief Assigns new content to the array, replacing its contents and modifying its size
     * accordingly.
     * @param new_size The new size of the array.
     * @param value The value to fill the array with.
     */
    void assign(std::size_t new_size, const Type& value);

protected:
    std::size_t size; ///< Number of elements in the array.
    Type* data;       ///< Pointer to heap-allocated data.
};

/**
 * @brief Outputs an array to an output stream.
 * @param stream The stream to output to.
 * @param array The array to output.
 * @return A reference to the stream.
 */
template <typename Type>
std::ostream& operator <<(std::ostream& stream, const Array<Type>& array) {
    stream << '(';
    for(const Type& element : array) {
        stream << element;
        if(&element < array.end() - 1) { stream << ", "; }
    }
    stream << ')';

    return stream;
}

template <typename Type>
Array<Type>::Array() : size(0), data(nullptr) { }

template <typename Type>
Array<Type>::Array(std::size_t size)
    : size(size), data(new Type[size]) {
    Type default_value = Type();
    for(unsigned int i = 0 ; i < size ; ++i) { data[i] = default_value; }
}

template <typename Type>
Array<Type>::Array(std::size_t size, const Type& default_value)
    : size(size), data(new Type[size]) {
    for(unsigned int i = 0 ; i < size ; ++i) { data[i] = default_value; }
}

template <typename Type>
Array<Type>::Array(const std::initializer_list<Type>& values)
    : size(values.size()), data(new Type[size]) {
    unsigned int i = 0;
    for(const Type& value : values) { data[i++] = value; }
}

template <typename Type>
Array<Type>::Array(const Array& other)
    : size(other.size), data(new Type[size]) {
    for(unsigned int i = 0 ; i < size ; ++i) { data[i] = other[i]; }
}

template <typename Type>
Array<Type>::~Array() {
    delete[] data;
}

template <typename Type>
Array<Type>& Array<Type>::operator=(const Array& other) {
    if(this == &other) { return *this; }

    delete[] data;

    size = other.size;
    data = new Type[size];
    for(unsigned int i = 0 ; i < size ; ++i) { data[i] = other[i]; }

    return *this;
}

template <typename Type>
Type& Array<Type>::operator[](std::size_t index) { return data[index]; }

template <typename Type>
const Type& Array<Type>::operator[](std::size_t index) const { return data[index]; }

template <typename Type>
std::size_t Array<Type>::get_size() const { return size; }

template <typename Type>
Type* Array<Type>::get_data() { return data; }

template <typename Type>
const Type* Array<Type>::get_data() const { return data; }

template <typename Type>
bool Array<Type>::empty() const { return size == 0; }

template <typename Type>
Type* Array<Type>::begin() { return data; }

template <typename Type>
const Type* Array<Type>::begin() const { return data; }

template <typename Type>
Type* Array<Type>::end() { return data + size; }

template <typename Type>
const Type* Array<Type>::end() const { return data + size; }

template <typename Type>
void Array<Type>::resize(std::size_t new_size) {
    if(new_size == size) { return; }

    if(new_size > 0) {
        Type* temp = data;
        data = new Type[new_size];
        Type default_value = Type();
        for(unsigned int i = 0 ; i < new_size ; ++i) { data[i] = i < size ? temp[i] : default_value; }
        size = new_size;
        delete[] temp;
    } else {
        delete[] data;
        size = 0;
        data = nullptr;
    }
}

template <typename Type>
void Array<Type>::fill(const Type& value) {
    for(std::size_t i = 0 ; i < size ; ++i) { data[i] = value; }
}

template <typename Type>
void Array<Type>::assign(std::size_t new_size, const Type& value) {
    if(new_size != size) {
        delete[] data;
        size = new_size;
        data = new Type[size];
    }

    fill(value);
}
