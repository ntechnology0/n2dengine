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
            
            if (this->m_window == nullptr) {
                std::cout << "SDL2 window parameter null" << std::endl;
                exit(1);
            }
            
            if(!SDL_Vulkan_GetInstanceExtensions(this->m_window, &extensionCount, nullptr)) {
                std::cout << "Failed to get Vulkan Instance Extensions count" << std::endl;
                exit(1);
            };
            
            extensions = new const char *[extensionCount];
            if(!SDL_Vulkan_GetInstanceExtensions(this->m_window, &extensionCount, extensions)) {
                SDL_free(extensions);
                std::cout << "Failed to get Vulkan Instance Extensions" << std::endl;
                exit(1);
            }
            
            this->m_extensionsCount = extensionCount;
            for (uint32_t i = 0; i < extensionCount; i++) {
                this->m_extensions.emplace_back(extensions[i]);
            }
            
            VkApplicationInfo applicationInformation = {
                VK_STRUCTURE_TYPE_APPLICATION_INFO,
                nullptr,
                this->m_name.data(),
                VK_MAKE_VERSION(1, 0, 0),
                "N2D Engine",
                VK_MAKE_VERSION(1, 0, 0),
                VK_API_VERSION_1_0
            };
            
            VkInstanceCreateInfo instanceInformation = {
                VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                nullptr,
                0,
                &applicationInformation,
                0,
                nullptr,
                extensionCount,
                extensions
            };
            
#           if defined(__N2D_APPLE__)
            this->m_extensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
            instanceInformation.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
            instanceInformation.ppEnabledExtensionNames = this->m_extensions.data();
            instanceInformation.enabledExtensionCount = (uint32_t) this->m_extensions.size();
#           endif

            if(vkCreateInstance(&instanceInformation, nullptr, &this->m_instance) != VK_SUCCESS) {
                SDL_free(extensions);
                exit(1);
            }
            
            SDL_free(extensions);
        }
    
        void N2DVulkan::destroy() {
            vkDestroyInstance(this->m_instance, nullptr);
            SDL_Vulkan_UnloadLibrary();
        }
    }
}
