/***************************************************************************************************
 * @file  main.cpp
 * @brief Contains the main program of the project
 **************************************************************************************************/

#include <vulkan/vulkan.hpp>

#include <iostream>
#include <stdexcept>
#include "Application.hpp"
#include "core/EventHandler.hpp"
#include "core/Instance.hpp"
#include "core/Window.hpp"

int main() {
    try {
        /* Making Sure Singletons are Initialized First and in the Right Order */
        Window::get(); // Needs to go first because it initializes GLFW
        Instance::get();
        EventHandler::get();

        /* Running Application */
        Application app;
        app.run();
    } catch(const vk::SystemError& error) {
        std::cerr << "VULKAN ERROR : " << error.what() << '\n';
        return -1;
    } catch(const std::exception& exception) {
        std::cerr << "ERROR : " << exception.what() << '\n';
        return -1;
    }

    return 0;
}
