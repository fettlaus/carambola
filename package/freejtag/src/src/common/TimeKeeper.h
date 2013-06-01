/**
 * @file TimeKeeper.h
 * @date Feb 7, 2013
 * @author Arne Wischer<Fettlaus@gmail.com>
 */

#ifndef TIMEKEEPER_H_
#define TIMEKEEPER_H_

#include <boost/chrono.hpp>

namespace freejtag {
using namespace boost::chrono;

/**
 * This class is used to keep track of time measured in microseconds. It is implemented
 * as a singleton so that it can easily be used from anywhere. On startup the counter is
 * reset to zero and the counter can be adjusted by using TimeKeeper::set().
 */
class TimeKeeper {
public:
    static microseconds time();
    static void set(microseconds difference);
private:
    static high_resolution_clock::time_point epoch_; ///< Epoch in relation to time since program start
    // Don't implement these (Use this class as a singleton)
    TimeKeeper(); ///< Part of singleton
    virtual ~TimeKeeper(); ///< Part of singleton
    TimeKeeper(TimeKeeper const&); ///< Part of singleton
    void operator=(TimeKeeper const&); ///< Part of singleton
};

} /* namespace freejtag */
#endif /* TIMEKEEPER_H_ */
