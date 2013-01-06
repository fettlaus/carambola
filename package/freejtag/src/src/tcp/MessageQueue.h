/*
 * MessageQueue.h
 *
 *  Created on: Jan 5, 2013
 *      Author: bachelor
 */

#ifndef MESSAGEQUEUE_H_
#define MESSAGEQUEUE_H_

#include <queue>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

namespace freejtag {


template<typename D>
class MessageQueue {
public:
	void push(D const& data);
	bool empty() const;
	void pop(D& data);
	//MessageQueue();
	//virtual ~MessageQueue();
private:
	mutable boost::mutex mutex;
	std::queue<D> queue;
	boost::condition_variable cond;
};

} /* namespace freejtag */
#include "MessageQueue.hpp"

#endif /* MESSAGEQUEUE_H_ */
