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

class TimeKeeper {
public:
    static microseconds time();
    static void set(microseconds difference);
    void timer();
private:
    static high_resolution_clock::time_point epoch_;
    // Don't implement these (Use this class as a singleton)
    TimeKeeper(); ///< Part of singleton
    virtual ~TimeKeeper(); ///< Part of singleton
    TimeKeeper(TimeKeeper const&); ///< Part of singleton
    void operator=(TimeKeeper const&); ///< Part of singleton
};

} /* namespace freejtag */
#endif /* TIMEKEEPER_H_ */
