/***************************************************************************************************
 * @file  Random.hpp
 * @brief Declaration of the Random class
 **************************************************************************************************/

#pragma once

#include <random>
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

/**
 * @class Random
 * @brief Utility class providing static methods for generating random integers and real numbers.
 */
class Random {
public:
    /**
     * @brief Generate a random integer between min and max (inclusive).
     * @param min The minimum value of the output.
     * @param max The maximum value of the output.
     */
    template <typename Type>
    static Type integer(Type min, Type max) { return std::uniform_int_distribution<Type>(min, max)(generator); }

    /**
     * @brief Generate a random 2D integer vector with component-wise ranges.
     * @param min The minimum values of each component of the output.
     * @param max The maximum values of each component of the output.
     */
    template <typename Type>
    static Vector2<Type> integer2(Vector2<Type> min, Vector2<Type> max) {
        return Vector2(
            std::uniform_int_distribution<Type>(min.x, max.x)(generator),
            std::uniform_int_distribution<Type>(min.y, max.y)(generator)
        );
    }

    /**
     * @brief Generate a random 2D integer vector, using a uniform range for all components.
     * @param min The minimum value of each component of the output.
     * @param max The maximum value of each component of the output.
     */
    template <typename Type>
    static Vector2<Type> integer2(Type min, Type max) {
        std::uniform_int_distribution<Type> distribution(min, max);
        return Vector2(
            distribution(generator),
            distribution(generator)
        );
    }

    /**
     * @brief Generate a random 3D integer vector with component-wise ranges.
     * @param min The minimum values of each component of the output.
     * @param max The maximum values of each component of the output.
     */
    template <typename Type>
    static Vector3<Type> integer3(Vector3<Type> min, Vector3<Type> max) {
        return Vector3(
            std::uniform_int_distribution<Type>(min.x, max.x)(generator),
            std::uniform_int_distribution<Type>(min.y, max.y)(generator),
            std::uniform_int_distribution<Type>(min.z, max.z)(generator)
        );
    }

    /**
     * @brief Generate a random 3D integer vector, using a uniform range for all components.
     * @param min The minimum value of each component of the output.
     * @param max The maximum value of each component of the output.
     */
    template <typename Type>
    static Vector3<Type> integer3(Type min, Type max) {
        std::uniform_int_distribution<Type> distribution(min, max);
        return Vector3(
            distribution(generator),
            distribution(generator),
            distribution(generator)
        );
    }

    /**
     * @brief Generate a random 4D integer vector with component-wise ranges.
     * @param min The minimum values of each component of the output.
     * @param max The maximum values of each component of the output.
     */
    template <typename Type>
    static Vector4<Type> integer4(Vector4<Type> min, Vector4<Type> max) {
        return Vector4(
            std::uniform_int_distribution<Type>(min.x, max.x)(generator),
            std::uniform_int_distribution<Type>(min.y, max.y)(generator),
            std::uniform_int_distribution<Type>(min.z, max.z)(generator),
            std::uniform_int_distribution<Type>(min.w, max.w)(generator)
        );
    }

    /**
     * @brief Generate a random 4D integer vector, using a uniform range for all components.
     * @param min The minimum value of each component of the output.
     * @param max The maximum value of each component of the output.
     */
    template <typename Type>
    static Vector4<Type> integer4(Type min, Type max) {
        std::uniform_int_distribution<Type> distribution(min, max);
        return Vector4(
            distribution(generator),
            distribution(generator),
            distribution(generator),
            distribution(generator)
        );
    }

    /**
     * @brief Generate a random real number between min and max (inclusive).
     * @param min The minimum value of the output.
     * @param max The maximum value of the output.
     */
    template <typename Type>
    static Type real(Type min, Type max) { return std::uniform_real_distribution<Type>(min, max)(generator); }

    /**
     * @brief Generate a random 2D real vector with component-wise ranges.
     * @param min The minimum values of each component of the output.
     * @param max The maximum values of each component of the output.
     */
    template <typename Type>
    static Vector2<Type> real2(Vector2<Type> min, Vector2<Type> max) {
        return Vector2(
            std::uniform_real_distribution<Type>(min.x, max.x)(generator),
            std::uniform_real_distribution<Type>(min.y, max.y)(generator)
        );
    }

    /**
     * @brief Generate a random 2D real vector with a uniform range for all components.
     * @param min The minimum value of each component of the output.
     * @param max The maximum value of each component of the output.
     */
    template <typename Type>
    static Vector2<Type> real2(Type min, Type max) {
        std::uniform_real_distribution<Type> distribution(min, max);
        return Vector2(
            distribution(generator),
            distribution(generator)
        );
    }

    /**
     * @brief Generate a random 3D real vector with component-wise ranges.
     * @param min The minimum values of each component of the output.
     * @param max The maximum values of each component of the output.
     */
    template <typename Type>
    static Vector3<Type> real3(Vector3<Type> min, Vector3<Type> max) {
        return Vector3(
            std::uniform_real_distribution<Type>(min.x, max.x)(generator),
            std::uniform_real_distribution<Type>(min.y, max.y)(generator),
            std::uniform_real_distribution<Type>(min.z, max.z)(generator)
        );
    }

    /**
     * @brief Generate a random 3D real vector with a uniform range for all components.
     * @param min The minimum value of each component of the output.
     * @param max The maximum value of each component of the output.
     */
    template <typename Type>
    static Vector3<Type> real3(Type min, Type max) {
        std::uniform_real_distribution<Type> distribution(min, max);
        return Vector3(
            distribution(generator),
            distribution(generator),
            distribution(generator)
        );
    }

    /**
     * @brief Generate a random 4D real vector with component-wise ranges.
     * @param min The minimum values of each component of the output.
     * @param max The maximum values of each component of the output.
     */
    template <typename Type>
    static Vector4<Type> real4(Vector4<Type> min, Vector4<Type> max) {
        return Vector4(
            std::uniform_real_distribution<Type>(min.x, max.x)(generator),
            std::uniform_real_distribution<Type>(min.y, max.y)(generator),
            std::uniform_real_distribution<Type>(min.z, max.z)(generator),
            std::uniform_real_distribution<Type>(min.w, max.w)(generator)
        );
    }

    /**
     * @brief Generate a random 4D real vector with a uniform range for all components.
     * @param min The minimum value of each component of the output.
     * @param max The maximum value of each component of the output.
     */
    template <typename Type>
    static Vector4<Type> real4(Type min, Type max) {
        std::uniform_real_distribution<Type> distribution(min, max);
        return Vector4(
            distribution(generator),
            distribution(generator),
            distribution(generator),
            distribution(generator)
        );
    }

private:
    /// Random seed sourced from hardware entropy.
    inline static std::random_device seed {};

    /// Shared random engine used across all random generation methods.
    inline static std::default_random_engine generator { seed() };
};
