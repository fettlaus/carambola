/**
 * @file TimeKeeper.h
 * @date Feb 7, 2013
 * @author Arne Wischer<Fettlaus@gmail.com>
 */

#ifndef TIMEKEEPER_H_
#define TIMEKEEPER_H_

//#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/chrono.hpp>

namespace freejtag {
using namespace boost::chrono;
/**
 *
 */
class TimeKeeper {
public:
    static microseconds time();
    static void set(microseconds difference);
    void timer();
private:
    static high_resolution_clock::time_point epoch;
    // Don't implement these
    TimeKeeper();
    virtual ~TimeKeeper();
    TimeKeeper(TimeKeeper const&);
    void operator=(TimeKeeper const&);
};

} /* namespace freejtag */
#endif /* TIMEKEEPER_H_ */
