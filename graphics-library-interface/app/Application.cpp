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
    ID_counter = 0;
}
void Application::run(){
    if (!closer){
        throw("no terminate condition set!");
    }
    this->init();
    while (!((closer)())){
        this->update();
//        std::cout << this->getFPS() << "\n";
    }
    this->destroy();
    
}
void Application::set_terminate_condition(std::function<bool(void)> c){
    closer = c;
}
void Application::enlist(Updatable* obj){
    updatables.push_back(obj);
}

uint32_t Application::newID(){
    return ++ID_counter;
}

INIT_FUNC_ID Application::enlist_init(std::function<void(void)> f){
    INIT_FUNC_ID id = newID();
    inits[id] = f;
    return id;
}

UPDATE_FUNC_ID Application::enlist_update(std::function<void(float)> f){
    UPDATE_FUNC_ID id = newID();
    updates[id] = f;
    return id;
}


DESTROY_FUNC_ID Application::enlist_destructor(std::function<void(void)> f){
    DESTROY_FUNC_ID id = newID();
    destroys[id] = f;
    return id;
}

void Application::delist_init(INIT_FUNC_ID i){
    inits.erase(i);
}
void Application::delist_update(UPDATE_FUNC_ID i){
    updates.erase(i);
}
void Application::delist_destructor(DESTROY_FUNC_ID i){
    destroys.erase(i);
}

void Application::init(){
    watch.start();
    for (auto i : updatables)
        i->init();
    for (auto i : inits)
        i.second();
    dt = watch.stop_reset_start();
}
void Application::update(){
    for (auto u : updatables)
        u->update(dt);
    for (auto i : updates)
        i.second(dt);
    dt = watch.stop_reset_start(ftime::SECONDS);
}
void Application::destroy(){
    for (auto d : updatables){
        d->destroy();
        delete d;
    }
    for (auto i : destroys)
        i.second();
}
float Application::getFPS(){
    return 1 / dt;
}


