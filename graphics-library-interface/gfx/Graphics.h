//
//  Graphics.h
//  graphics-library-interface
//
//  Created by Frank Collebrusco on 3/17/23.
//
//

#ifndef Graphics_h
#define Graphics_h
#include "Window.h"
#include "ID_Map.h"

class Graphics {
private:
    static bool isinit;
public:
    static void init();
    static bool isInit();
    static void destroy();
    
    static Window& createWindow(const char* title);
    static ID_Map<Shader> shaders;
};

#endif /* Graphics_h */
