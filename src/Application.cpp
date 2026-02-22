/***************************************************************************************************
 * @file  Application.cpp
 * @brief Implementation of the Application class
 **************************************************************************************************/

#include "Application.hpp"

#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <vk_mem_alloc.h>
#include <vulkan/vulkan.h>

const char* vk_result_to_string(VkResult result) {
    switch(result) {
        case 0:           return "VK_SUCCESS";
        case 1:           return "VK_NOT_READY";
        case 2:           return "VK_TIMEOUT";
        case 3:           return "VK_EVENT_SET";
        case 4:           return "VK_EVENT_RESET";
        case 5:           return "VK_INCOMPLETE";
        case -1:          return "VK_ERROR_OUT_OF_HOST_MEMORY";
        case -2:          return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
        case -3:          return "VK_ERROR_INITIALIZATION_FAILED";
        case -4:          return "VK_ERROR_DEVICE_LOST";
        case -5:          return "VK_ERROR_MEMORY_MAP_FAILED";
        case -6:          return "VK_ERROR_LAYER_NOT_PRESENT";
        case -7:          return "VK_ERROR_EXTENSION_NOT_PRESENT";
        case -8:          return "VK_ERROR_FEATURE_NOT_PRESENT";
        case -9:          return "VK_ERROR_INCOMPATIBLE_DRIVER";
        case -10:         return "VK_ERROR_TOO_MANY_OBJECTS";
        case -11:         return "VK_ERROR_FORMAT_NOT_SUPPORTED";
        case -12:         return "VK_ERROR_FRAGMENTED_POOL";
        case -13:         return "VK_ERROR_UNKNOWN";
        case -1000011001: return "VK_ERROR_VALIDATION_FAILED";
        case -1000069000: return "VK_ERROR_OUT_OF_POOL_MEMORY";
        case -1000072003: return "VK_ERROR_INVALID_EXTERNAL_HANDLE";
        case -1000257000: return "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
        case -1000161000: return "VK_ERROR_FRAGMENTATION";
        case 1000297000:  return "VK_PIPELINE_COMPILE_REQUIRED";
        case -1000174001: return "VK_ERROR_NOT_PERMITTED";
        case -1000000000: return "VK_ERROR_SURFACE_LOST_KHR";
        case -1000000001: return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
        case 1000001003:  return "VK_SUBOPTIMAL_KHR";
        case -1000001004: return "VK_ERROR_OUT_OF_DATE_KHR";
        case -1000003001: return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
        case -1000012000: return "VK_ERROR_INVALID_SHADER_NV";
        case -1000023000: return "VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR";
        case -1000023001: return "VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR";
        case -1000023002: return "VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR";
        case -1000023003: return "VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR";
        case -1000023004: return "VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR";
        case -1000023005: return "VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR";
        case -1000158000: return "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
        case -1000208000: return "VK_ERROR_PRESENT_TIMING_QUEUE_FULL_EXT";
        case -1000255000: return "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
        case 1000268000:  return "VK_THREAD_IDLE_KHR";
        case 1000268001:  return "VK_THREAD_DONE_KHR";
        case 1000268002:  return "VK_OPERATION_DEFERRED_KHR";
        case 1000268003:  return "VK_OPERATION_NOT_DEFERRED_KHR";
        case -1000299000: return "VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR";
        case -1000338000: return "VK_ERROR_COMPRESSION_EXHAUSTED_EXT";
        case 1000482000:  return "VK_INCOMPATIBLE_SHADER_BINARY_EXT";
        case 1000483000:  return "VK_PIPELINE_BINARY_MISSING_KHR";
        case -1000483000: return "VK_ERROR_NOT_ENOUGH_SPACE_KHR";
        default:          return "Unknown VkResult";
    }
}

static inline void vk_check(VkResult result) {
    if(result != VK_SUCCESS) {
        std::stringstream error_message;
        error_message << "Vulkan call returned error code " << result << ": " << vk_result_to_string(result);
        throw std::runtime_error(error_message.str());
    }
}

Application::Application() {}

