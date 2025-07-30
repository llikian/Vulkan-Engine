/***************************************************************************************************
 * @file  Application.hpp
 * @brief Declaration of the Application class
 **************************************************************************************************/

#pragma once

#include "assets/Camera.hpp"

/**
 * @class Application
 * @brief
 */
class Application {
public:
    Application();
    void run();

private:
    Camera camera;
};