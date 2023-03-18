//
//  ShaderContainer.cpp
//  graphics-library-interface
//
//  Created by Frank Collebrusco on 3/17/23.
//
//

#include "ShaderContainer.h"

SHADER_ID ShaderContainer::counter = 0;

SHADER_ID ShaderContainer::emplace_shader(const char * vn, const char * fn){
    SHADER_ID res = counter++;
    shaderMap[res].compileAndLink(vn, fn);
    return res;
}

Shader& ShaderContainer::get(SHADER_ID id){
    return shaderMap[id];
}

void ShaderContainer::remove(SHADER_ID id){
    shaderMap[id].destroy();
    shaderMap.erase(id);
}

Shader& ShaderContainer::operator[](SHADER_ID id){
    return shaderMap[id];
}
