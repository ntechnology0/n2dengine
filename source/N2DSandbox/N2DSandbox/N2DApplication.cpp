//
//  N2DApplication.cpp
//  N2DSandbox
//
//  Created by Oussama Jaaouani on 9/12/2022.
//

#include "N2DApplication.hpp"

namespace N2D {
    N2D::N2DApplication::N2DApplication(unsigned int _width, unsigned int _height) : m_width(_width), m_height(_height), m_isDone(false) {
        this->m_renderer = new N2D::Graphics::N2DRenderer(_width, _height);
    }
    N2DApplication::~N2DApplication(void) {}

    void N2D::N2DApplication::initialize(char *_windowCaption) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cout << "Failed to initialize SDL2 :" << SDL_GetError() << std::endl;
            exit(1);
        }
        SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING,"1");
        this->m_renderer->initialize(_windowCaption);
    }
    
    void N2D::N2DApplication::input(void) {
        while(SDL_PollEvent(&m_event) != 0) {
            switch(m_event.type) {
                case SDL_QUIT: this->m_isDone = true; break;
                default: break;
            }
        }
    }

    void N2D::N2DApplication::update(void) {
        SDL_GetWindowPosition(this->m_renderer->getWindow(), &this->m_mouseX, &this->m_mouseY);
    }

    void N2D::N2DApplication::close() {
        this->m_renderer->destroy();
        SDL_Quit();
    }
}
