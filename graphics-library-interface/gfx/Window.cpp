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

static std::map<GLFWwindow*, Window*> windowMap;

void Window::register_handle(GLFWwindow* handle){
    assert(windowMap.find(handle) == windowMap.end());
    windowMap[handle] = this;
}

static void size_callback(GLFWwindow *handle, int width, int height){
    glViewport(0, 0, width, height);
    windowMap[handle]->frame = glm::ivec2(width, height);
    windowMap[handle]->aspect = (float)width / (float)height;
}

static void window_close_callback(GLFWwindow *handle){
    std::cout << "window " << windowMap[handle]->get_title() << " closed" << std::endl;
    
}

static void error_callback(int error, const char* description){
    std::cout << "error: " << description << std::endl;
}

static void cursor_callback(GLFWwindow *handle, double xp, double yp){
    glm::vec2 p = glm::vec2(xp,yp);
    windowMap[handle]->mouse.delta = p - windowMap[handle]->mouse.pos;
    windowMap[handle]->mouse.delta.x = glm::clamp(windowMap[handle]->mouse.delta.x, -100.0f, 100.0f);
    windowMap[handle]->mouse.delta.y = glm::clamp(windowMap[handle]->mouse.delta.y, -100.0f, 100.0f);

    windowMap[handle]->mouse.pos = p;
}

static void key_callback(GLFWwindow* handle, int key, int scancode, int action, int mods){
    if (key < 0) {
        return;
    }
    switch (action){
        case GLFW_PRESS:
            windowMap[handle]->keyboard.keys[key].down = true;
            break;
        case GLFW_RELEASE:
            windowMap[handle]->keyboard.keys[key].down = false;
            break;
        default:
            break;
    }
    // TODO: escape key is baked into window obj as exit key temporarily for convenience. Remove later
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(handle, GLFW_TRUE);
    }
}

static void mouse_callback(GLFWwindow *handle, int button, int action, int mods){
    if (button < 0){
        return;
    }
    switch (action) {
        case GLFW_PRESS:
            windowMap[handle]->mouse.buttons[button].down = true;
            break;
        case GLFW_RELEASE:
            windowMap[handle]->mouse.buttons[button].down = false;
            break;
        default:
            break;
    }
}

static void scroll_callback(GLFWwindow* handle, double xoffset, double yoffset){
    windowMap[handle]->mouse.scroll.x = xoffset;
    windowMap[handle]->mouse.scroll.y = yoffset;
}


static void initGLFW(){
    static bool isinit = false;
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

// ================================

Window::Window(const char* t){
    title = t;
}

const char* Window::get_title(){
    return title;
}

void Window::update_buttons(Button * b, size_t n){
    for (int i = 0; i < n; i++){
        b[i].pressed = b[i].down && !b[i].last;
        b[i].released = b[i].last && !b[i].down;
        b[i].last = b[i].down;
    }
}

void Window::update_mouse_data(){
    update_buttons(mouse.buttons, GLFW_MOUSE_BUTTON_LAST);
    if (mouse.delta == mouse.delta_last){
        mouse.delta = glm::vec2(0);
    }
    mouse.delta_last = mouse.delta;
    if (mouse.scroll == mouse.scroll_last){
        mouse.scroll = glm::vec2(0);
    }
    mouse.scroll_last = mouse.scroll;
}

void Window::update_key_data(){
    update_buttons(keyboard.keys, GLFW_KEY_LAST);
}

void Window::init() {
    initGLFW();
    frame.x = 960;
    frame.y = 720;
    aspect = (float)frame.x / (float)frame.y;
    handle = glfwCreateWindow(frame.x, frame.y, title, NULL, NULL);
    if (!handle){ //redundant
        glfwTerminate();
        std::cout << "Failed to create window!" << std::endl;
        assert(false);
    }
    register_handle(handle);
    
    glfwSetFramebufferSizeCallback(handle, size_callback);
    glfwSetWindowCloseCallback(handle, window_close_callback);
    glfwSetKeyCallback(handle, key_callback);
    glfwSetScrollCallback(handle, scroll_callback);
    glfwSetCursorPosCallback(handle, cursor_callback);
    glfwSetMouseButtonCallback(handle, mouse_callback);
    
    glfwMakeContextCurrent(handle);
    glfwSwapInterval(0);
}
void Window::update(float dt) {
    update_mouse_data();
    update_key_data();
    glfwPollEvents();
    glfwSwapBuffers(handle);
}
void Window::destroy() {
    glfwTerminate();
}

bool Window::should_close(){
    return glfwWindowShouldClose(handle);
}
