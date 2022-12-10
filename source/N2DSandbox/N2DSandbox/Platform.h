//
//  Platform.h
//  N2DSandbox
//
//  Created by Oussama Jaaouani on 10/12/2022.
//

#ifndef Platform_h
#define Platform_h

# include <vulkan/vulkan.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_vulkan.h>

# include <vector>
# include <iostream>
# include <string>
# include <optional>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define C_STR(s) (char*)#s

# if defined(__APPLE__)
# define __N2D_APPLE__ 1
# endif

#endif /* Platform_h */
