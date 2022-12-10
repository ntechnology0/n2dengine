//
//  N2DRenderer.hpp
//  N2DSandbox
//
//  Created by Oussama Jaaouani on 9/12/2022.
//

#ifndef N2DRenderer_hpp
#define N2DRenderer_hpp

# include "Platform.h"
# include "N2DVulkan.hpp"

namespace N2D {
    namespace Graphics {
        class N2DRenderer {
        public:
            N2DRenderer() = delete;
            N2DRenderer(unsigned int _width, unsigned int _height);
            ~N2DRenderer(void);
        public:
            void initialize(char* _windowCaption);
            void destroy(void);
        public:
            inline SDL_Window* getWindow(void) { return this->m_handle; }
            inline SDL_Renderer* getRenderer(void) { return this->m_renderer; }
            inline unsigned int getWidth(void) { return this->m_width; }
            inline unsigned int getHeight(void) { return this->m_height; }
        private:
            SDL_Window* m_handle = nullptr;
            SDL_Renderer* m_renderer = nullptr;
            N2DVulkan* m_vulkan = nullptr;
            unsigned int m_width;
            unsigned int m_height;
        };
    }
}
#endif /* N2DRenderer_hpp */
