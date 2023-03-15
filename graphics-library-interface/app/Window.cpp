//
//  Window.cpp
//  graphics-library-interface
//
//  Created by Frank Collebrusco on 3/14/23.
//
//
#define GL_SILENCE_DEPRECATION
#include "Window.h"
#include <iostream>

static std::map<GLFWwindow*, Window*> window_map;

static void size_callback(GLFWwindow *handle, int width, int height){
    glViewport(0, 0, width, height);
    window_map[handle]->frame = glm::ivec2(width, height);
    window_map[handle]->aspect = (float)width / (float)height;
}

static void error_callback(int error, const char* description){
    std::cout << "error: " << description << std::endl;
}

static void window_close_callback(GLFWwindow *handle){
    std::cout << "window " << window_map[handle]->get_title() << " closed" << std::endl;
}

// ================================

Window::Window(const char* t){
    title = t;
}

const char* Window::get_title(){
    return title;
}

void Window::register_handle(GLFWwindow* h){
    if (window_map.find(h) != window_map.end()){
        throw("duplicate window pointers");
    }
    window_map[h] = this;
}

void Window::init() {
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
    frame.x = 960;
    frame.y = 720;
    aspect = (float)frame.x / (float)frame.y;
    handle = glfwCreateWindow(frame.x, frame.y, title, NULL, NULL);
    if (!handle){ //redundant
        glfwTerminate();
        std::cout << "Failed to create window!" << std::endl;
    }
    register_handle(handle);
    
    glfwSetErrorCallback(error_callback);
    glfwSetFramebufferSizeCallback(handle, size_callback);
    glfwSetWindowCloseCallback(handle, window_close_callback);
    
    glfwMakeContextCurrent(handle);
    glfwSwapInterval(0);
}
void Window::update(float dt) {
    glfwPollEvents();
    glfwSwapBuffers(handle);
}
void Window::destroy() {
    glfwTerminate();
}

bool Window::should_close(){
    return glfwWindowShouldClose(handle);
}
