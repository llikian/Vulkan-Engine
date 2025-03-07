/***************************************************************************************************
 * @file  Instance.hpp
 * @brief Declaration of the Instance class
 **************************************************************************************************/

#pragma once

#include <DebugMessenger.hpp>
#include <vulkan/vulkan.hpp>

/**
 * @class Instance
 * @brief
 */
class Instance {
public:
    Instance();
    explicit Instance(const VkDebugUtilsMessengerCreateInfoEXT* debugMessengerCreateInfo);
    ~Instance();

    vk::Instance& get();
    const vk::Instance& get() const;
    operator vk::Instance&();
    operator const vk::Instance&() const;

private:
    static void getRequiredExtensions(std::vector<const char*>& extensions);

    vk::Instance instance;

#ifdef DEBUG
    void checkValidationLayerSupport() const;

    DebugMessenger debugMessenger;
    std::vector<const char*> validationLayers;
#endif
};