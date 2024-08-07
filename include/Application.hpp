/***************************************************************************************************
 * @file  Application.hpp
 * @brief Declaration of the Application class
 **************************************************************************************************/

#pragma once

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include <unordered_map>
#include <vector>

/**
 * @class Application
 * @brief The core of the engine.
 */
class Application {
public:
    /**** Constructor & Destructor ****/

    /**
     * @brief Constructor.
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
     * @brief Initializes GLFW and the GLFW window.
     */
    void initWindow();

    /**
     * @brief Initializes Vulkan.
     */
    void initVulkan();

    /**
     * @brief Creates the Vulkan Instance.
     */
    void initInstance();

    void checkValidationLayerSupport();

    std::vector<const char*> getRequiredExtensions();

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT severity,
        VkDebugUtilsMessageTypeFlagsEXT type,
        const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
        void* userDate);

    void setupDebugMessenger();

    static VkResult createDebugUtilsMessengerEXT(
        VkInstance instance,
        const VkDebugUtilsMessengerCreateInfoEXT* cInfo,
        const VkAllocationCallbacks* allocator,
        VkDebugUtilsMessengerEXT* debugMessenger);

    static void destroyDebugUtilsMessengerEXT(
        VkInstance instance,
        VkDebugUtilsMessengerEXT debugMessenger,
        const VkAllocationCallbacks* pAllocator);

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

    VkInstance instance; ///< Vulkan instance.
    VkDebugUtilsMessengerEXT debugMessenger; ///< Debug messenger.
    std::vector<const char*> validationLayers; ///< Active validation layers.

    std::unordered_map<int, bool> keys; ///< Map of the current state of keys.
};