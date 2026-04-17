#pragma once
#include "core/application.h"
#include "core/logger.h"
#include "core/fmemory.h"

#include "game_types.h"

//externally defined function to create game
extern b8 create_game(game* out_game);


application app;
/*
    main entry point of app
*/
int main(void)
{  
    
    
   
    game game_inst;

    if(!create_game(&game_inst)){
        FFATAL("Could not create game!");
        return -1;
    }

    //ensure function pointers exist
    if(!game_inst.render || !game_inst.update || !game_inst.initialize || !game_inst.on_resize){
        FFATAL("The games function pointers must be assigned!");
        return -2;
    }

    
   
    
    if(!app.application_create(&game_inst)){
        FINFO("Application failed to create!\n");
        return 1;
    }
    //begin game loop!
    if(!app.application_run()){
        FINFO("Applicationg failed to deactivate systems!\n");
        return 2;
    }

    memory.shutdown_memeory();

    
    return 0;
}