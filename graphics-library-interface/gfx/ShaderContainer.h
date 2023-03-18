//
//  ShaderContainer.h
//  graphics-library-interface
//
//  Created by Frank Collebrusco on 3/17/23.
//
//

#ifndef ShaderContainer_h
#define ShaderContainer_h
#include "Shader.h"
#include <unordered_map>

typedef uint32_t SHADER_ID;

class ShaderContainer {
private:
    static SHADER_ID counter;
    std::unordered_map<SHADER_ID, Shader> shaderMap;
public:
    SHADER_ID emplace_shader(const char*, const char*);
    Shader& get(SHADER_ID);
    void remove(SHADER_ID);
    Shader& operator[](SHADER_ID);
};


#endif /* ShaderContainer_h */
