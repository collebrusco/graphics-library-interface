//
//  main.cpp
//  graphics-library-interface
//
//  Created by Frank Collebrusco on 3/13/23.
//
#include <iostream>
#include "app/Application.h"
#include "flgl/Graphics.h"

#include "Meshes.h"

static Application* app;

int main(int argc, const char * argv[]) {
    
    Graphics::init();
    Window& w = Graphics::createWindow("test");
    auto shaderID = Graphics::shaders.emplace("test_vert_shader", "test_frag_shader");
    auto tileID = Graphics::meshes.emplace(Graphics::UploadMesh(TileMesh));
    Graphics::setClearColor(0.5f, 0.f, 0.f, 0.f);
        
    app = new Application();
    app->enlist(&w);
    app->enlist_update([&](float){
        Graphics::clear(false);
        Graphics::shaders[shaderID].bind();
        Graphics::DrawMesh(Graphics::meshes[tileID]);
    });
    app->set_window_terminate_condition(w);
    
//    int c = 0;
//    
//    UPDATE_FUNC_ID n = app->enlist_update([&](float){
//        if (w.keyboard.keys[GLFW_KEY_SPACE].pressed){
//            std::cout << "that's " << c++ << " space(s) from " << w.get_title() << "!\n";
//            if (c>10){
//                app->delist_update(n);
//            }
//        }
//    });
    
    
    app->run();
    
    delete app;
    
    return 0;
}
