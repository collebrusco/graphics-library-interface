//
//  main.cpp
//  graphics-library-interface
//
//  Created by Frank Collebrusco on 3/13/23.
//
#include <iostream>
#include "app/Application.h"
#include "gfx/Graphics.h"

static Application* app;

int main(int argc, const char * argv[]) {
    
    Graphics::init();
    
    Window& w = Graphics::createWindow("test");
        
    app = new Application();
    app->enlist(&w);
    app->set_terminate_condition([&]()->bool{return w.should_close();});
    
    int c = 0;
    
    UPDATE_FUNC_ID n = app->enlist_update([&](float){
        if (w.keyboard.keys[GLFW_KEY_SPACE].pressed){
            std::cout << "that's " << c++ << " space(s) from " << w.get_title() << "!\n";
            if (c>10){
                app->delist_update(n);
            }
        }
    });
    
    
    app->run();
    
    delete app;
    
    return 0;
}
