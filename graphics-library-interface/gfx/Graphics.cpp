//
//  Graphics.cpp
//  graphics-library-interface
//
//  Created by Frank Collebrusco on 3/17/23.
//
//

#include "Graphics.h"
#include <iostream>

bool Graphics::isinit = false;
ShaderContainer Graphics::shaders;

static void error_callback(int error, const char* description){
    std::cout << "error: " << description << std::endl;
}

void Graphics::init(){
    if (!isinit){
        glfwSetErrorCallback(error_callback);
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
        isinit = true;
    }
}

void Graphics::destroy(){
    isinit = false;
    glfwTerminate();
}

bool Graphics::isInit(){
    return isinit;
}

Window& Graphics::createWindow(const char *title){
    assert(isinit);
    Window* win = new Window(title);
    return *win;
}
