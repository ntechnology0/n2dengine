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
        struct N2DVulkanQueueFamilyIndices {
            std::optional<uint32_t> m_queueFamilyCount;
            std::vector<VkQueueFamilyProperties> m_queueFamilies;
            std::optional<uint32_t> m_pickedQueueFamily;
            
            bool isComplete () {
                return m_pickedQueueFamily.has_value();
            }
        };
    
        class N2DVulkanDevice {
        public:
            N2DVulkanDevice() = default;
            ~N2DVulkanDevice(void) = delete;
        public:
            void initialize(SDL_Window* _window, VkInstance _instance);
            void destroy();
        private:
            bool isPhysicalDeviceSuitable(VkPhysicalDevice _device);
        private:
            VkDevice m_device = nullptr;
            VkPhysicalDevice m_pickedPhysicalDevice = nullptr;
            VkSurfaceKHR m_surface = nullptr;
            VkInstance m_instance = nullptr;
            VkPhysicalDeviceFeatures m_pickedPhysicalDeviceFeatures;
            
            uint32_t m_physicalDevicesCount = 0;
            N2DVulkanQueueFamilyIndices m_queueFamilyIndices = {};
            std::vector<VkPhysicalDevice> m_physicalDevices = {};
        };
    }
}
#endif /* N2DVulkanDevice_hpp */
