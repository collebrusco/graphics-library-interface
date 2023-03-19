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

typedef uint32_t MAP_ID;

template <typename T>
class ID_Map {
private:
    MAP_ID counter;
    std::unordered_map<MAP_ID, Shader> map;
public:
    ID_Map(){
        counter = 0;
    }
    template <typename... Params>
    MAP_ID emplace_shader(Params... args){
        MAP_ID res = counter++;
        map.emplace(std::make_pair(res, Shader(args...)));
        return res;
    }
    Shader& get(MAP_ID id){
        return map[id];
    }
    void remove(MAP_ID id){
        map[id].destroy();
        map.erase(id);
    }
    Shader& operator[](MAP_ID id){
        return map[id];
    }
};


#endif /* ShaderContainer_h */
