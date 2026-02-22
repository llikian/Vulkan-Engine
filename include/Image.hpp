/***************************************************************************************************
 * @file  Image.hpp
 * @brief Declaration of the Image class
 **************************************************************************************************/

#pragma once

#include <filesystem>
#include "Array2D.hpp"
#include "vec.hpp"

/**
 * @class Image
 * @brief A 2D floating-point RGB image.
 *
 * Extends the Array<vec3> class and supports loading and writing images from and to files using the
 * stb_image and stb_image_write libraries.
 *
 * Pixel values are stored as linear RGB values in the range [0 ; 1].
 */
class Image : public Array2D<vec3> {
public:
    using Array2D::Array2D; // Inheriting constructors.

    /**
     * @brief Construct an image by loading it from a file.
     * @param path The path to the input image file.
     * @param flip_vertically Whether to flip the image vertically on load.
     */
    explicit Image(const std::filesystem::path& path, bool flip_vertically = false);

    /**
     * @brief Loads an image from a file.
     * @param path The path to the input image file.
     * @param flip_vertically Whether to flip the image vertically on load.
     */
    void read(const std::filesystem::path& path, bool flip_vertically = false);

    /**
     * @brief Writes an image to a file.
     * @param path The path to the output image file.
     */
    void write(const std::filesystem::path& path);

private:
    bool is_flipped; ///< Whether the image was flipped on load (and thus needs to be flipped on write).
};
