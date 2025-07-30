/***************************************************************************************************
 * @file  Instance.cpp
 * @brief Implementation of the Instance class
 **************************************************************************************************/

#include "core/Instance.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

Instance::Instance()
    : instance(nullptr), debug_messenger(nullptr) {
    constexpr vk::ApplicationInfo application_info{
        .pApplicationName = "Vulkan Engine",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "No Engine",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = vk::ApiVersion14
    };

    /* ---- Validation Layers ---- */
    const std::vector<const char*> validation_layers{
        "VK_LAYER_KHRONOS_validation"
    };

    std::vector<char const*> required_layers;
    required_layers.assign(validation_layers.begin(), validation_layers.end());

    std::vector<vk::LayerProperties> layer_properties = context.enumerateInstanceLayerProperties();
    for(const char* validation_layer : validation_layers) {
        bool was_layer_found = false;

        for(const vk::LayerProperties& layer_property : layer_properties) {
            if(strcmp(validation_layer, layer_property.layerName) == 0) {
                was_layer_found = true;
                break;
            }
        }

        if(!was_layer_found) {
            throw std::runtime_error("Required validation layer not supported: " + std::string(validation_layer));
        }
    }

    /* ---- Extensions ---- */
    uint32_t glfw_extensions_count = 0;
    const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extensions_count);

    std::vector<const char*> extensions(glfw_extensions, glfw_extensions + glfw_extensions_count);
    extensions.push_back(vk::EXTDebugUtilsExtensionName);

    std::vector<vk::ExtensionProperties> extension_properties = context.enumerateInstanceExtensionProperties();
    for(const char* extension : extensions) {
        bool was_extension_found = false;

        for(const vk::ExtensionProperties& extension_property : extension_properties) {
            if(strcmp(extension, extension_property.extensionName) == 0) {
                was_extension_found = true;
                break;
            }
        }

        if(!was_extension_found) {
            throw std::runtime_error("Required GLFW extension not supported: " + std::string(extension));
        }
    }

    /* ---- Create Instance ---- */
    vk::InstanceCreateInfo create_info{
        .pApplicationInfo = &application_info,
        .enabledLayerCount = static_cast<uint32_t>(required_layers.size()),
        .ppEnabledLayerNames = required_layers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
        .ppEnabledExtensionNames = extensions.data(),
    };

    instance = vk::raii::Instance(context, create_info);

    /* ---- Create Debug Messenger ---- */
    vk::DebugUtilsMessengerCreateInfoEXT debug_messenger_create_info{
        .messageSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose
                           | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
                           | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
        .messageType = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral
                       | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance
                       | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
        .pfnUserCallback = &debug_callback
    };

    debug_messenger = instance.createDebugUtilsMessengerEXT(debug_messenger_create_info);
}

vk::Bool32 Instance::debug_callback(vk::DebugUtilsMessageSeverityFlagBitsEXT severity,
                                    vk::DebugUtilsMessageTypeFlagsEXT type,
                                    const vk::DebugUtilsMessengerCallbackDataEXT* callback_data,
                                    void* /* user_data */) {
    std::cerr << "Vulkan Message:\n"
        "\tSeverity: " << vk::to_string(severity) << "\n"
        "\tType: " << vk::to_string(type) << "\n"
        "\tMessage: " << callback_data->pMessage << '\n';

    if(callback_data->objectCount > 0) {
        std::cerr << "\tObjects:\n";

        for(uint32_t i = 0 ; i < callback_data->objectCount ; ++i) {
            std::cerr << "\t\t" << callback_data->pObjects[i].pObjectName << '\n';
        }
    }

    return vk::False;
}
