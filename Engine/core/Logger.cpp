#include "Engine/core/Logger.h"

static std::vector<std::string> s_logBuffer;

int Logger::VDebugPrintF(const char* format, va_list argList)
{

    const std::uint32_t MAX_CHARS = 1024;
    static char s_buffer[MAX_CHARS];
    //format string 
    int charsWritten = vsnprintf(s_buffer, MAX_CHARS, format, argList);

    //handles the formatting
    TraceLog(LOG_INFO, s_buffer);


    s_logBuffer.push_back(std::string(s_buffer));
    return charsWritten;
}


int Logger::DebugPrintF(const char* format, ...)
{
    va_list argList;

    va_start(argList, format);

    //uses VDebugPrint to format string 
    int charsWritten = VDebugPrintF(format, argList);

    va_end(argList);
    return charsWritten;
}

//returns log buffer for Log panel in editor
const std::vector<std::string>& Logger::GetLogBuffer()
{
    return s_logBuffer;
}