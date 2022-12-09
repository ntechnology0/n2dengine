//
//  main.cpp
//  N2DSandbox
//
//  Created by Oussama Jaaouani on 9/12/2022.
//

# include "N2DApplication.hpp"

int main(int argc, const char * argv[]) {
    N2D::N2DApplication* app = new N2D::N2DApplication(1366, 768);
    app->initialize("SDL2 Window");
    while(!app->isDone()) {
        app->update();
        app->input();
    }
    app->close();
    delete app;
    return 0;
}
