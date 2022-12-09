//
//  N2DRenderer.cpp
//  N2DSandbox
//
//  Created by Oussama Jaaouani on 9/12/2022.
//

#include "N2DRenderer.hpp"

namespace N2D {
    namespace Graphics {
        N2DRenderer::N2DRenderer(unsigned int _width, unsigned int _height) : m_handle(nullptr), m_width(_width), m_height(_height) {}
        N2DRenderer::~N2DRenderer(void) {}
    
        void N2DRenderer::initialize(char *_windowCaption) {
            std::cout << "Initializing window(" << this->m_width << "," << this->m_height << ")" << std::endl;
            this->m_handle = SDL_CreateWindow(_windowCaption, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->m_width, this->m_height, SDL_WINDOW_RESIZABLE);
            if (this->m_handle == nullptr) {
                std::cout << "SDL_CreateWindow failure: " << SDL_GetError() << std::endl;
                exit(1);
            }
            this->m_renderer = SDL_CreateRenderer(this->m_handle, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
            if (this->m_renderer == nullptr) {
                std::cout << "SDL_CreateRenderer failure: " << SDL_GetError() << std::endl;
                exit(1);
            }
        }

        void N2DRenderer::destroy() {
            SDL_DestroyWindow(this->m_handle);
            SDL_DestroyRenderer(this->m_renderer);
        }
    }
}
