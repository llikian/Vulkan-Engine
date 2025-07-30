/***************************************************************************************************
 * @file  Instance.hpp
 * @brief Declaration of the Instance class
 **************************************************************************************************/

#pragma once

#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>

/**
 * @class Instance
 * @brief
 */
class Instance {
public:
    Instance();

    Instance(const Instance&) = delete;            ///< Deleted copy constructor.
    Instance& operator=(const Instance&) = delete; ///< Deleted copy operator.

    /**
     * @brief Access the Instance singleton.
     * @return A reference to the Instance singleton.
     */
    static Instance& get() {
        static Instance instance;
        return instance;
    }

    static VKAPI_ATTR vk::Bool32 VKAPI_CALL debug_callback(vk::DebugUtilsMessageSeverityFlagBitsEXT severity,
                                                           vk::DebugUtilsMessageTypeFlagsEXT type,
                                                           const vk::DebugUtilsMessengerCallbackDataEXT* callback_data,
                                                           void* user_data);

private:
    vk::raii::Context context;
    vk::raii::Instance instance;
    vk::raii::DebugUtilsMessengerEXT debug_messenger;
};
