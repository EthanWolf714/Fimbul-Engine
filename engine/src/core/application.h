#pragma once

#include "defines.h"
#include "logger.h"
#include "platform/platform.h"
#include "core/fmemory.h"
#include "core/event.h"
#include "core/input.h"

struct game;

struct application_config{
    //window start x position 
    i16 start_pos_x; 

    //window start y position
    i16 start_pos_y;

    //window start window
    i16 start_width;

    //window start height
    i16 start_height;

    //platform window name if applicable
    const char* name;
};

struct application_state{
        game* game_inst;
        b8 is_running;
        b8 is_suspended;
        platform_state platform;
        i16 width;
        i16 height;
        f64 last_time;

};
class application {
    

    public:
        FAPI b8 application_create(struct game* game_inst);
        FAPI b8 application_run();
    private:
    
        

        

};