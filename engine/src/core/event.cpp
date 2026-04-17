#include "core/event.h"

event event_syst;



b8 event::initialize() {
    if(is_initialized == TRUE){
        return FALSE;
    }

    is_initialized = TRUE;
    return TRUE;
}


void event::shutdown(){
    registery.clear();
    is_initialized = false;
}

b8 event::register_event(u16 code,void* listener, EventCallback callback){
    
    if(is_initialized == FALSE){
        return FALSE;
    }

    auto& vec = registery[code];

    // prevent duplicate registration
    for (const auto& e : vec) {
        if (e.listener == listener) {
            return FALSE;
        }
    }
    

    vec.push_back({listener, callback});

    return TRUE;


}


b8 event::unregister_event(u16 code, void* listener){
    if (!is_initialized) return FALSE;

 
    auto& vec = registery[code];
    for(auto i = vec.begin(); i != vec.end(); ++i){
        if(i->listener == listener){
            vec.erase(i);
            return TRUE;
        }
    }
    
    return FALSE;
}

b8 event::fire_event(u16 code, void* sender, EventContext context){
    auto it = registery.find(code);
    if(it == registery.end()) return FALSE;

    auto listeners = it->second;
    for(auto& e: listeners){
        if(e.callback(code, sender, context)){
            return TRUE; //handled
        }
    }

    return FALSE;
}

