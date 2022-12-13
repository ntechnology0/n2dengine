//
//  N2DVulkanDevice.hpp
//  N2DSandbox
//
//  Created by Oussama Jaaouani on 10/12/2022.
//

#ifndef N2DVulkanDevice_hpp
#define N2DVulkanDevice_hpp

# include "Platform.h"

namespace N2D {
    namespace Graphics {
        struct N2DVulkanQueueFamilyIndice {
            std::optional<uint32_t> m_queueFamilyCount;
            std::vector<VkQueueFamilyProperties> m_queueFamilies;
            std::optional<uint32_t> m_pickedQueueFamily;
            std::optional<uint32_t> m_pickedPresentFamily;
            
            bool isComplete () {
                return m_pickedQueueFamily.has_value()
                    && m_pickedPresentFamily.has_value();
            }
        };
    
        class N2DVulkanDevice {
        public:
            N2DVulkanDevice() = default;
            ~N2DVulkanDevice(void) = delete;
        public:
            void initialize(SDL_Window* _window, VkInstance _instance);
            inline VkDevice getDevice() { return this->m_device; }
            inline VkQueue  getGraphicsQueue() { return this->m_graphicsQueue; }
            inline VkQueue  getPresentQueue() { return this->m_presentQueue; }
            inline VkPhysicalDeviceFeatures getPhysicalDeviceFeatures() { return this->m_pickedPhysicalDeviceFeatures; }
            inline VkPhysicalDevice getPhysicalDevice() { return this->m_pickedPhysicalDevice; }
            inline VkSurfaceKHR getSurfaceKHR() { return this->m_surface; }
            
            void destroy();
        private:
            bool isPhysicalDeviceSuitable(VkPhysicalDevice _device);
        private:
            VkDevice m_device = nullptr;
            VkPhysicalDevice m_pickedPhysicalDevice = nullptr;
            VkSurfaceKHR m_surface = nullptr;
            VkInstance m_instance = nullptr;
            VkPhysicalDeviceFeatures m_pickedPhysicalDeviceFeatures;
            VkQueue m_graphicsQueue = nullptr;
            VkQueue m_presentQueue = nullptr;
            
            uint32_t m_physicalDevicesCount = 0;
            N2DVulkanQueueFamilyIndice m_queueFamilyIndices = {};
            std::vector<VkDeviceQueueCreateInfo> m_queueCreateInfos = {};
            std::vector<VkPhysicalDevice> m_physicalDevices = {};
        };
    }
}
#endif /* N2DVulkanDevice_hpp */
