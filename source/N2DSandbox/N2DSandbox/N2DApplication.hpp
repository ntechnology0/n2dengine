//
//  N2DApplication.hpp
//  N2DSandbox
//
//  Created by Oussama Jaaouani on 9/12/2022.
//

#ifndef N2DApplication_hpp
#define N2DApplication_hpp

# include "N2DRenderer.hpp"

namespace N2D {
    class N2DApplication {
    public:
        N2DApplication() = delete;
        N2DApplication(unsigned int _width, unsigned int _height);
        ~N2DApplication(void);
    public:
        void initialize(char* _windowCaption);
        void update(void);
        void input(void);
        void close(void);
    public:
        inline bool isDone(void) { return this->m_isDone; }
        inline unsigned int getWidth(void) { return this->m_width; }
        inline unsigned int getHeight(void) { return this->m_height; }
    private:
        unsigned int m_height;
        unsigned int m_width;
        int m_mouseX = 0;
        int m_mouseY = 0;
        bool m_isDone = false;
        unsigned char* m_keystate = nullptr;
    private:
        SDL_Event m_event;
        N2D::Graphics::N2DRenderer* m_renderer = nullptr;
    };
}

#endif /* N2DApplication_hpp */
