/***************************************************************************************************
 * @file  DebugMessenger.cpp
 * @brief Implementation of the DebugMessenger class
 **************************************************************************************************/

#include "DebugMessenger.hpp"

#include <iostream>

VkResult vkCreateDebugUtilsMessengerEXT(VkInstance instance,
                                        const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                        const VkAllocationCallbacks* pAllocator,
                                        VkDebugUtilsMessengerEXT* pMessenger) {
    static auto func = vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if(func == nullptr) { return VK_ERROR_EXTENSION_NOT_PRESENT; }
    return reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(func)(instance, pCreateInfo, pAllocator, pMessenger);
}

void vkDestroyDebugUtilsMessengerEXT(VkInstance instance,
                                     VkDebugUtilsMessengerEXT messenger,
                                     const VkAllocationCallbacks* pAllocator) {
    static auto func = vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if(func != nullptr) {
        reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(func)(instance, messenger, pAllocator);
    }
}

DebugMessenger::DebugMessenger(const vk::Instance& instance)
    : instance(instance) {
    createInfo.sType = vk::StructureType::eDebugUtilsMessengerCreateInfoEXT;
    createInfo.messageSeverity =
        vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
        | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
        // | vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose
        // | vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo
    ;
    createInfo.messageType =
        vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral
        | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation
        | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance
    ;
    createInfo.pfnUserCallback = debugCallback;
    createInfo.pUserData = nullptr;
}

void DebugMessenger::create() {
    debugMessenger = instance.createDebugUtilsMessengerEXT(createInfo);
}

void DebugMessenger::destroy() const {
    vkDestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
}

const VkDebugUtilsMessengerCreateInfoEXT* DebugMessenger::getCreateInfo() const {
    return reinterpret_cast<const VkDebugUtilsMessengerCreateInfoEXT*>(&createInfo);
}

VkBool32 DebugMessenger::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
                                       [[maybe_unused]] VkDebugUtilsMessageTypeFlagsEXT type,
                                       const VkDebugUtilsMessengerCallbackDataEXT* data,
                                       [[maybe_unused]] void* userData) {

    switch(static_cast<vk::DebugUtilsMessageSeverityFlagBitsEXT>(severity)) {
        case vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose:
            std::cout << "\033[38;5;123m[Verbose] ";
            break;
        case vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo:
            std::cout << "\033[38;5;76m[Info] ";
            break;
        case vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning:
            std::cout << "\033[38;5;208m[Warning] ";
            break;
        case vk::DebugUtilsMessageSeverityFlagBitsEXT::eError:
            std::cout << "\033[38;5;160m[Error] ";
            break;
    }

    std::cout << data->pMessage << "\033[0m\n";

    return VK_FALSE;
}
