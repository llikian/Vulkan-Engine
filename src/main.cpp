/***************************************************************************************************
 * @file  main.cpp
 * @brief Contains the main program of the project
 **************************************************************************************************/

#include <iostream>
#include <stdexcept>

// Needs to be included before everything because it contains the GLFW_INCLUDE_VULKAN define
#include "Window.hpp"

#include "Application.hpp"

int main() {
    try {
        Application app;

        app.run();
    } catch(const std::exception& exception) {
        std::cerr << "ERROR : " << exception.what() << '\n';
        return -1;
    }

    return 0;
}
