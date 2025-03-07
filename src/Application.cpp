/***************************************************************************************************
 * @file  Application.cpp
 * @brief Implementation of the Application class
 **************************************************************************************************/

#include "Application.hpp"

Application::Application()
    : window("Vulkan Engine", this) { }

Application::~Application() { }

void Application::run() {
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwSetWindowShouldClose(window, true); // TODO : Remove this
    }
}
