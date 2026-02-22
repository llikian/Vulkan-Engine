/***************************************************************************************************
 * @file  Window.cpp
 * @brief Implementation of the Window class
 **************************************************************************************************/

#include "Window.hpp"

static void glfw_error_callback(int code, const char* message) {
    std::cerr << "GLFW Error '" << code << "' : " << message << '\n';
}

Window::Window() : window(nullptr) {
    /* ---- GLFW ---- */
    glfwSetErrorCallback(glfw_error_callback);

    if(!glfwInit()) { throw std::runtime_error("Failed to initialize GLFW."); }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window = glfwCreateWindow(1920, 1080, "OpenGL-Engine", nullptr, nullptr);
    if(window == nullptr) { throw std::runtime_error("Failed to create window."); }

    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwMaximizeWindow(window);
    glfwGetWindowSize(window, &width, &height);
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* Window::get_glfw_window() {
    return window;
}

int Window::get_width() {
    return width;
}

int Window::get_height() {
    return height;
}

float Window::get_aspect_ratio() {
    return static_cast<float>(width) / static_cast<float>(height);
}

void Window::update_size(int width, int height) {
    this->width = width;
    this->height = height;
}

vec2 Window::get_resolution() {
    return vec2(width, height);
}

bool Window::should_close() {
    return glfwWindowShouldClose(get_glfw_window());
}

void Window::swap_buffers() {
    glfwSwapBuffers(get_glfw_window());
}
