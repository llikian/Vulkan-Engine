/***************************************************************************************************
 * @file  Application.cpp
 * @brief Implementation of the Application class
 **************************************************************************************************/

#include "Application.hpp"

#include <stdexcept>
#include "callbacks.hpp"

Application::Application()
    : window(nullptr), width(1600u), height(900u) {

    initWindow();
}

Application::~Application() {
    /**** GLFW ****/
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::run() {
    while(!glfwWindowShouldClose(window)) {
        handleEvents();
    }
}

void Application::setWindowSize(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
}

void Application::handleKeyCallback(int key, int action, int /* mods */) {
    if(action == GLFW_PRESS) {
        keys[key] = true;
    } else if(action == GLFW_RELEASE) {
        keys[key] = false;
    }
}

void Application::initWindow() {
    if(!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW.");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Tells Vulkan to not create an Opengl context.
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, "Vulkan Engine", nullptr, nullptr);
    if(!window) {
        throw std::runtime_error("Failed to create window.");
    }

    glfwSetWindowSizeCallback(window, windowSizeCallback);
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
}

void Application::handleEvents() {
    glfwPollEvents();
    handleKeyboardEvents();
}

void Application::handleKeyboardEvents() {
    for(const auto& [key, isKeyActive]: keys) {
        if(isKeyActive) {
            switch(key) {
                case GLFW_KEY_ESCAPE:
                    glfwSetWindowShouldClose(window, true);
                    break;
                default:
                    break;
            }
        }
    }
}
