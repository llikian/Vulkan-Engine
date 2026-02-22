/***************************************************************************************************
 * @file  Image.cpp
 * @brief Implementation of the Image class
 **************************************************************************************************/

#include "Image.hpp"

#include <vector>
#include "stb_image.h"
#include "stb_image_write.h"

Image::Image(const std::filesystem::path& path, bool flip_vertically) {
    read(path, flip_vertically);
}

void Image::read(const std::filesystem::path& path, bool flip_vertically) {
    is_flipped = flip_vertically;
    stbi_set_flip_vertically_on_load(flip_vertically);

    int w, h, c;
    const unsigned char* image_data = stbi_load(path.string().c_str(), &w, &h, &c, 3);
    if(image_data == nullptr) { throw std::runtime_error("Couldn't load image '" + path.string() + '\''); }

    resize(h, w);
    for(std::size_t i = 0 ; i < height ; ++i) {
        for(std::size_t j = 0 ; j < width ; ++j) {
            std::size_t index = (i * width + j) * 3;

            data[i][j] = vec3(
                image_data[index] / 255.0f,
                image_data[index + 1] / 255.0f,
                image_data[index + 2] / 255.0f
            );
        }
    }
}

void Image::write(const std::filesystem::path& path) {
    std::vector<uint8_t> normalized_data;
    normalized_data.reserve(height * width * 3);

    for(std::size_t i = 0 ; i < height ; ++i) {
        for(std::size_t j = 0 ; j < width ; ++j) {
            const auto& [r, g, b] = data[i][j];

            normalized_data.push_back(std::clamp(255.0f * r, 0.0f, 255.0f));
            normalized_data.push_back(std::clamp(255.0f * g, 0.0f, 255.0f));
            normalized_data.push_back(std::clamp(255.0f * b, 0.0f, 255.0f));
        }
    }

    stbi_flip_vertically_on_write(is_flipped);
    stbi_write_png(path.string().c_str(), width, height, 3, normalized_data.data(), width * 3);
}
