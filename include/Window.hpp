/***************************************************************************************************
 * @file  Window.hpp
 * @brief Declaration of the Window class
 **************************************************************************************************/

#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include "maths/vec2.hpp"

/**
 * @class Window
 * @brief Handles initializing GLFW, creates the window and initializes other libraries.
 */
class Window {
public:
    /**
     * @brief Initializes GLFW and other libraries.
     * @param name The name of the window.
     * @param windowUserPointer A pointer to
     */
    Window(const std::string& name, void* windowUserPointer);

    /**
     * @brief Destroys the GLFW window.
     */
    ~Window();

    /**
     * @brief Returns the GLFWwindow pointer.
     * @return The GLFW window.
     */
    operator GLFWwindow*();

    /**
     * @brief Updates the width and height of the window.
     * @param width The window's new width.
     * @param height The window's new height.
     */
    void updateSize(unsigned int width, unsigned int height);

    /**
     * @brief Getter for the width.
     * @return The window's width.
     */
    unsigned int getWidth() const;

    /**
     * @brief Getter for the height.
     * @return The window's height.
     */
    unsigned int getHeight() const;

    /**
     * @brief Returns the resolution of the window.
     * @return A vec2 containing the width as the x component and the height as the y component.
     */
    vec2 getResolution() const;

    /**
     * @brief Returns the window's size ratio.
     * @return The window's width divided by its height.
     */
    float getRatio() const;

private:
    GLFWwindow* window;  ///< The GLFW window.
    unsigned int width;  ///< The width of the window in pixels.
    unsigned int height; ///< The height of the window in pixels.
};