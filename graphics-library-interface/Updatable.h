//
//  Updatable.h
//  graphics-library-interface
//
//  Created by Frank Collebrusco on 3/15/23.
//

#ifndef Updatable_h
#define Updatable_h

class Updatable {
public:
    virtual ~Updatable() = default;
    virtual void init() = 0;
    virtual void update(float dt) = 0;
    virtual void destroy() = 0;
};

#endif /* Updatable_h */
