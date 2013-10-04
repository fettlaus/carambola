/**
 * @file debug.h
 * @date Jan 7, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <boost/date_time/posix_time/posix_time.hpp>
#include <ostream>

/**
 * Log a warning to stderr.
 * This macro prints a message to stderr. In opposite to PRINT(), this macro
 * is even enabled if DEBUG is not defined.
 * @see DPRINT
 *
 */
#define WARNING(...) {DPRINT(std::cerr) << __VA_ARGS__;}

/**
 * Log a message to stdout.
 * This macro utilizes DPRINT to print the message to stdout. It is
 * @see DPRINT
 * @pre DEBUG needs to be defined. Can be done by adding -DDEBUG to the compiler flags.
 */
#ifdef DEBUG
#define PRINT(...) {DPRINT(std::cout) << __VA_ARGS__;}
#else
#define PRINT(...)
#endif
/**
 *
 * Class to handle printing to a std::ostream.
 * This class takes a std::ostream to which output can be passed by using the \c operator<<.
 *
 * This results in calls like
 * \code DPRINT(std::cout) << "Hello" << "world";\endcode
 * A timestamp will be prepended once the constructor of this class gets called.
 * This function is usually wrapped by a call to PRINT or WARNING. All calls to this class are
 * inherently synchronized if C++11 or another threadsafe version of cout is used.
 *
 * @see WARNING PRINT
 * @see http://stackoverflow.com/questions/9527127/thread-safe-cout-technique-am-i-missing-something
 */
class DPRINT {
public:
	/**
	 * Creates a new instance and prepends the current timestamp.
	 * @param str target ostream
	 */
    explicit DPRINT(std::ostream& str):stream_(str),
    f(new boost::posix_time::time_facet("%H:%M:%S%F")){
        ss_.imbue(std::locale(ss_.getloc(),f));
        ss_ << boost::posix_time::microsec_clock::local_time();
    	ss_ << ": ";
    }

    /**
     * Flushes log message if instance gets deleted.
     * This destructor automatically appends an endline and flushes the complete
     * log message to the specified std::ostream.
     */
    ~DPRINT() {
    	ss_ << std::endl;
        stream_ << ss_.str() << std::flush; //flush string once object gets destroyed
    }

    /**
     * Operator used to append strings to the instance.
     *
     * @param t A new string to append
     * @return This instance
     */
    template <typename T>
    DPRINT& operator<<(T const& t) {
        ss_ << t;
        return *this;
    }
private:
    std::ostream& stream_; ///< Target std::ostream
    std::stringstream ss_; ///< Buffer for log message
    boost::posix_time::time_facet*const f; ///< Time facet used for the timestamp
};

#endif /* DEBUG_H_ */
