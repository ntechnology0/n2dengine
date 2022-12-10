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
        class N2DVulkanDevice {
        public:
            N2DVulkanDevice() = default;
            ~N2DVulkanDevice(void) = delete;
        public:
            void initialize(VkInstance _instance);
            void destroy();
        private:
            bool isPhysicalDeviceSuitable(VkPhysicalDevice _device);
        private:
            VkDevice m_device = nullptr;
            VkPhysicalDevice m_pickedPhysicalDevice = nullptr;
            uint32_t m_physicalDevicesCount = 0;
            std::vector<VkPhysicalDevice> m_physicalDevices;
        };
    }
}
#endif /* N2DVulkanDevice_hpp */
