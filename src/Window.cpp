/***************************************************************************************************
 * @file  Window.cpp
 * @brief Implementation of the Window class
 **************************************************************************************************/

#include "Window.hpp"

#include <stdexcept>

Window::Window(const std::string& name, void* windowUserPointer)
    : window(nullptr) {
    /* ---- GLFW ---- */
    if(!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW.");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window = glfwCreateWindow(1, 1, name.c_str(), nullptr, nullptr);
    if(!window) {
        throw std::runtime_error("Failed to create window.");
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, windowUserPointer);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwMaximizeWindow(window);
    glfwGetWindowSize(window, reinterpret_cast<int*>(&width), reinterpret_cast<int*>(&height));
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

Window::operator GLFWwindow*() {
    return window;
}

void Window::updateSize(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
}

unsigned int Window::getWidth() const {
    return width;
}

unsigned int Window::getHeight() const {
    return height;
}

vec2 Window::getResolution() const {
    return vec2(static_cast<float>(width), static_cast<float>(height));
}

float Window::getRatio() const {
    return static_cast<float>(width) / static_cast<float>(height);
}
