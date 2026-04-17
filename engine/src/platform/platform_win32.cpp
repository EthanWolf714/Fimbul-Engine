#include "platform/platform.h"

//Windows layer
#if FPLATFORM_WINDOWS
#include <stdlib.h>
#include "core/logger.h"
#include "core/input.h"

#include <windows.h>
#include <windowsx.h> //param input extractions

typedef struct internal_state{
    HINSTANCE h_instance;
    HWND hwnd; //window handle
}internal_state;

//Clock
static f64 clock_frequency; 
static LARGE_INTEGER start_time;

LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM w_parm, LPARAM l_param);

b8 platform_startup(
    platform_state* plat_state,
    const char* application_name,
    i32 x,
    i32 y,
    i32 width,
    i32 height){


    //allocate memory for state, create the internal state the size of the internal state?
    plat_state->internal_state = malloc(sizeof(internal_state));
    //cold cast, how we handle void pointer types
    internal_state *state = (internal_state *)plat_state->internal_state;

    state->h_instance = GetModuleHandleA(0);

    //setup and register window class
    HICON icon = LoadIcon(state->h_instance, IDI_APPLICATION);
    WNDCLASS wc;
    memset(&wc, 0, sizeof(wc));
    wc.style = CS_DBLCLKS; // get double clicks
    //window procedure, this handles events in the system
    wc.lpfnWndProc = win32_process_message;
    wc.cbClsExtra = 0;
    //points to h_instatnce
    wc.hInstance = state->h_instance;
    wc.hIcon = icon;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); //NULL, manage cursor manually
    wc.hbrBackground = NULL;  //transparent
    wc.lpszClassName = "fimbul_window_class";

    if(!RegisterClassA(&wc)){
        MessageBoxA(0, "window registration failed", "Error", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    //create window
    u32 client_x = x;
    u32 client_y = y;
    u32 client_width = width;
    u32 client_height = height;
    
    //intially setting window to client area size
    //gonna modifie the client values for window area
    u32 window_x = client_x;
    u32 window_y = client_y;
    u32 window_width = client_width;
    u32 window_height = client_height;

    u32 window_style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
    u32 window_ex_style = WS_EX_APPWINDOW;

    //describe how window looks
    window_style |= WS_MAXIMIZEBOX;
    window_style |= WS_MINIMIZEBOX;
    window_style |= WS_THICKFRAME;

    //obtain the size of the border
    RECT border_rect = {0,0,0,0};
    AdjustWindowRectEx(&border_rect, window_style, 0, window_ex_style);

    //in this case the border rectangle is negatice
    window_x += border_rect.left;
    window_y += border_rect.top;

    //Grow by the size of the OS border
    window_width += border_rect.right - border_rect.left;
    window_height += border_rect.bottom - border_rect.top;

    HWND handle = CreateWindowEx(
        window_ex_style, "Fimbul_window_class", application_name,
        window_style, window_x, window_y, window_width, window_height,
        0,0, state->h_instance, 0);

    if(handle == 0){
        MessageBoxA(NULL,"window creation failed: ", "Error!", MB_ICONEXCLAMATION | MB_OK);

        FFATAL("Window create failed!");
        return FALSE;
    }else {
        state->hwnd = handle;
    }

    //show the window
    b32 should_activate = 1; //TODO: if the window should not accept input, this should be false
    i32 show_window_command_flags = should_activate ? SW_SHOW : SW_SHOWNOACTIVATE;
    //if initially minimized, use sw_minimize : SW_SHOWMINNOACTVE
    //if initially maximized, use SW_SHOWMAXIMIZED : SW_MAXIMIZE
    ShowWindow(state->hwnd, show_window_command_flags);

    //clock setup
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    clock_frequency = 1.0 / (f64)frequency.QuadPart;
    QueryPerformanceCounter(&start_time);

    return TRUE;
}
void platform_shutdown(platform_state* plat_state)
{
    //simply cold cast to the known type
    internal_state *state = (internal_state *)plat_state->internal_state;

    if(state->hwnd){
        DestroyWindow(state->hwnd);
        state->hwnd = 0;
    }
}


b8 platform_pump_message(platform_state* plat_state){
    MSG message;
    //pop message on stack
    while(PeekMessageA(&message, NULL, 0,0,PM_REMOVE)){
        TranslateMessage(&message);
        DispatchMessageA(&message);
    }
    return true;
}


void* platform_allocator(u64 size, b8 alligned){
    return malloc(size);
}
void platform_free(void* block, b8 aligned){
    free(block);
}
void* platform_zero_memory(void* block, u64 size){
    return memset(block, 0, size);
}
void* platform_copy_memory(void* dest, const void* source, u64 size){
    return memcpy(dest, source, size);
}
void* platform_set_memory(void* dest, i32 value, u64 size){
    return memset(dest, value, size);
}

void platform_console_write(const char* message, u8 colour){
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //Fatal, error , warn, info, debug, trace
    static u8 levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[colour]);

    OutputDebugStringA(message);
    u64 length = strlen(message);
    LPDWORD number_written = 0;
    WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, (DWORD)length, number_written,0);
}
void platform_console_write_error(const char* message, u8 colour){
    HANDLE console_handle = GetStdHandle(STD_ERROR_HANDLE);
    //Fatal, error , warn, info, debug, trace
    static u8 levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[colour]);

    OutputDebugStringA(message);
    u64 length = strlen(message);
    LPDWORD number_written = 0;
    WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message, (DWORD)length, number_written,0);
}


