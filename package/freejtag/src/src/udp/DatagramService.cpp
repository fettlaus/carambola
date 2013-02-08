/**
 * @file DatagramService.cpp
 * @date Feb 7, 2013
 * @author Arne Wischer<Fettlaus@gmail.com>
 */

#include "DatagramService.h"
#include <common/TimeKeeper.h>

namespace freejtag {

DatagramService::DatagramService(boost::asio::io_service& io_service, settings& settings) {
    ///< @todo Auto-generated constructor stub
    TimeKeeper::time();

}

DatagramService::~DatagramService() {
    ///<  @todo Auto-generated destructor stub
}

} /* namespace freejtag */
