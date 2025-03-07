/***************************************************************************************************
 * @file  quaternion.cpp
 * @brief Implementation of the quaternion struct
 **************************************************************************************************/

#include "maths/quaternion.hpp"

#include <cmath>

quaternion::quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }

quaternion::quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }

quaternion& quaternion::operator +=(const quaternion& q) {
    x += q.x;
    y += q.y;
    z += q.z;
    w += q.w;

    return *this;
}

quaternion& quaternion::operator -=(const quaternion& q) {
    x -= q.x;
    y -= q.y;
    z -= q.z;
    w -= q.w;

    return *this;;
}

quaternion& quaternion::operator *=(const quaternion& q) {
    x = y * q.z - z * q.y + x * q.w + w * q.x;
    y = z * q.x - x * q.z + y * q.w + w * q.y;
    z = x * q.y - y * q.x + z * q.w + w * q.z;
    w = w * q.w - x * q.x - y * q.y - z * q.z;

    return *this;
}

quaternion& quaternion::operator /=(const quaternion& q) {
    quaternion i = q.inverse();

    x = y * i.z - z * i.y + x * i.w + w * i.x;
    y = z * i.x - x * i.z + y * i.w + w * i.y;
    z = x * i.y - y * i.x + z * i.w + w * i.z;
    w = w * i.w - x * i.x - y * i.y - z * i.z;

    return *this;
}

quaternion& quaternion::operator *=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;

    return *this;;
}

quaternion& quaternion::operator /=(float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;

    return *this;;
}

float quaternion::norm() const {
    return sqrt(x * x + y * y + z * z + w * w);
}

quaternion quaternion::conjugate() const {
    return quaternion(-x, -y, -z, w);
}

quaternion quaternion::inverse() const {
    float n = norm();
    n = 1.0f / (n * n);

    return quaternion(-n * x, -n * y, -n * z, n * w);
}

mat4 quaternion::toMatrix() const {
    return mat4(x, -y, -z, -w,
                y, x, -w, z,
                z, w, x, -y,
                w, -z, y, x);
}

float norm(const quaternion& q) {
    return q.norm();
}

quaternion conjugate(const quaternion& q) {
    return q.conjugate();
}

quaternion inverse(const quaternion& q) {
    return q.inverse();
}

mat4 toMatrix(const quaternion& q) {
    return q.toMatrix();
}

std::ostream& operator <<(std::ostream& stream, const quaternion& q) {
    std::cout << q.x << 'i'
              << ((q.y >= 0) ? " + " : " - ") << fabs(q.y) << 'j'
              << ((q.z >= 0) ? " + " : " - ") << fabs(q.y) << 'k'
              << ((q.w >= 0) ? " + " : " - ") << fabs(q.y);

    return stream;
}

std::istream& operator >>(std::istream& stream, quaternion& q) {
    return stream >> q.x >> q.y >> q.z >> q.w;
}

quaternion operator +(const quaternion& q, const quaternion& r) {
    return quaternion(q.x + r.x, q.y + r.y, q.z + r.z, q.w + r.w);
}

quaternion operator -(const quaternion& q, const quaternion& r) {
    return quaternion(q.x - r.x, q.y - r.y, q.z - r.z, q.w - r.w);
}

quaternion operator *(const quaternion& q, const quaternion& r) {
    return quaternion(
        q.y * r.z - q.z * r.y + q.x * r.w + q.w * r.x,
        q.z * r.x - q.x * r.z + q.y * r.w + q.w * r.y,
        q.x * r.y - q.y * r.x + q.z * r.w + q.w * r.z,
        q.w * r.w - q.x * r.x - q.y * r.y - q.z * r.z
    );
}

quaternion operator /(const quaternion& q, const quaternion& r) {
    return q * r.inverse();
}

quaternion operator *(const quaternion& q, float scalar) {
    return quaternion(q.x * scalar, q.y * scalar, q.z * scalar, q.w * scalar);
}

quaternion operator *(float scalar, const quaternion& q) {
    return quaternion(scalar * q.x, scalar * q.y, scalar * q.z, scalar * q.w);
}

quaternion operator /(const quaternion& q, float scalar) {
    return quaternion(q.x / scalar, q.y / scalar, q.z / scalar, q.w / scalar);
}

quaternion operator /(float scalar, const quaternion& q) {
    return scalar * q.inverse();
}
