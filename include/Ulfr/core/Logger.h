#pragma once

#include "raylib.h"
#include <cstdint>
#include <cstdio>
#include <cstdarg>
#include <vector>
#include <string>



class Logger
{
    public:
        static int VDebugPrintF(const char* format, va_list argList);
        static int DebugPrintF(const char* format, ...);
        static const std::vector<std::string>& GetLogBuffer();

   
       
        
};
