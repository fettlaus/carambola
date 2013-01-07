/*
 * MessageQueue.hpp
 *
 *  Created on: Jan 5, 2013
 *      Author: bachelor
 */

template<typename D>
inline void freejtag::MessageQueue<D>::push(const D& data) {
	boost::mutex::scoped_lock lock(mutex_);
	PRINT("Push to Queue");
	queue_.push(data);
	lock.unlock();
	cond_.notify_one();
}

template<typename D>
inline bool freejtag::MessageQueue<D>::empty() const {
	boost::mutex::scoped_lock lock(mutex_);
	return queue_.empty();
}

template<typename D>
inline void freejtag::MessageQueue<D>::pop(D& data) {
	boost::mutex::scoped_lock lock(mutex_);
	while(queue_.empty()){
		cond_.wait(lock);
	}
	data = queue_.front();
	queue_.pop();
}

