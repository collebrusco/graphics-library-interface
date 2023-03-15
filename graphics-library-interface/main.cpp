//
//  main.cpp
//  graphics-library-interface
//
//  Created by Frank Collebrusco on 3/13/23.
//
#include <iostream>
#include "app/Application.h"
#include "app/Window.h"

static Application* app;

int main(int argc, const char * argv[]) {
    
    Window* w = new Window("default");
    
    std::function<bool(void)> test = [&]()->bool{return w->should_close();} ;
    
    app = new Application();
    app->enlist(w);
    app->set_terminate_condition([&]()->bool{return w->should_close();});
    app->run();
    
    delete app;
    
    return 0;
}
