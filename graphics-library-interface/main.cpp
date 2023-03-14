//
//  main.cpp
//  graphics-library-interface
//
//  Created by Frank Collebrusco on 3/13/23.
//
#include <iostream>
#include "app/Application.h"

static Application* app;

int main(int argc, const char * argv[]) {
    
    Window* w = new Window();
    
    app = new Application();
    app->enlist(w);
    app->set_terminate_condition(w);
    
    app->run();
    
    delete app;
    
    return 0;
}
