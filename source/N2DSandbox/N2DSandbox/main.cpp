//
//  main.cpp
//  N2DSandbox
//
//  Created by Oussama Jaaouani on 9/12/2022.
//

# include "N2DApplication.hpp"

int main() {
    N2D::N2DApplication* app = new N2D::N2DApplication(1366, 768);
    app->initialize(C_STR(SDL2 Window with Vulkan));
    while(!app->isDone()) {
        app->update();
        app->input();
    }
    app->close();
    delete app;
    return 0;
}
