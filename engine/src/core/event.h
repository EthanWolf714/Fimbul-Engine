#pragma once


#include "defines.h"
#include <functional>
#include "core/fmemory.h"
#include <unordered_map>
#include <vector>



 
// event data passed to every callback
struct EventContext {
      union {
        i64 i64[2];
        u64 u64[2];
        f64 f64[2];

        i32 i32[4];
        u32 u32[4];
        f32 f32[4];

        i16 i16[8];
        u16 u16[8];

        i8 i8[16];
        u8 u8[16];

        char c[16];
    } data;
};

//returns true if handled
using EventCallback = std::function<bool(u16 code, void* sender,void* listener, EventContext data)>;

//one registerd listener
struct RegisteredEvent {
    //use handle for unregistering
    void* listener;
    EventCallback callback;
};



class event {       
    public:
    b8 initialize();
    void shutdown();

    FAPI b8 register_event(u16 code,void* listener, EventCallback callback);
    FAPI b8 unregister_event(u16 code,void* listener);
    FAPI b8 fire_event(u16 code, void* sender, EventContext context);
    

    private:
        std::unordered_map<u16, std::vector<RegisteredEvent>> registery;
        b8 is_initialized = FALSE;
    
 


};


typedef enum system_event_code {
    // Shuts the application down on the next frame.
    EVENT_CODE_APPLICATION_QUIT = 0x01,

    // Keyboard key pressed.
    /* Context usage:
     * u16 key_code = data.data.u16[0];
     */
    EVENT_CODE_KEY_PRESSED = 0x02,

    // Keyboard key released.
    /* Context usage:
     * u16 key_code = data.data.u16[0];
     */
    EVENT_CODE_KEY_RELEASED = 0x03,

    // Mouse button pressed.
    /* Context usage:
     * u16 button = data.data.u16[0];
     */
    EVENT_CODE_BUTTON_PRESSED = 0x04,

    // Mouse button released.
    /* Context usage:
     * u16 button = data.data.u16[0];
     */
    EVENT_CODE_BUTTON_RELEASED = 0x05,

    // Mouse moved.
    /* Context usage:
     * u16 x = data.data.u16[0];
     * u16 y = data.data.u16[1];
     */
    EVENT_CODE_MOUSE_MOVED = 0x06,

    // Mouse moved.
    /* Context usage:
     * u8 z_delta = data.data.u8[0];
     */
    EVENT_CODE_MOUSE_WHEEL = 0x07,

    // Resized/resolution changed from the OS.
    /* Context usage:
     * u16 width = data.data.u16[0];
     * u16 height = data.data.u16[1];
     */
    EVENT_CODE_RESIZED = 0x08,

    MAX_EVENT_CODE = 0xFF
}system_event_code;

extern FAPI event event_syst;

