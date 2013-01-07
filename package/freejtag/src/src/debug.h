/*
 * debug.h
 *
 *  Created on: Jan 7, 2013
 *      Author: bachelor
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <boost/date_time/posix_time/posix_time.hpp>
#include <ostream>

#ifdef DEBUG
#define PRINT(...) {DPRINT() << __VA_ARGS__;}
class DPRINT {
public:
    explicit DPRINT(){
    	ss << boost::posix_time::to_iso_string(boost::posix_time::microsec_clock::local_time());
    	ss << ": ";
    }
    ~DPRINT() {
    	ss << std::endl;
        std::cout << ss.str() << std::flush; // write the whole shebang in one go
    }
    template <typename T>
    DPRINT& operator<<(T const& t) {
        ss << t;
        return *this;
    }
private:
    std::stringstream ss;
};

#else
#define PRINT(...)
#endif

#endif /* DEBUG_H_ */
