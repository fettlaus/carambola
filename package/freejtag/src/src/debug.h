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


#define WARNING(...) {DPRINT(std::cerr) << __VA_ARGS__;}
#ifdef DEBUG
#define PRINT(...) {DPRINT(std::cout) << __VA_ARGS__;}
#else
#define PRINT(...)
#endif
/**
 * http://stackoverflow.com/questions/9527127/thread-safe-cout-technique-am-i-missing-something
 */
class DPRINT {
public:
    explicit DPRINT(std::ostream& str):stream_(str){
    	ss_ << boost::posix_time::to_iso_string(boost::posix_time::microsec_clock::local_time());
    	ss_ << ": ";
    }
    ~DPRINT() {
    	ss_ << std::endl;
        stream_ << ss_.str() << std::flush; // write the whole shebang in one go
    }
    template <typename T>
    DPRINT& operator<<(T const& t) {
        ss_ << t;
        return *this;
    }
private:
    std::ostream& stream_;
    std::stringstream ss_;
};



#endif /* DEBUG_H_ */
