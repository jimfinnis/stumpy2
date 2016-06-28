/**
 * @file
 * A timer device, for providing frame ticks and also real time data.
 * It's a singleton called gTimerDevice
 * 
 * 
 */

#ifndef __TIMER_H
#define __TIMER_H

#include <stdint.h>
#include "errors.h"
#include "util/exception.h"

class TimerDevice {
    
public:
    TimerDevice(){
        ticks=0;
    }

    
    /// return frames since the start of the app
    uint32_t getTicks(){
        return ticks;
    }
    
    
    /// return the number of seconds since the start of the app
    float getRunTime(){
        throw Exception("getRunTime() not yet implemented");
    }
    
    /// this must be run every frame
    void tick(){
        ticks++;
    }
    
private:
    int ticks;
};

extern TimerDevice gTimerDevice;


#endif /* __TIMER_H */
