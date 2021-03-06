/**
 * @file MessageQueue.hpp
 * @date Jan 5, 2013
 * @author Arne Wischer<Fettlaus@gmail.com>
 */

template<typename D>
inline void freejtag::BlockingQueue<D>::push(const D& data) {
    boost::mutex::scoped_lock lock(mutex_);
    PRINT("Push to Queue");
    queue_.push(data);
    lock.unlock();
    cond_.notify_one();
}

template<typename D>
inline bool freejtag::BlockingQueue<D>::empty() const {
    boost::mutex::scoped_lock lock(mutex_);
    return queue_.empty();
}

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
