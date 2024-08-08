/***************************************************************************************************
 * @file  vulkan_functions.cpp
 * @brief
 **************************************************************************************************/

#include "vulkan_functions.hpp"

#include <iostream>

VkBool32 debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT /* severity */,
                       VkDebugUtilsMessageTypeFlagsEXT /* type */,
                       const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
                       void* /* userData */) {

    std::cerr << "[DEBUG] " << callbackData->pMessage << '\n';

    return VK_FALSE;
}

VkResult createDebugUtilsMessengerEXT(VkInstance instance,
                                      const VkDebugUtilsMessengerCreateInfoEXT* cInfo,
                                      const VkAllocationCallbacks* allocator,
                                      VkDebugUtilsMessengerEXT* debugMessenger) {

    static auto func = (PFN_vkCreateDebugUtilsMessengerEXT)
        vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

    if(func != nullptr) {
        return func(instance, cInfo, allocator, debugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void destroyDebugUtilsMessengerEXT(VkInstance instance,
                                   VkDebugUtilsMessengerEXT debugMessenger,
                                   const VkAllocationCallbacks* pAllocator) {

    static auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)
        vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

    if(func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}