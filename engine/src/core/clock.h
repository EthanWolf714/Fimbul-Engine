#pragma once
#include "defines.h"

typedef struct clock{
    f64 start_time;
    f64 elapsed;
}clock;

//updatse the provided clock. shoudl be called before checking elapsed timne
//has no effect on non started clocks
void clock_update(clock* clock);

//starts provided clock. Resets elapsed time
void clock_start(clock* clock);

//stops clock, does not reset elapsed time
void clock_stop(clock* clock);