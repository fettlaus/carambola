/*
 * UARTTypes.h
 *
 *  Created on: Jan 11, 2013
 *      Author: bachelor
 */

#ifndef UARTTYPES_H_
#define UARTTYPES_H_

#include <boost/asio/serial_port_base.hpp>
#include <boost/any.hpp>
#include <vector>

namespace freejtag {
namespace uart {


using namespace boost::asio;
/**
 * none, odd, even
 */
struct parity:public serial_port_base::parity{
	parity(type t = none);
};


using namespace boost::asio;
/**
 * none, software, hardware
 */
struct flow_control:public serial_port_base::flow_control{
	flow_control(type t = none);
};


using namespace boost::asio;
/**
 * one, onepointfive, two
 */
struct stop_bits:public serial_port_base::stop_bits{
	stop_bits(type t = one);
};

void validate(boost::any& v,const std::vector<std::string>& val,parity* type,int);
void validate(boost::any& v,const std::vector<std::string>& val,flow_control* type,int);
void validate(boost::any& v,const std::vector<std::string>& val,stop_bits* type,int);


} /* namespace uart */
/*
* boost::asio::serial_port_base::flow_control @n
* boost::asio::serial_port_base::stop_bits @n
*/

} /* namespace freejtag */
#endif /* UARTTYPES_H_ */
