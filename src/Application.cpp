/***************************************************************************************************
 * @file  Application.cpp
 * @brief Implementation of the Application class
 **************************************************************************************************/

#include "Application.hpp"

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include "callbacks.hpp"

Application::Application()
    : window(nullptr), width(1600u), height(900u) {

    initWindow();
    initVulkan();
}

Application::~Application() {
    /**** Vulkan ****/
    if(IS_DEBUG) {
        destroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    }

    vkDestroyInstance(instance, nullptr);

    /**** GLFW ****/
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::run() {
    while(!glfwWindowShouldClose(window)) {
        handleEvents();
    }
}

void Application::setWindowSize(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
}

void Application::handleKeyCallback(int key, int action, int /* mods */) {
    if(action == GLFW_PRESS) {
        keys[key] = true;
    } else if(action == GLFW_RELEASE) {
        keys[key] = false;
    }
}

void Application::initWindow() {
    if(!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW.");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Tells Vulkan to not create an Opengl context.
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, "Vulkan Engine", nullptr, nullptr);
    if(!window) {
        throw std::runtime_error("Failed to create window.");
    }

    glfwSetWindowSizeCallback(window, windowSizeCallback);
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
}

void Application::initVulkan() {
    initInstance();
    setupDebugMessenger();
}

void Application::initInstance() {
    VkApplicationInfo info{};
    info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    info.pApplicationName = "Vulkan Engine";
    info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    info.pEngineName = "No Engine";
    info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    info.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo cInfo{};
    cInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    cInfo.pApplicationInfo = &info;
    cInfo.ppEnabledExtensionNames = glfwGetRequiredInstanceExtensions(&cInfo.enabledExtensionCount);

    if(IS_DEBUG) {
        checkValidationLayerSupport();
        cInfo.enabledLayerCount = validationLayers.size();
        cInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        cInfo.enabledLayerCount = 0;
    }

    std::vector<const char*> extensions = getRequiredExtensions();
    cInfo.enabledExtensionCount = extensions.size();
    cInfo.ppEnabledExtensionNames = extensions.data();

    if(vkCreateInstance(&cInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create instance.");
    }
}

void Application::checkValidationLayerSupport() {
    validationLayers.push_back("VK_LAYER_KHRONOS_validation");

    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    bool layerFound;
    for(const char* layer: validationLayers) {
        layerFound = false;

        for(const VkLayerProperties& layerProperties: availableLayers) {
            if(strcmp(layer, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if(!layerFound) {
            std::string error("Validation layer \"");
            error += layer;
            error += "\" was requested but not available.";
            throw std::runtime_error(error);
        }
    }
}

std::vector<const char*> Application::getRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if(IS_DEBUG) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

void Application::setupDebugMessenger() {
    if(!IS_DEBUG) {
        return;
    }

    VkDebugUtilsMessengerCreateInfoEXT cInfo{};
    cInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    cInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    cInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    cInfo.pfnUserCallback = debugCallback;

    if(createDebugUtilsMessengerEXT(instance, &cInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
        throw std::runtime_error("Failed to set up debug messenger.");
    }
}

void Application::handleEvents() {
    glfwPollEvents();
    handleKeyboardEvents();
}

void Application::handleKeyboardEvents() {
    for(const auto& [key, isKeyActive]: keys) {
        if(isKeyActive) {
            switch(key) {
                case GLFW_KEY_ESCAPE:
                    glfwSetWindowShouldClose(window, true);
                    break;
                default:
                    break;
            }
        }
    }
}
