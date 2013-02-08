/**
 * @file DatagramService.h
 * @date Feb 7, 2013
 * @author Arne Wischer<Fettlaus@gmail.com>
 */

#ifndef DATAGRAMSERVICE_H_
#define DATAGRAMSERVICE_H_

#include <boost/asio/io_service.hpp>
#include <settings.h>

namespace freejtag {

/**
 *
 */
class DatagramService {
public:
    DatagramService(boost::asio::io_service& io_service, settings& settings);
    virtual ~DatagramService();
};

} /* namespace freejtag */
#endif /* DATAGRAMSERVICE_H_ */
