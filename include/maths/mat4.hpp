/***************************************************************************************************
 * @file  mat4.hpp
 * @brief Declaration of the mat4 struct
 **************************************************************************************************/

#pragma once

#include <ostream>
#include "vec3.hpp"

/**
 * @struct mat4
 * @brief Represents a 4 by 4 matrix.
 */
struct mat4 {
public:
    /**
     * @brief Constructs a matrix with all components equal to 0.
     */
    mat4();

    /**
     * @brief Constructs a matrix with a specific value for each component.
     * @param v00, v01, v02, v03 The values of the components of the first row.
     * @param v10, v11, v12, v13 The values of the components of the second row.
     * @param v20, v21, v22, v23 The values of the components of the third row.
     * @param v30, v31, v32, v33 The values of the components of the fourth row.
     */
    mat4(float v00, float v01, float v02, float v03,
         float v10, float v11, float v12, float v13,
         float v20, float v21, float v22, float v23,
         float v30, float v31, float v32, float v33);

    /**
     * @brief Constructs a matrix with a specific value for each component of the 3 first columns
     * and rows. The fourth column and row are the same as the identity matrix.
     * @param v00, v01, v02 The values of the first three components of the first row.
     * @param v10, v11, v12 The values of the first three components of the second row.
     * @param v20, v21, v22 The values of the first three components of the third row.
     */
    mat4(float v00, float v01, float v02,
         float v10, float v11, float v12,
         float v20, float v21, float v22);

    /**
     * @brief Constructs a matrix which is the identity matrix multiplied by a scalar.
     * Each value of the diagonal is equal to the scalar and the rest is zeros.
     * @param scalar The value for the components on the diagonal.
     */
    mat4(float scalar);

    /**
     * @brief Accesses an element of the matrix.
     * @param row The row's index.
     * @param column The column's index.
     * @return A reference to the element.
     */
    float& operator ()(int row, int column);

    /**
     * @brief Accesses an element of the matrix.
     * @param row The row's index.
     * @param column The column's index.
     * @return A const reference to the element.
     */
    const float& operator ()(int row, int column) const;

    /**
     * @brief Applies a transform that scales by the same factor in all 3 directions.
     * @param factor The scaling factor.
     * @return A refence to the matrix.
     */
    mat4& scale(float factor);

    /**
     * @brief Applies a transform that scales by a specific factor in each direction.
     * @param x The scaling factor in the x direction.
     * @param y The scaling factor in the y direction.
     * @param z The scaling factor in the z direction.
     * @return A refence to the matrix.
     */
    mat4& scale(float x, float y, float z);

    /**
     * @brief Applies a transformthat scales by a specific factor in each direction.
     * @param factors The scaling factors.
     * @return A reference to the matrix.
     */
    mat4& scale(const vec3& factors);

    /**
     * @brief Applies a transform that only scales in the x direction.
     * @param factor The scaling factor.
     * @return A reference to the matrix.
     */
    mat4& scaleX(float factor);

    /**
     * @brief Applies a transform that only scales in the y direction.
     * @param factor The scaling factor.
     * @return A reference to the matrix.
     */
    mat4& scaleY(float factor);

    /**
     * @brief Applies a transform that only scales in the z direction.
     * @param factor The scaling factor.
     * @return A reference to the matrix.
     */
    mat4& scaleZ(float factor);

    /**
     * @brief Applies a transformthat displaces by a specific vector.
     * @param factor The scaling factor.
     * @return A reference to the matrix.
     */
    mat4& translate(const Vector& vector);

    /**
     * @brief Applies a transform that displaces by a specific amount in each direction.
     * @param x The displacement in the x direction.
     * @param y The displacement in the y direction.
     * @param z The displacement in the z direction.
     * @return A reference to the matrix.
     */
    mat4& translate(float x, float y, float z);

    /**
     * @brief Applies a transform that only displaces in the x direction.
     * @param scalar The displacement amount.
     * @return A reference to the matrix.
     */
    mat4& translateX(float scalar);

    /**
     * @brief Applies a transform that only displaces in the y direction.
     * @param scalar The displacement amount.
     * @return A reference to the matrix.
     */
    mat4& translateY(float scalar);

    /**
     * @brief Applies a transform that only displaces in the z direction.
     * @param scalar The displacement amount.
     * @return A reference to the matrix.
     */
    mat4& translateZ(float scalar);

