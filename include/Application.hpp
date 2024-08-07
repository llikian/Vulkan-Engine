/***************************************************************************************************
 * @file  Application.hpp
 * @brief Declaration of the Application class
 **************************************************************************************************/

#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <unordered_map>

/**
 * @class Application
 * @brief The core of the engine.
 */
class Application {
public:
    /**** Constructor & Destructor ****/

    /**
     * @brief Sets the default value of all member variables and constants.
     */
    Application();

    /**
     * @brief Frees all allocated memory.
     */
    ~Application();

    /**** Public Methods ****/

    /**
     * @brief Contains the main loop.
     */
    void run();

    /**
     * @brief Sets the width and height of the GLFW window.
     * @param width The new width of the window.
     * @param height The new height of the window.
     */
    void setWindowSize(unsigned int width, unsigned int height);

    /**
     * @brief Handles what happens when a key is pressed.
     * @param key
     * @param action
     * @param mods
     */
    void handleKeyCallback(int key, int action, int mods);

private:
    /**** Private Methods ****/

    /**
     * @brief Initializes the GLFW window.
     */
    void initWindow();

    /**
     * @brief Polls and handles events with GLFW.
     */
    void handleEvents();

    /**
     * @brief Handles keyboard events.
     */
    void handleKeyboardEvents();

    /**** Variables & Constants ****/
    GLFWwindow* window;  ///< GLFW window.
    unsigned int width;  ///< The width of the window in pixels.
    unsigned int height; ///< The height of the window in pixels.

    std::unordered_map<int, bool> keys; ///< Map of the current state of keys.
};