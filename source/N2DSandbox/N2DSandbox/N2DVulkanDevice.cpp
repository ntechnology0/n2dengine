//
//  N2DVulkanDevice.cpp
//  N2DSandbox
//
//  Created by Oussama Jaaouani on 10/12/2022.
//

#include "N2DVulkanDevice.hpp"

namespace N2D {
    namespace Graphics {
        void N2DVulkanDevice::initialize(SDL_Window* _window, VkInstance _instance) {
            uint32_t physicalDevicesCount = 0;
            float queuePriority = 1.0f;
            
            vkEnumeratePhysicalDevices(_instance, &physicalDevicesCount, nullptr);
            this->m_physicalDevices.resize(physicalDevicesCount);
            vkEnumeratePhysicalDevices(_instance, &physicalDevicesCount, this->m_physicalDevices.data());
            this->m_physicalDevicesCount = physicalDevicesCount;
            this->m_instance = _instance;
            
            if(physicalDevicesCount == 0) {
                std::cout << "No Physical device found" << std::endl;
                exit(1);
            }
            
            if(SDL_Vulkan_CreateSurface(_window, this->m_instance, &this->m_surface) == SDL_FALSE) {
                std::cout  << "Failed to create Vulkan Surface KHR" << std::endl;
                exit(1);
            }
            
            for (const VkPhysicalDevice& device: this->m_physicalDevices) {
                if (this->isPhysicalDeviceSuitable(device)) {
                    this->m_pickedPhysicalDevice = device;
                    break;
                }
            }
            
            if (this->m_pickedPhysicalDevice == nullptr) {
                std::cout << "Failed to pick the right physical device" << std::endl;
                exit(1);
            }
            
            std::set<uint32_t> uniqueQueueFamilies = {
                this->m_queueFamilyIndices.m_pickedQueueFamily.value(),
                this->m_queueFamilyIndices.m_pickedPresentFamily.value()
            };
            
            for (uint32_t queueFamily: uniqueQueueFamilies) {
                VkDeviceQueueCreateInfo _queueCreateInfo {};
                _queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                _queueCreateInfo.queueFamilyIndex = queueFamily;
                _queueCreateInfo.queueCount = 1;
                _queueCreateInfo.pQueuePriorities = &queuePriority;
                this->m_queueCreateInfos.push_back(_queueCreateInfo);
            }
            
            VkDeviceCreateInfo deviceCreateInfo = {
                VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
                nullptr,
                0,
                static_cast<uint32_t>(this->m_queueCreateInfos.size()),
                this->m_queueCreateInfos.data(),
            };
            
            deviceCreateInfo.enabledLayerCount = 0;
            deviceCreateInfo.pEnabledFeatures = &this->m_pickedPhysicalDeviceFeatures;
            
            if (vkCreateDevice(this->m_pickedPhysicalDevice, &deviceCreateInfo, nullptr, &this->m_device) != VK_SUCCESS) {
                std::cout  << "Failed to create Vulkan Device" << std::endl;
                exit(1);
            }
            
            vkGetDeviceQueue(this->m_device, this->m_queueFamilyIndices.m_pickedQueueFamily.value(), 0, &this->m_graphicsQueue);
            vkGetDeviceQueue(this->m_device, this->m_queueFamilyIndices.m_pickedPresentFamily.value(), 0, &this->m_presentQueue);
        }
    
        void N2DVulkanDevice::destroy() {
            vkDestroyDevice(this->m_device, nullptr);
            vkDestroySurfaceKHR(this->m_instance, this->m_surface, nullptr);
        }
    
        bool N2DVulkanDevice::isPhysicalDeviceSuitable(VkPhysicalDevice _device) {
            uint32_t queueFamilyCount = 0;
            uint32_t index = 0;
            VkBool32 isPresentQueueSupported = false;
            
            VkPhysicalDeviceProperties deviceProperties;
            VkPhysicalDeviceFeatures deviceFeatures;
            vkGetPhysicalDeviceFeatures(_device, &deviceFeatures);
            vkGetPhysicalDeviceProperties(_device, &deviceProperties);
            this->m_pickedPhysicalDeviceFeatures = deviceFeatures;
            
            // -- get the queue family
            vkGetPhysicalDeviceQueueFamilyProperties(_device, &queueFamilyCount, nullptr);
            this->m_queueFamilyIndices.m_queueFamilies.resize(queueFamilyCount);
            vkGetPhysicalDeviceQueueFamilyProperties(_device, &queueFamilyCount, this->m_queueFamilyIndices.m_queueFamilies.data());
            this->m_queueFamilyIndices.m_queueFamilyCount = queueFamilyCount;
            
            for (const VkQueueFamilyProperties& queueFamily: this->m_queueFamilyIndices.m_queueFamilies) {
                vkGetPhysicalDeviceSurfaceSupportKHR(_device, index, this->m_surface, &isPresentQueueSupported);
                if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) { this->m_queueFamilyIndices.m_pickedQueueFamily = index; }
                if (isPresentQueueSupported) { this->m_queueFamilyIndices.m_pickedPresentFamily = index; }
                index++;
            }
            
            return (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU
                || deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
                && this->m_queueFamilyIndices.isComplete();
        }
    }
}
