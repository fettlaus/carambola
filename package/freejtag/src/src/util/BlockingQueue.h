/*
 * MessageQueue.h
 *
 *  Created on: Jan 5, 2013
 *      Author: bachelor
 */


#ifndef MESSAGEQUEUE_H_
#define MESSAGEQUEUE_H_

#include "debug.h"

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <queue>


namespace freejtag {

/**
 * http://www.justsoftwaresolutions.co.uk/threading/implementing-a-thread-safe-queue-using-condition-variables.html
 */
template<typename D>
class BlockingQueue {
public:
	void push(D const& data);
	bool empty() const;
	D pop();
	//MessageQueue();
	//virtual ~MessageQueue();
private:
	mutable boost::mutex mutex_;
	std::queue<D> queue_;
	boost::condition_variable cond_;
};

} /* namespace freejtag */
#include "BlockingQueue.hpp"

#endif /* MESSAGEQUEUE_H_ */
