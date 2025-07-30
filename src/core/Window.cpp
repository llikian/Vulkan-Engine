/***************************************************************************************************
 * @file  Window.cpp
 * @brief Implementation of the Window class
 **************************************************************************************************/

#include "core/Window.hpp"

static void glfw_error_callback(int code, const char* message) {
    std::cerr << "GLFW Error '" << code << "' : " << message << '\n';
}

Window::Window()
    : window(nullptr) {
    glfwSetErrorCallback(glfw_error_callback);

    if(!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW.");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1920, 1080, "Vulkan Engine", nullptr, nullptr);
    if(window == nullptr) { throw std::runtime_error("Failed to create window."); }

    glfwMakeContextCurrent(window);

    glfwMaximizeWindow(window);
    glfwGetWindowSize(window, &width, &height);
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* Window::get_glfw() {
    return get().window;
}

int Window::get_width() {
    return get().width;
}

int Window::get_height() {
    return get().height;
}

float Window::get_aspect_ratio() {
    const Window& window = get();
    return static_cast<float>(window.width) / static_cast<float>(window.height);
}

void Window::update_size(int width, int height) {
    Window& window = get();
    window.width = width;
    window.height = height;
}

vec2 Window::get_resolution() {
    Window& window = get();
    return vec2(window.width, window.height);
}

bool Window::should_close() {
    return glfwWindowShouldClose(get_glfw());
}

void Window::swap_buffers() {
    glfwSwapBuffers(get_glfw());
}
