/*
 * UARTService.h
 *
 *  Created on: Jan 11, 2013
 *      Author: bachelor
 */

#ifndef UARTSERVICE_H_
#define UARTSERVICE_H_

#include "UARTConnection.h"
#include "../util/BlockingQueue.h"
#include "../settings.h"
#include <boost/thread.hpp>

namespace freejtag {

class UARTConnection;
typedef std::pair<uint32_t,std::string> UARTMessage;
class UARTService {
public:
	UARTService(boost::asio::io_service& io_service, settings& settings);
	virtual ~UARTService();
	std::string get_line();
private:
	void reload_settings();
	settings& settings_;
	boost::asio::io_service& io_service_;
	bool shutdown_;
	void read_line();
	BlockingQueue<UARTMessage> uart_buffer_;
	boost::thread uart_thread_;
	UARTConnection* uart_connection_;
};

} /* namespace freejtag */
#endif /* UARTSERVICE_H_ */
