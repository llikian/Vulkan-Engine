/***************************************************************************************************
 * @file  Instance.cpp
 * @brief Implementation of the Instance class
 **************************************************************************************************/

#include "Instance.hpp"

#include <iostream>
#include <GLFW/glfw3.h>

#include "types.hpp"

Instance::Instance()
#ifdef DEBUG
    : debugMessenger(instance)
#endif
{
    vk::ApplicationInfo appInfo;
    appInfo.sType = vk::StructureType::eApplicationInfo;
    appInfo.pApplicationName = "Vulkan Engine";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    vk::InstanceCreateInfo createInfo;
    createInfo.sType = vk::StructureType::eInstanceCreateInfo;
    createInfo.pApplicationInfo = &appInfo;

    std::vector<const char*> requiredExtensions;
    getRequiredExtensions(requiredExtensions);
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();
    createInfo.enabledExtensionCount = requiredExtensions.size();

#ifdef DEBUG
    validationLayers.push_back("VK_LAYER_KHRONOS_validation");
    checkValidationLayerSupport();
    createInfo.enabledLayerCount = validationLayers.size();
    createInfo.ppEnabledLayerNames = validationLayers.data();
    createInfo.pNext = debugMessenger.getCreateInfo();
#else
    createInfo.enabledLayerCount = 0;
    createInfo.ppEnabledLayerNames = nullptr;
    createInfo.pNext = nullptr;
#endif

    uint32 extensionCount = 0;
    if(vk::enumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr) != vk::Result::eSuccess) {
        throw std::runtime_error("Couldn't retrieve instance extension count.");
    }

    std::vector<vk::ExtensionProperties> extensions(extensionCount);
    if(vk::enumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data()) != vk::Result::eSuccess) {
        throw std::runtime_error("Couldn't retrieve instance extension properties");
    }

    std::cout << "Available extensions:\n";
    for(const vk::ExtensionProperties& extension : extensions) {
        std::cout << '\t' << extension.extensionName << '\n';
    }

    if(vk::createInstance(&createInfo, nullptr, &instance) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to create instance.");
    }

#ifdef DEBUG
    debugMessenger.create();
#endif
}

Instance::~Instance() {
#ifdef DEBUG
    debugMessenger.destroy();
#endif

    instance.destroy();
}

vk::Instance& Instance::get() {
    return instance;
}

const vk::Instance& Instance::get() const {
    return instance;
}

Instance::operator vk::Instance&() {
    return instance;
}

Instance::operator const vk::Instance&() const {
    return instance;
}

void Instance::getRequiredExtensions(std::vector<const char*>& extensions) {
    uint32 glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    for(unsigned int i = 0 ; i < glfwExtensionCount ; ++i) {
        extensions.push_back(glfwExtensions[i]);
    }

#ifdef DEBUG
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif
}

#ifdef DEBUG
void Instance::checkValidationLayerSupport() const {
    uint32 layerCount = 0;
    if(vk::enumerateInstanceLayerProperties(&layerCount, nullptr) != vk::Result::eSuccess) {
        throw std::runtime_error("Couldn't retrieve instance layer count.");
    }

    std::vector<vk::LayerProperties> layers(layerCount);
    if(vk::enumerateInstanceLayerProperties(&layerCount, layers.data()) != vk::Result::eSuccess) {
        throw std::runtime_error("Couldn't retrieve instance layer properties.");
    }

    for(std::string layerName : validationLayers) {
        bool found = false;

        for(const vk::LayerProperties& layer : layers) {
            if(layerName == layer.layerName) {
                found = true;
                break;
            }
        }

        if(!found) {
            throw std::runtime_error("Couldn't find validation layer: " + layerName + '.');
        }
    }
}
#endif