f64 platform_get_absolute_time(){
    LARGE_INTEGER now_time;
    QueryPerformanceCounter(&now_time);
    return (f64)now_time.QuadPart * clock_frequency;
}

void platform_sleep(u64 ms){
    Sleep(ms);
}

LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param){
    switch (msg)
    {
        case WM_ERASEBKGND:
            // notify os that erasing will be handled by the applicatiuon to prevent flicker
            return 1;
        case WM_CLOSE:
            //TODO: Fire an event for the applciation to close
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_SIZE: {
            //get updated size
            // RECT r;
            // GetClientRect(hwnd, &r);
            // u32 width = r.right - r.left;
            // u32 height = r.bottom - r.top

            //TODO: fire off even for window resize;
        }break;
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP: {
            //key pressed/released
            b8 pressed = (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN);
            keys key = static_cast<keys>(w_param);

            //pass to input for processing
            input_process_key(key, pressed);

        }break;
        case WM_MOUSEMOVE: {
            //mouse move
            i32 x_position = GET_X_LPARAM(l_param);
            i32 y_position = GET_Y_LPARAM(l_param);
            //input processing
            input_process_mouse_move(x_position,y_position);

        }break; 
        case WM_MOUSEWHEEL: {
            i32 z_delta = GET_WHEEL_DELTA_WPARAM(w_param);
            if(z_delta != 0){
                //flatteen the input to an os indepented {-1,1}
                 z_delta = (z_delta < 0) ? -1 : 1;
                 input_process_mouse_wheel(z_delta);
            }
        }break;
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP:{
            b8 pressed = msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_MBUTTONDOWN;
            buttons mouse_button = BUTTON_MAX_BUTTONS;
            switch(msg) {
                case WM_LBUTTONDOWN:
                case WM_LBUTTONUP:
                    mouse_button = BUTTON_LEFT;
                    break;
                case WM_MBUTTONDOWN:
                case WM_MBUTTONUP:
                    mouse_button = BUTTON_MIDDLE;
                    break;
                case WM_RBUTTONDOWN:
                case WM_RBUTTONUP:
                    mouse_button = BUTTON_RIGHT;
                    break;
            }

            //pass to input system
            if(mouse_button != BUTTON_MAX_BUTTONS){
                input_process_button(mouse_button, pressed);
            }
        }break;

    }

    return DefWindowProc(hwnd, msg, w_param, l_param);
}    
#endif// FPLATFORM WINDOWS