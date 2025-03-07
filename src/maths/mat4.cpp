/***************************************************************************************************
 * @file  mat4.cpp
 * @brief Implementation of the mat4 struct
 **************************************************************************************************/

#include "maths/mat4.hpp"

#include <cmath>
#include "maths/geometry.hpp"
#include "maths/trigonometry.hpp"

mat4::mat4()
    : values{{0.0f, 0.0f, 0.0f, 0.0f},
             {0.0f, 0.0f, 0.0f, 0.0f},
             {0.0f, 0.0f, 0.0f, 0.0f},
             {0.0f, 0.0f, 0.0f, 0.0f}} { }

mat4::mat4(float v00, float v01, float v02, float v03,
           float v10, float v11, float v12, float v13,
           float v20, float v21, float v22, float v23,
           float v30, float v31, float v32, float v33)
    : values{{v00, v10, v20, v30},
             {v01, v11, v21, v31},
             {v02, v12, v22, v32},
             {v03, v13, v23, v33}} { }

mat4::mat4(float v00, float v01, float v02,
           float v10, float v11, float v12,
           float v20, float v21, float v22)
    : values{{v00,  v10,  v20,  0.0f},
             {v01,  v11,  v21,  0.0f},
             {v02,  v12,  v22,  0.0f},
             {0.0f, 0.0f, 0.0f, 1.0f}} { }

mat4::mat4(float scalar)
    : values{{scalar, 0.0f,   0.0f,   0.0f},
             {0.0f,   scalar, 0.0f,   0.0f},
             {0.0f,   0.0f,   scalar, 0.0f},
             {0.0f,   0.0f,   0.0f,   scalar}} { }

float& mat4::operator ()(int row, int column) {
    return values[column][row];
}

const float& mat4::operator ()(int row, int column) const {
    return values[column][row];
}

mat4& mat4::scale(float factor) {
    for(int i = 0 ; i < 3 ; ++i) {
        values[0][i] *= factor;
        values[1][i] *= factor;
        values[2][i] *= factor;
    }

    return *this;
}

mat4& mat4::scale(float x, float y, float z) {
    for(int i = 0 ; i < 3 ; ++i) {
        values[0][i] *= x;
        values[1][i] *= y;
        values[2][i] *= z;
    }

    return *this;
}

mat4& mat4::scale(const vec3& factors) {
    for(int i = 0 ; i < 3 ; ++i) {
        values[0][i] *= factors.x;
        values[1][i] *= factors.y;
        values[2][i] *= factors.z;
    }

    return *this;
}

mat4& mat4::scaleX(float factor) {
    for(int i = 0 ; i < 3 ; ++i) {
        values[0][i] *= factor;
    }

    return *this;
}

mat4& mat4::scaleY(float factor) {
    for(int i = 0 ; i < 3 ; ++i) {
        values[1][i] *= factor;
    }

    return *this;
}

mat4& mat4::scaleZ(float factor) {
    for(int i = 0 ; i < 3 ; ++i) {
        values[2][i] *= factor;
    }

    return *this;
}

mat4& mat4::translate(const Vector& vector) {
    values[3][0] += values[0][0] * vector.x + values[1][0] * vector.y + values[2][0] * vector.z;
    values[3][1] += values[0][1] * vector.x + values[1][1] * vector.y + values[2][1] * vector.z;
    values[3][2] += values[0][2] * vector.x + values[1][2] * vector.y + values[2][2] * vector.z;
    values[3][3] += values[0][3] * vector.x + values[1][3] * vector.y + values[2][3] * vector.z;

    return *this;
}

mat4& mat4::translate(float x, float y, float z) {
    values[3][0] += values[0][0] * x + values[1][0] * y + values[2][0] * z;
    values[3][1] += values[0][1] * x + values[1][1] * y + values[2][1] * z;
    values[3][2] += values[0][2] * x + values[1][2] * y + values[2][2] * z;
    values[3][3] += values[0][3] * x + values[1][3] * y + values[2][3] * z;

    return *this;
}

mat4& mat4::translateX(float scalar) {
    values[3][0] += values[0][0] * scalar;
    values[3][1] += values[0][1] * scalar;
    values[3][2] += values[0][2] * scalar;
    values[3][3] += values[0][3] * scalar;

    return *this;
}

mat4& mat4::translateY(float scalar) {
    values[3][0] += values[1][0] * scalar;
    values[3][1] += values[1][1] * scalar;
    values[3][2] += values[1][2] * scalar;
    values[3][3] += values[1][3] * scalar;

    return *this;
}

mat4& mat4::translateZ(float scalar) {
    values[3][0] += values[2][0] * scalar;
    values[3][1] += values[2][1] * scalar;
    values[3][2] += values[2][2] * scalar;
    values[3][3] += values[2][3] * scalar;

    return *this;
}

mat4& mat4::rotate(float angle, const Vector& axis) {
    angle = radians(angle);

    float cosine = cosf(angle);
    float sine = sinf(angle);

    Vector nAxis = axis;
    if(nAxis != Vector(0.0f, 0.0f, 0.0f)) {
        nAxis = normalize(axis);
    }

    Vector temp = (1.0f - cosine) * nAxis;

    float upperLeft3x3[3][3]{
        {values[0][0], values[0][1], values[0][2]},
        {values[1][0], values[1][1], values[1][2]},
        {values[2][0], values[2][1], values[2][2]}
    };

    float rotation[3][3]{
        {cosine + temp.x * nAxis.x,         temp.x * nAxis.y + sine * nAxis.z, temp.x * nAxis.z - sine * nAxis.y},
        {temp.y * nAxis.x - sine * nAxis.z, cosine + temp.y * nAxis.y,         temp.y * nAxis.z + sine * nAxis.x},
        {temp.x * nAxis.x + sine * nAxis.y, temp.x * nAxis.y - sine * nAxis.x, cosine + temp.x * nAxis.z}
    };

    for(int i = 0 ; i < 3 ; ++i) {
        for(int j = 0 ; j < 3 ; ++j) {
            values[j][i] = 0.0f;

            for(int k = 0 ; k < 3 ; ++k) {
                values[j][i] += upperLeft3x3[k][i] * rotation[j][k];
            }
        }
    }

    return *this;
}

