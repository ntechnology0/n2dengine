//
//  N2DRenderer.hpp
//  N2DSandbox
//
//  Created by Oussama Jaaouani on 9/12/2022.
//

#ifndef N2DRenderer_hpp
#define N2DRenderer_hpp

# include <SDL2/SDL.h>
# include <iostream>

namespace N2D {
    namespace Graphics {
        class N2DRenderer {
        public:
            N2DRenderer() = delete;
            N2DRenderer(unsigned int _width, unsigned int _height);
            ~N2DRenderer(void) = delete;
        public:
            void initialize(char* _windowCaption);
            void destroy(void);
        private:
            SDL_Window* m_handle;
            SDL_Renderer* m_renderer;
            unsigned int m_width;
            unsigned int m_height;
        };
    }
}
#endif /* N2DRenderer_hpp */
