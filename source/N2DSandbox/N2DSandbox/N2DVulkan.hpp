//
//  N2DVulkan.hpp
//  N2DSandbox
//
//  Created by Oussama Jaaouani on 10/12/2022.
//

#ifndef N2DVulkan_hpp
#define N2DVulkan_hpp

#include "Platform.h"

namespace N2D {
    namespace Graphics {
        class N2DVulkan {
        public:
            N2DVulkan() = delete;
            N2DVulkan(SDL_Window* _window, std::string_view _name);
        public:
            void initialize(void);
            void destroy(void);
        private:
            SDL_Window* m_window = nullptr;
            VkInstance m_instance = nullptr;
            uint32_t m_extensionsCount = 0;
        private:
            std::string_view m_name;
            std::vector<const char*> m_extensions = {};
        };
    }
}
#endif /* N2DVulkan_hpp */
