//
//  N2DVulkan.cpp
//  N2DSandbox
//
//  Created by Oussama Jaaouani on 10/12/2022.
//

#include "N2DVulkan.hpp"

namespace N2D {
    namespace Graphics {
        N2DVulkan::N2DVulkan(SDL_Window* _window, std::string_view _name) : m_window(_window), m_name(_name) {
            SDL_Vulkan_LoadLibrary(nullptr);
        }
        
        void N2DVulkan::initialize() {
            uint32_t extensionCount;
            const char** extensions = 0;
            
            SDL_Vulkan_GetInstanceExtensions(this->m_window, &extensionCount, nullptr);
            extensions = new const char *[extensionCount];
            SDL_Vulkan_GetInstanceExtensions(this->m_window, &extensionCount, extensions);
            this->m_extensionsCount = extensionCount;
            this->m_extensions.resize(extensionCount);
            
            while(*extensions != nullptr) {
                this->m_extensions.push_back(*extensions++);
            }
            
            const VkApplicationInfo applicationInformation = {
                VK_STRUCTURE_TYPE_APPLICATION_INFO,
                nullptr,
                this->m_name.data(),
                VK_MAKE_VERSION(1, 0, 0),
                "N2D Engine",
                VK_MAKE_VERSION(1, 0, 0),
                VK_API_VERSION_1_0
            };
            
            const VkInstanceCreateInfo instanceInformation = {
                VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                &applicationInformation,
                0,
                nullptr,
                0,
                nullptr,
                extensionCount,
                extensions
            };
 
            if(vkCreateInstance(&instanceInformation, nullptr, &this->m_instance) != VK_SUCCESS) {
                std::cout << "Failed to create Vulkan Instance" << std::endl;
                exit(1);
            }
        }
    
        void N2DVulkan::destroy() {
            vkDestroyInstance(this->m_instance, nullptr);
            SDL_Vulkan_UnloadLibrary();
        }
    }
}