mat4& mat4::rotateX(float angle) {
    angle = radians(angle);

    const float cosine = cosf(angle);
    const float sine = sinf(angle);

    float column[4]{values[1][0], values[1][1], values[1][2], values[1][3]};

    values[1][0] = cosine * column[0] + sine * values[2][0];
    values[1][1] = cosine * column[1] + sine * values[2][1];
    values[1][2] = cosine * column[2] + sine * values[2][2];
    values[1][3] = cosine * column[3] + sine * values[2][3];

    values[2][0] = -sine * column[0] + cosine * values[2][0];
    values[2][1] = -sine * column[1] + cosine * values[2][1];
    values[2][2] = -sine * column[2] + cosine * values[2][2];
    values[2][3] = -sine * column[3] + cosine * values[2][3];

    return *this;
}

mat4& mat4::rotateY(float angle) {
    angle = radians(angle);

    const float cosine = cosf(angle);
    const float sine = sinf(angle);

    float column[4]{values[0][0], values[0][1], values[0][2], values[0][3]};

    values[0][0] = cosine * column[0] - sine * values[2][0];
    values[0][1] = cosine * column[1] - sine * values[2][1];
    values[0][2] = cosine * column[2] - sine * values[2][2];
    values[0][3] = cosine * column[3] - sine * values[2][3];

    values[2][0] = sine * column[0] + cosine * values[2][0];
    values[2][1] = sine * column[1] + cosine * values[2][1];
    values[2][2] = sine * column[2] + cosine * values[2][2];
    values[2][3] = sine * column[3] + cosine * values[2][3];

    return *this;
}

mat4& mat4::rotateZ(float angle) {
    angle = radians(angle);

    const float cosine = cosf(angle);
    const float sine = sinf(angle);

    float column[4]{values[0][0], values[0][1], values[0][2], values[0][3]};

    values[0][0] = cosine * column[0] + sine * values[1][0];
    values[0][1] = cosine * column[1] + sine * values[1][1];
    values[0][2] = cosine * column[2] + sine * values[1][2];
    values[0][3] = cosine * column[3] + sine * values[1][3];

    values[1][0] = -sine * column[0] + cosine * values[1][0];
    values[1][1] = -sine * column[1] + cosine * values[1][1];
    values[1][2] = -sine * column[2] + cosine * values[1][2];
    values[1][3] = -sine * column[3] + cosine * values[1][3];

    return *this;
}

std::ostream& operator <<(std::ostream& stream, const mat4& mat) {
    for(int i = 0 ; i < 4 ; ++i) {
        stream << "( ";

        for(int j = 0 ; j < 3 ; ++j) {
            stream << ' ' << mat(i, j) << " ; ";
        }

        stream << mat(i, 3) << " )\n";
    }
    return stream;
}

void operator +=(mat4& left, const mat4& right) {
    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            left(i, j) += right(i, j);
        }
    }
}

void operator -=(mat4& left, const mat4& right) {
    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            left(i, j) -= right(i, j);
        }
    }
}

void operator +=(mat4& mat, float scalar) {
    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            mat(i, j) += scalar;
        }
    }
}

void operator -=(mat4& mat, float scalar) {
    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            mat(i, j) -= scalar;
        }
    }
}

void operator *=(mat4& mat, float scalar) {
    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            mat(i, j) *= scalar;
        }
    }
}

void operator /=(mat4& mat, float scalar) {
    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            mat(i, j) /= scalar;
        }
    }
}

mat4 operator +(const mat4& left, const mat4& right) {
    mat4 result;

    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            result(i, j) = left(i, j) + right(i, j);
        }
    }

    return result;
}

mat4 operator -(const mat4& left, const mat4& right) {
    mat4 result;

    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            result(i, j) = left(i, j) - right(i, j);
        }
    }

    return result;
}

mat4 operator *(const mat4& left, const mat4& right) {
    mat4 result;

    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            for(int k = 0 ; k < 4 ; ++k) {
                result(i, j) += left(i, k) * right(k, j);
            }
        }
    }

    return result;
}

mat4 operator +(const mat4& mat, float scalar) {
    mat4 result;

    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            result(i, j) = mat(i, j) + scalar;
        }
    }

    return result;
}

mat4 operator -(const mat4& mat, float scalar) {
    mat4 result;

    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            result(i, j) = mat(i, j) - scalar;
        }
    }

    return result;
}

mat4 operator *(const mat4& mat, float scalar) {
    mat4 result;

    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            result(i, j) = mat(i, j) * scalar;
        }
    }

    return result;
}

mat4 operator *(float scalar, const mat4& mat) {
    mat4 result;

    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            result(i, j) = scalar * mat(i, j);
        }
    }

    return result;
}

mat4 operator /(const mat4& mat, float scalar) {
    mat4 result;

    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            result(i, j) = mat(i, j) / scalar;
        }
    }

    return result;
}
