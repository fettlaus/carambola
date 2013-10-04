/**
 * @file BlockingQueue.hpp
 * @date Jan 5, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

/**
 * Stores a single object of type D in the queue. This also notifies the pop() method if ot waits
 * for data.
 * @param data An object of type D
 */
template<typename D>
inline void freejtag::BlockingQueue<D>::push(const D& data) {
    boost::mutex::scoped_lock lock(mutex_);
    PRINT("Push to Queue");
    queue_.push(data);
    lock.unlock();
    cond_.notify_one();
}

/**
 * Checks queue for emptiness.
 * @return true if queue is empty
 */
template<typename D>
inline bool freejtag::BlockingQueue<D>::empty() const {
    boost::mutex::scoped_lock lock(mutex_);
    return queue_.empty();
}

/**
 * This function pops one element of type D. If the queue is empty, it locks until an element
 * is available.
 * @return The popped element
 */
template<typename D>
inline D freejtag::BlockingQueue<D>::pop() {
    boost::mutex::scoped_lock lock(mutex_);
    while(queue_.empty()){
        cond_.wait(lock);
    }
    D temp = queue_.front();
    queue_.pop();
    PRINT("Removed from Queue");
    return temp;
}