void Application::run() {
    VkApplicationInfo app_info {};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "Vulkan Engine";
    app_info.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo instance_ci {};
    instance_ci.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_ci.pApplicationInfo = &app_info;
    instance_ci.enabledExtensionCount = 0;
    instance_ci.ppEnabledExtensionNames = glfwGetRequiredInstanceExtensions(&instance_ci.enabledExtensionCount);

    VkInstance instance = VK_NULL_HANDLE;
    vk_check(vkCreateInstance(&instance_ci, nullptr, &instance));

    uint32_t device_count = 0;
    vk_check(vkEnumeratePhysicalDevices(instance, &device_count, nullptr));
    std::vector<VkPhysicalDevice> devices(device_count);
    vk_check(vkEnumeratePhysicalDevices(instance, &device_count, devices.data()));

    uint32_t device_index = 0;
    if(device_count > 1) {
        std::cout << "Found " << device_count << " physical devices. Pick which one to use:\n";
        do {
            for(std::size_t i = 0; i < device_count; ++i) {
                VkPhysicalDeviceProperties2 device_properties {};
                device_properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
                vkGetPhysicalDeviceProperties2(devices[i], &device_properties);
                std::cout << "\tDevice " << i << ": " << device_properties.properties.deviceName << '\n';
            }

            std::cout << "Device index: ";
            std::cin >> device_index;
            if(device_index >= device_count) { std::cout << "Please enter a correct device index.\n"; }
        } while(device_index >= device_count);
    }

    VkPhysicalDeviceProperties2 device_properties {};
    device_properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
    vkGetPhysicalDeviceProperties2(devices[device_index], &device_properties);
    std::cout << "Selected device: " << device_properties.properties.deviceName << "\n";

    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(devices[device_index], &queue_family_count, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(devices[device_index], &queue_family_count, queueFamilies.data());
    uint32_t queue_family_index = 0;
    for(size_t i = 0; i < queueFamilies.size(); i++) {
        if(queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            queue_family_index = i;
            break;
        }
    }

    if(!glfwGetPhysicalDevicePresentationSupport(instance, devices[device_index], queue_family_index)) {
        throw std::runtime_error("Selected queue family does not support presentation.");
    }

    const float queue_priorities = 1.0f;
    VkDeviceQueueCreateInfo queue_ci {};
    queue_ci.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_ci.queueFamilyIndex = queue_family_index;
    queue_ci.queueCount = 1;
    queue_ci.pQueuePriorities = &queue_priorities;

    const std::vector<const char*> deviceExtensions { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

    VkPhysicalDeviceVulkan12Features enabled_vulkan_1_2_features {};
    enabled_vulkan_1_2_features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
    enabled_vulkan_1_2_features.descriptorIndexing = true;
    enabled_vulkan_1_2_features.shaderSampledImageArrayNonUniformIndexing = true;
    enabled_vulkan_1_2_features.descriptorBindingVariableDescriptorCount = true;
    enabled_vulkan_1_2_features.runtimeDescriptorArray = true;
    enabled_vulkan_1_2_features.bufferDeviceAddress = true;

    VkPhysicalDeviceVulkan13Features enabled_vulkan_1_3_features {};
    enabled_vulkan_1_3_features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
    enabled_vulkan_1_3_features.pNext = &enabled_vulkan_1_2_features;
    enabled_vulkan_1_3_features.synchronization2 = true;
    enabled_vulkan_1_3_features.dynamicRendering = true;

    VkPhysicalDeviceFeatures enabled_vulkan_1_0_features {};
    enabled_vulkan_1_0_features.samplerAnisotropy = VK_TRUE;

    VkDeviceCreateInfo device_ci {};
    device_ci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_ci.pNext = &enabled_vulkan_1_3_features;
    device_ci.queueCreateInfoCount = 1;
    device_ci.pQueueCreateInfos = &queue_ci;
    device_ci.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    device_ci.ppEnabledExtensionNames = deviceExtensions.data();
    device_ci.pEnabledFeatures = &enabled_vulkan_1_0_features;

    VkDevice device = VK_NULL_HANDLE;
    vk_check(vkCreateDevice(devices[device_index], &device_ci, nullptr, &device));

    VkQueue queue = VK_NULL_HANDLE;
    vkGetDeviceQueue(device, queue_family_index, 0, &queue);

    VmaVulkanFunctions vk_functions {};
    vk_functions.vkGetInstanceProcAddr = vkGetInstanceProcAddr;
    vk_functions.vkGetDeviceProcAddr = vkGetDeviceProcAddr;
    vk_functions.vkCreateImage = vkCreateImage;

    VmaAllocatorCreateInfo allocator_ci {};
    allocator_ci.flags = VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT;
    allocator_ci.physicalDevice = devices[device_index];
    allocator_ci.device = device;
    allocator_ci.pVulkanFunctions = &vk_functions;
    allocator_ci.instance = instance;

    VmaAllocator allocator = VK_NULL_HANDLE;
    vk_check(vmaCreateAllocator(&allocator_ci, &allocator));

    VkSurfaceKHR surface = VK_NULL_HANDLE;
    glfwCreateWindowSurface(instance, window.get_glfw_window(), nullptr, &surface);

    VkSurfaceCapabilitiesKHR surface_capabilities {};
    vk_check(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(devices[device_index], surface, &surface_capabilities));

    const VkFormat image_format = VK_FORMAT_B8G8R8A8_SRGB;
    VkSwapchainCreateInfoKHR swapchain_ci {};
    swapchain_ci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchain_ci.surface = surface;
    swapchain_ci.minImageCount = surface_capabilities.minImageCount;
    swapchain_ci.imageFormat = image_format;
    swapchain_ci.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    swapchain_ci.imageExtent.width = surface_capabilities.currentExtent.width;
    swapchain_ci.imageExtent.height = surface_capabilities.currentExtent.height;
    swapchain_ci.imageArrayLayers = 1;
    swapchain_ci.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapchain_ci.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    swapchain_ci.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchain_ci.presentMode = VK_PRESENT_MODE_FIFO_KHR;

    VkSwapchainKHR swapchain = VK_NULL_HANDLE;
    vk_check(vkCreateSwapchainKHR(device, &swapchain_ci, nullptr, &swapchain));

    uint32_t image_count = 0;
    vk_check(vkGetSwapchainImagesKHR(device, swapchain, &image_count, nullptr));
    std::vector<VkImage> swapchainImages(image_count);
    vk_check(vkGetSwapchainImagesKHR(device, swapchain, &image_count, swapchainImages.data()));
    std::vector<VkImageView> swapchainImageViews(image_count);

    std::vector<VkFormat> depth_format_list { VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT };
    VkFormat depth_format = VK_FORMAT_UNDEFINED;
    for(VkFormat& format : depth_format_list) {
        VkFormatProperties2 format_properties {};
        format_properties.sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2;
        vkGetPhysicalDeviceFormatProperties2(devices[device_index], format, &format_properties);
        if(format_properties.formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
            depth_format = format;
            break;
        }
    }
}
