/***************************************************************************************************
 * @file  quaternion.hpp
 * @brief Declaration of the quaternion struct
 **************************************************************************************************/

#pragma once

#include <iostream>
#include "mat4.hpp"

/**
 * @class quaternion
 * @brief Represents a quaternion with each of its four coefficients (x, y, z, w) where a quaternion
 * q = x*i + y*j + z*k + d.
 */
struct quaternion {
    quaternion();
    quaternion(float x, float y, float z, float w);

    quaternion& operator +=(const quaternion& q);
    quaternion& operator -=(const quaternion& q);
    quaternion& operator *=(const quaternion& q);
    quaternion& operator /=(const quaternion& q);

    quaternion& operator *=(float scalar);
    quaternion& operator /=(float scalar);

    float norm() const;
    quaternion conjugate() const;
    quaternion inverse() const;
    mat4 toMatrix() const;

    float x; ///< The coefficient of the i imaginary unit.
    float y; ///< The coefficient of the j imaginary unit.
    float z; ///< The coefficient of the k imaginary unit.
    float w; ///< The real part of the quaternion.
};

float norm(const quaternion& q);
quaternion conjugate(const quaternion& q);
quaternion inverse(const quaternion& q);
mat4 toMatrix(const quaternion& q);

std::ostream& operator <<(std::ostream& stream, const quaternion& q);
std::istream& operator >>(std::istream& stream, quaternion& q);

quaternion operator +(const quaternion& q, const quaternion& r);
quaternion operator -(const quaternion& q, const quaternion& r);
quaternion operator *(const quaternion& q, const quaternion& r);
quaternion operator /(const quaternion& q, const quaternion& r);

quaternion operator *(const quaternion& q, float scalar);
quaternion operator *(float scalar, const quaternion& q);
quaternion operator /(const quaternion& q, float scalar);
quaternion operator /(float scalar, const quaternion& q);