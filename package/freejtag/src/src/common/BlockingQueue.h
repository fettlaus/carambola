/**
 * @file BlockingQueue.h
 * @date Jan 5, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#ifndef MESSAGEQUEUE_H_
#define MESSAGEQUEUE_H_

#include <debug.h>

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <queue>

namespace freejtag {

/**
 * A templated blocking queue.
 * This FIFO queue uses a mutex to coordinate access to the data. All methods of this class
 * are synchronized.
 *
 * http://www.justsoftwaresolutions.co.uk/threading/implementing-a-thread-safe-queue-using-condition-variables.html
 */
template<typename D>
class BlockingQueue {
public:
    void push(D const& data);
    bool empty() const;
    D pop();
private:
    mutable boost::mutex mutex_; ///< The mutex to protect access
    std::queue<D> queue_; ///< The internal queue
    boost::condition_variable cond_; ///< Condition variable used with the mutex
};

} /* namespace freejtag */
#include "BlockingQueue.hpp"

#endif /* MESSAGEQUEUE_H_ */
