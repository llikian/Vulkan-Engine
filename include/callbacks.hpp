/***************************************************************************************************
 * @file  callbacks.hpp
 * @brief Declaration of the callback functions for OpenGL
 **************************************************************************************************/

#pragma once

#include "Application.hpp"

extern Application application;

/**
 * @brief Callback for when the specified window is resized.
 * @param window The GLFW window.
 * @param width The new width of the window.
 * @param height The new height of the window.
 */
void windowSizeCallback(GLFWwindow* window, int width, int height);

/**
 * @brief Callback for when the framebuffer of the specified window is resized.
 * @param window The GLFW window.
 * @param width The new width of the frame buffer.
 * @param height The new height of the frame buffer.
 */
void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

/**
 * @brief Callback for when a key is pressed, released or held down.
 * @param window The GLFW window.
 * @param key The affected key. This is a platform-independent key code using GLFW_KEY_*.
 * @param scancode The system-specific scancode for the key.
 * @param action The action performed. Can be one of three values:\n
 * - GLFW_PRESS: The key was pressed.\n
 * - GLFW_RELEASE: The key was released.\n
 * - GLFW_REPEAT: The key was held down and is being repeatedly sent.
 * @param mods Bit field representing the modifier keys that were held down when the event occured.
 * It is a bitwise OR combination of the following flags:\n
 * - GLFW_MOD_SHIFT\n
 * - GLFW_MOD_CONTROL\n
 * - GLFW_MOD_ALT\n
 * - GLFW_MOD_SUPER\n
 */
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);