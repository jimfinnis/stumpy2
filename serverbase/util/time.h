/**
 * @file time.h
 * @brief  Brief description of file.
 *
 */

#ifndef __UTIME_H
#define __UTIME_H

namespace Time {
void init();
double now(); // takes pause()/restart() into account
double realnow(); // disregarding pauses
void pause();
void restart();
uint32_t ticks();
void tick();
};

#endif /* __UTIME_H */