    /**
     * @brief Applies a transform that rotates around an axis by a certain angle.
     * @param angle The rotation angle in degrees.
     * @param axis The rotation axis.
     * @return A reference to the matrix.
     */
    mat4& rotate(float angle, const Vector& axis);

    /**
     * @brief Applies a transform that rotates around the x axis by a certain angle.
     * @param angle The rotation angle in degrees.
     * @return A reference to the matrix.
     */
    mat4& rotateX(float angle);

    /**
     * @brief Applies a transform that rotates around the y axis by a certain angle.
     * @param angle The rotation angle in degrees.
     * @return A reference to the matrix.
     */
    mat4& rotateY(float angle);

    /**
     * @brief Applies a transform that rotates around the z axis by a certain angle.
     * @param angle The rotation angle in degrees.
     * @return A reference to the matrix.
     */
    mat4& rotateZ(float angle);

private:
    float values[4][4]; ///< The values of the matrix.
};

/**
 * @brief Writes the components of the given matrix to the output stream in the format:\n
 * ( v00 ; v01 ; v02 ; v03 )\n
 * ( v10 ; v11 ; v12 ; v13 )\n
 * ( v20 ; v21 ; v22 ; v23 )\n
 * ( v30 ; v31 ; v32 ; v33 )\n
 * @param stream The output stream to write to.
 * @param mat The matrix to write to the stream.
 * @return A reference to the output stream after writing the matrix.
 */
std::ostream& operator <<(std::ostream& stream, const mat4& mat);

/**
 * @brief Adds the second matrix's components to the first's.
 * @param left The left operand. Will store the result.
 * @param right The right operand.
 */
void operator +=(mat4& left, const mat4& right);

/**
 * @brief Subtracts the second matrix's components from the first's.
 * @param left The left operand. Will store the result.
 * @param right The right operand.
 */
void operator -=(mat4& left, const mat4& right);

/**
 * @brief Adds a scalar to all of a matrix's components.
 * @param mat The matrix.
 * @param scalar The scalar.
 */
void operator +=(mat4& mat, float scalar);

/**
 * @brief Subtracts all of a matrix's components by a scalar.
 * @param mat The matrix.
 * @param scalar The scalar.
 */
void operator -=(mat4& mat, float scalar);

/**
 * @brief Multiplies a scalar to all of a matrix's components.
 * @param mat The matrix.
 * @param scalar The scalar.
 */
void operator *=(mat4& mat, float scalar);

/**
 * @brief Divides all of a matrix's components by a scalar.
 * @param mat The matrix.
 * @param scalar The scalar.
 */
void operator /=(mat4& mat, float scalar);

/** @brief Adds a matrix's components to another's.
 *  @param left The left operand.
 *  @param right The right operand.
 *  @return The component-wise sum of the two matrix.
 */
mat4 operator +(const mat4& left, const mat4& right);

/** @brief Subtracts a matrix's components by another's.
 *  @param left The left operand.
 *  @param right The right operand.
 *  @return The component-wise subtraction of the first matrix by the second.
 */
mat4 operator -(const mat4& left, const mat4& right);

/** @brief Multiplies a matrix by another.
 *  @param left The left operand.
 *  @param right The right operand.
 *  @return The product of the two matrix.
 */
mat4 operator *(const mat4& left, const mat4& right);

/** @brief Adds a scalar to each of a matrix's components.
 *  @param mat The matrix.
 *  @param scalar The scalar.
 *  @return The component-wise sum of a matrix by a scalar.
 */
mat4 operator +(const mat4& mat, float scalar);

/** @brief Subtracts each of a matrix's components by a scalar.
 *  @param mat The matrix.
 *  @param scalar The scalar.
 *  @return The component-wise subtraction of a matrix by a scalar.
 */
mat4 operator -(const mat4& mat, float scalar);

/** @brief Multiplies each of a matrix's components by a scalar.
 *  @param mat The matrix.
 *  @param scalar The scalar.
 *  @return The component-wise product of a matrix by a scalar.
 */
mat4 operator *(const mat4& mat, float scalar);

/** @brief Multiplies each of a matrix's components by a scalar.
 *  @param scalar The scalar.
 *  @param mat The matrix.
 *  @return The component-wise product of a matrix by a scalar.
 */
mat4 operator *(float scalar, const mat4& mat);

/** @brief Divides each of a matrix's components by a scalar.
 *  @param mat The matrix.
 *  @param scalar The scalar.
 *  @return The component-wise division of a matrix by a scalar.
 */
mat4 operator /(const mat4& mat, float scalar);