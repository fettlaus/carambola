/**
 * @file TimeKeeper.cpp
 * @date Feb 7, 2013
 * @author Arne Wischer<Fettlaus@gmail.com>
 */

#include "TimeKeeper.h"

#include <debug.h>

namespace freejtag {
high_resolution_clock::time_point TimeKeeper::epoch_(high_resolution_clock::now());

microseconds TimeKeeper::time(){
    high_resolution_clock::duration now = high_resolution_clock::now() - epoch_;
    return duration_cast<microseconds>(now);
}

void TimeKeeper::set(microseconds difference){
    epoch_ = epoch_ + difference;
    PRINT("Corrected time by " << difference);
}

} /* namespace freejtag */
