//
//  Application.cpp
//  graphics-library-interface
//
//  Created by Frank Collebrusco on 3/13/23.
//
//


#include <GLFW/glfw3.h>

#include "Application.h"

Application::Application() {
    watch.setUnit(ftime::SECONDS);
    dt = 0;
}
void Application::run(){
    if (!closer){
        throw("no terminate condition set!");
    }
    this->init();
    while (!((closer)())){
        this->update();
        std::cout << this->getFPS() << "\n";
    }
    this->destroy();
    
}
void Application::set_terminate_condition(std::function<bool(void)> c){
    closer = c;
}
void Application::enlist(Updatable* obj){
    updates.push_back(obj);
}
void Application::init(){
    watch.start();
    for (auto i : updates)
        i->init();
    dt = watch.stop_reset_start();
}
void Application::update(){
    for (auto u : updates)
        u->update(dt);
    dt = watch.stop_reset_start(ftime::SECONDS);
}
void Application::destroy(){
    for (auto d : updates){
        d->destroy();
        delete d;
    }
}
float Application::getFPS(){
    return 1 / dt;
}


