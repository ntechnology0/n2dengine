//
//  N2DVulkanDevice.cpp
//  N2DSandbox
//
//  Created by Oussama Jaaouani on 10/12/2022.
//

#include "N2DVulkanDevice.hpp"

namespace N2D {
    namespace Graphics {
        void N2DVulkanDevice::initialize(VkInstance _instance) {
            uint32_t physicalDevicesCount;
            vkEnumeratePhysicalDevices(_instance, &physicalDevicesCount, nullptr);
            this->m_physicalDevices.resize(physicalDevicesCount);
            vkEnumeratePhysicalDevices(_instance, &physicalDevicesCount, this->m_physicalDevices.data());
            this->m_physicalDevicesCount = physicalDevicesCount;
            
            if(physicalDevicesCount == 0) {
                std::cout << "No Physical device found" << std::endl;
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
        }
    
        void N2DVulkanDevice::destroy() {
            vkDestroyDevice(this->m_device, nullptr);
        }
    
        bool N2DVulkanDevice::isPhysicalDeviceSuitable(VkPhysicalDevice _device) {
            VkPhysicalDeviceProperties deviceProperties;
            VkPhysicalDeviceFeatures deviceFeatures;
            vkGetPhysicalDeviceFeatures(_device, &deviceFeatures);
            vkGetPhysicalDeviceProperties(_device, &deviceProperties);
            
            return (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU
                || deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
        }
    }
}
