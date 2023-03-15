//
//  Window.h
//  graphics-library-interface
//
//  Created by Frank Collebrusco on 3/14/23.
//
//

#ifndef Window_h
#define Window_h
#include "../Updatable.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <map>
class Window : public Updatable {
private:
    void register_handle(GLFWwindow*);
    const char* title;
    GLFWwindow* handle;
public:
    glm::vec2 frame;
    float aspect;
    Window(const char*);
    virtual void init() override;
    virtual void update(float dt) override;
    virtual void destroy() override;
    
    const char* get_title();
    bool should_close();
};

#endif /* Window_h */
