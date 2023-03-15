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
#include "../util/f_stopwatch.h"
#include "../Updatable.h"

class Application {
protected:
    float dt;
    ftime::StopWatch watch;
    std::vector<Updatable*> updates;
    std::function<bool(void)> closer;
public:
    Application();
    void run();
    void set_terminate_condition(std::function<bool(void)>);
    void enlist(Updatable* obj);
    void init();
    void update();
    void destroy();
    float getFPS();
};

#endif /* Application_h */
