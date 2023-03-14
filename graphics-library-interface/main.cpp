//
//  main.cpp
//  graphics-library-interface
//
//  Created by Frank Collebrusco on 3/13/23.
//
#include <GLFW/glfw3.h>
#include <iostream>

struct ivec2 {
    int32_t x, y;
};

static ivec2 frame;
static float aspect;
static GLFWwindow* handle;
const static char* title = "hello world";

int main(int argc, const char * argv[]) {
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
    handle = glfwCreateWindow(frame.x, frame.y, title, NULL, NULL);
    if (!handle){ //redundant
        glfwTerminate();
        std::cout << "Failed to create window!" << std::endl;
    }
    
    //CALLBACKS
    glfwMakeContextCurrent(handle);

    //V-SYNC
    glfwSwapInterval(1);
    while (!glfwWindowShouldClose(handle)){
        
        glfwPollEvents();
        glfwSwapBuffers(handle);
    }
}
