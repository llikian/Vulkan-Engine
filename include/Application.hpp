/***************************************************************************************************
 * @file  Application.hpp
 * @brief Declaration of the Application class
 **************************************************************************************************/

#pragma once

#include "Window.hpp"

/**
 * @class Application
 * @brief
 */
class Application {
public:
    Application();
    void run();

private:
    Window window;
};

