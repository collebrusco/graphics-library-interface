//
//  main.cpp
//  graphics-library-interface
//
//  Created by Frank Collebrusco on 3/13/23.
//
#include <iostream>
#include "app/Application.h"
#include "gfx/Window.h"

static Application* app;

int main(int argc, const char * argv[]) {
    
    Window* w = new Window("test");
    Window* w1 = new Window("test2");
        
    app = new Application();
    app->enlist(w);
    app->enlist(w1);
    app->set_terminate_condition([&]()->bool{return w->should_close() || w1->should_close();});
    
    int c = 0;
    
    UPDATE_FUNC_ID n = app->enlist_update([&](float){
        if (w->keyboard.keys[GLFW_KEY_SPACE].pressed){
            std::cout << "that's " << c++ << " space(s) from " << w->get_title() << "!\n";
            if (c>10){
                app->delist_update(n);
            }
        }
        if (w1->keyboard.keys[GLFW_KEY_SPACE].pressed){
            std::cout << "that's " << c++ << " space(s) from " << w1->get_title() << "!\n";
            if (c>10){
                app->delist_update(n);
            }
        }
    });
    
    
    app->run();
    
    delete app;
    
    return 0;
}
