/***************************************************************************************************
 * @file  callbacks.cpp
 * @brief Implementation of the callback functions for OpenGL
 **************************************************************************************************/

#include "callbacks.hpp"

void windowSizeCallback(GLFWwindow* /* window */, int width, int height) {
    application.setWindowSize(width, height);
}

void frameBufferSizeCallback(GLFWwindow* /* window */, int width, int height) {

}

void keyCallback(GLFWwindow* /* window */, int key, int /* scancode */, int action, int mods) {
    application.handleKeyCallback(key, action, mods);
}
