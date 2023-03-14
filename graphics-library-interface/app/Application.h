//
//  Application.h
//  graphics-library-interface
//
//  Created by Frank Collebrusco on 3/13/23.
//
//

#ifndef Application_h
#define Application_h
#include <vector>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../util/f_stopwatch.h"
class Updatable {
public:
    virtual ~Updatable() = default;
    virtual void init() = 0;
    virtual void update(float dt) = 0;
    virtual void destroy() = 0;
};

class Closer {
public:
    virtual bool should_close() = 0;
};

class Application {
private:
    float dt;
    ftime::StopWatch watch;
    std::vector<Updatable*> updates;
    Closer* terminator;
public:
    Application() {
        watch.setUnit(ftime::SECONDS);
        dt = 0;
    }
    void run(){
        if (!terminator){
            throw("no terminate condition set!");
        }
        this->init();
        while (!(terminator->should_close())){
            this->update();
            std::cout << this->getFPS() << "\n";
        }
        this->destroy();
        
    }
    void set_terminate_condition(Closer* term){
        terminator = term;
    }
    void enlist(Updatable* obj){
        updates.push_back(obj);
    }
    void init(){
        watch.start();
        for (auto i : updates)
            i->init();
        dt = watch.stop_reset_start();
    }
    void update(){
        for (auto u : updates)
            u->update(dt);
        dt = watch.stop_reset_start(ftime::SECONDS);
    }
    void destroy(){
        for (auto d : updates){
            d->destroy();
            delete d;
        }
    }
    float getFPS(){
        return 1 / dt;
    }
};
#include <glm/glm.hpp>
class Window : public Updatable, public Closer {
private:
    GLFWwindow* handle;
    glm::vec2 frame;
    float aspect;
public:
    bool should_close() override {
        return glfwWindowShouldClose(handle);
    }
    virtual void init() override {
        if (!glfwInit()){
            std::cout << "Failed to initialize GLFW! :(\n";
            throw ("failed GLFW init");
        }
    #ifdef __APPLE__
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #endif
    //    window.frame.x = 1440;
    //    window.frame.y = 1080;
        frame.x = 960;
        frame.y = 720;
        aspect = (float)frame.x / (float)frame.y;
        handle = glfwCreateWindow(frame.x, frame.y, "title", NULL, NULL);
        if (!handle){ //redundant
            glfwTerminate();
            std::cout << "Failed to create window!" << std::endl;
        }
        
        glfwMakeContextCurrent(handle);
        glfwSwapInterval(0);
    }
    virtual void update(float dt) override {
        glfwPollEvents();
        glfwSwapBuffers(handle);
    }
    virtual void destroy() override {
        glfwTerminate();
    }
};

#endif /* Application_h */
