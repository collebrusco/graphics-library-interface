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
#include "Vertex.h"
#include "ID_Map.h"

typedef uint32_t TEXTURE_SLOT;

class Graphics {
private:
    static bool isinit;
    static TEXTURE_SLOT slotsInUse;
public:
    static void init();
    static bool isInit();
    static void destroy();
    static void clear(bool depth);
    static void setClearColor(float, float, float, float);
    static void setDepthTestEnable(bool);
    
    static Window& createWindow(const char* title);
    static ID_Map<Shader> shaders;
    static ID_Map<MeshDetails> meshes;
    
    static TEXTURE_SLOT UploadTexture(std::string name, bool pixelated);
    static MeshDetails UploadMesh(const ConstMesh& mesh);
    static MeshDetails UploadMesh(Mesh const& mesh);
    static void UnloadMesh(MeshDetails&);
    static void UnloadTexture(TEXTURE_SLOT);
    
    static void DrawMesh(MeshDetails& mesh);
    static void DrawMesh(MeshDetails const& mesh);
};

#endif /* Graphics_h */
