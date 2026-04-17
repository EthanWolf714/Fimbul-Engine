#include "application.h"
#include "game_types.h"

static b8 initialized = FALSE;
static application_state app_state;

b8 application_on_event(u16 code, void* sender, void* listener_inst, EventContext context);
b8 application_on_keys(u16 code, void* sender, void* listener_inst, EventContext context);

b8 application::application_create(game* game_inst){
    if(initialized){
        FERROR("application_create called more than once");
        return FALSE;
    } 

    app_state.game_inst = game_inst;

    //intialize subsystems
    initialize_logging();
    input_initialize();


     //log test
    FFATAL("A TEST MESSAGE: %f", 3.14);
    FERROR("A TEST MESSAGE: %f", 3.14);
    FWARN("A TEST MESSAGE: %f", 3.14);
    FINFO("A TEST MESSAGE: %f", 3.14);
    FDEBUG("A TEST MESSAGE: %f", 3.14);
    FTRACE("A TEST MESSAGE: %f", 3.14);

    app_state.is_running = TRUE;
    app_state.is_suspended = FALSE;

    if(!event_syst.initialize()){
        FERROR("Event system failed initialization. Application cannot continue!");
        return FALSE;
    }

    event_syst.register_event(EVENT_CODE_APPLICATION_QUIT, 0, application_on_event);
    event_syst.register_event(EVENT_CODE_KEY_PRESSED,0, application_on_keys);
    event_syst.register_event(EVENT_CODE_KEY_RELEASED, 0, application_on_keys);

    if(!platform_startup(
        &app_state.platform, 
        game_inst->app_config.name, 
        game_inst->app_config.start_pos_x, 
        game_inst->app_config.start_pos_y, 
        game_inst->app_config.start_width, 
        game_inst->app_config.start_height)){
        return FALSE;
    }

    //initialize
    if(!app_state.game_inst->initialize(app_state.game_inst)){
        FFATAL("Game failed to initialized.");
    }

    app_state.game_inst->on_resize(app_state.game_inst,app_state.width, app_state.height);

    initialized = true;

    return TRUE;

    
}
        
b8 application::application_run(){
    FINFO(memory.get_memory_usage_str());
    while(app_state.is_running){
        if(!platform_pump_message(&app_state.platform)){
            app_state.is_running = FALSE;
        }   
        if(!app_state.is_suspended){
            if(!app_state.game_inst->update(app_state.game_inst, (f32)(0))){
                FFATAL("Game update failed, shutting down.");
                app_state.is_running = FALSE;
                break;
            }

        }   
        //call games render routine
        if(!app_state.game_inst->render(app_state.game_inst, (f32)0)){
            FFATAL("Game render failed, shutting down.");
            app_state.is_running = FALSE;
            break;
        }

        //NOTE: input update/state copying should 
        //always be handled after any input 
        //should be recordere; I.E. before this line
        //as a saftey, input is the last thing to be updated before
        //this frame ends

        input_update(0);
    }

    app_state.is_running = FALSE;
     event_syst.unregister_event(EVENT_CODE_APPLICATION_QUIT, 0);
    event_syst.unregister_event(EVENT_CODE_KEY_PRESSED,0);
    event_syst.unregister_event(EVENT_CODE_KEY_RELEASED, 0);
    event_syst.shutdown();
    input_shutdown();
    platform_shutdown(&app_state.platform);

    return TRUE;
}


b8 application_on_event(u16 code, void* sender, void* listener_inst, EventContext context){
    switch(code){
        case EVENT_CODE_APPLICATION_QUIT: {
            FINFO("EVENT_CODE_APPLICATION_QUIT recieved, shutting down. \n");
            app_state.is_running = FALSE;
            return TRUE;
        }
    }

    return FALSE;
}

b8 application_on_keys(u16 code, void* sender, void* listener_inst, EventContext context){
    if(code == EVENT_CODE_KEY_PRESSED){
        u16 key_code = context.data.u16[0];
        if(key_code == KEY_ESCAPE){
            EventContext data = {};
            event_syst.fire_event(EVENT_CODE_APPLICATION_QUIT, 0, data);

            return TRUE;
        }else if(key_code == KEY_A){
            FDEBUG("Explicit - A key pressed!");
        }else{
            FDEBUG("'%c' key pressed in window.", key_code);
        }
    }else if(code == EVENT_CODE_KEY_RELEASED){
         u16 key_code = context.data.u16[0];
        if(key_code == KEY_B){
            FDEBUG("Explicit - B key relesase!");
        }else{
            FDEBUG("'%c' key released in window.", key_code);
        }
    }
    return FALSE;
}

