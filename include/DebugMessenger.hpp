/***************************************************************************************************
 * @file  DebugMessenger.hpp
 * @brief Declaration of the DebugMessenger class
 **************************************************************************************************/

#pragma once

#include <vulkan/vulkan.hpp>

/**
 * @class DebugMessenger
 * @brief
 */
class DebugMessenger {
public:
    explicit DebugMessenger(const vk::Instance& instance);

    void create();
    void destroy() const;

    const VkDebugUtilsMessengerCreateInfoEXT* getCreateInfo() const;

private:
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT severity,
        VkDebugUtilsMessageTypeFlagsEXT type,
        const VkDebugUtilsMessengerCallbackDataEXT* data,
        void* userData);

    vk::DebugUtilsMessengerCreateInfoEXT createInfo;
    vk::DebugUtilsMessengerEXT debugMessenger;
    const vk::Instance& instance;
};
