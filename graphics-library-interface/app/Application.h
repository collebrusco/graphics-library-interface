//
//  Application.h
//  graphics-library-interface
//
//  Created by Frank Collebrusco on 3/13/23.
//
//

#ifndef Application_h
#define Application_h
#include <vector>
#include <iostream>
#include <functional>
#include <unordered_map>
#include "../util/f_stopwatch.h"
#include "../Updatable.h"
#include "../gfx/Window.h"

typedef uint32_t INIT_FUNC_ID;
typedef uint32_t UPDATE_FUNC_ID;
typedef uint32_t DESTROY_FUNC_ID;

class Application {
private:
    uint32_t ID_counter;
    std::unordered_map<INIT_FUNC_ID, std::function<void(void)>> inits;
    std::unordered_map<UPDATE_FUNC_ID, std::function<void(float)>> updates;
    std::unordered_map<DESTROY_FUNC_ID, std::function<void(void)>> destroys;
    std::unordered_map<Updatable*, bool> updatables;
    uint32_t newID();
protected:
    float dt;
    ftime::StopWatch watch;
//    std::vector<Updatable*> updatables;
    std::function<bool(void)> closer;
public:
    // these will be protecteed, public for testing
    void set_terminate_condition(std::function<bool(void)>);
    void set_window_terminate_condition(Window const&);
    void enlist(Updatable* obj);
    void enable(Updatable* obj);
    void disable(Updatable* obj);
    void delist(Updatable* obj);
    INIT_FUNC_ID enlist_init(std::function<void(void)>);
    UPDATE_FUNC_ID enlist_update(std::function<void(float)>);
    DESTROY_FUNC_ID enlist_destructor(std::function<void(void)>);
    void delist_init(INIT_FUNC_ID);
    void delist_update(UPDATE_FUNC_ID);
    void delist_destructor(DESTROY_FUNC_ID);
    
    Application();
    void run();
    void init();
    void update();
    void destroy();
    float getFPS();
};

#endif /* Application_h */
