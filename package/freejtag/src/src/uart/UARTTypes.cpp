/**
 * @file UARTTypes.cpp
 * @date Jan 11, 2013
 * @author Arne Wischer<Fettlaus@gmail.com>
 */

#include "UARTTypes.h"
#include <debug.h>
#include <boost/program_options.hpp>

namespace freejtag {
namespace uart{


parity::parity(type t):serial_port_base::parity(t) {
}

flow_control::flow_control(type t):serial_port_base::flow_control(t) {
}

stop_bits::stop_bits(type t):serial_port_base::stop_bits(t) {
}

void validate(boost::any& v,
        const std::vector<std::string>& val, parity* type, int int1) {
    using namespace freejtag;
    using namespace boost::program_options;
    validators::check_first_occurrence(v);
    const std::string& s = validators::get_single_string(val);
    PRINT("Validate parity");
    if(s == "none"){
        v = boost::any(parity(parity::none));
    }else if (s == "odd"){
        v = boost::any(parity(parity::odd));
    }else if(s == "even"){
        v = boost::any(parity(parity::even));
    }else{
        throw validation_error(validation_error::invalid_option_value);
    }
}

void validate(boost::any& v, const std::vector<std::string>& val,
        flow_control* type, int int1) {
    using namespace freejtag;
    using namespace boost::program_options;
    validators::check_first_occurrence(v);
    const std::string& s = validators::get_single_string(val);
    PRINT("Validate flow_control");
    if(s == "none"){
        v = boost::any(flow_control(flow_control::none));
    }else if(s == "software"){
        v = boost::any(flow_control(flow_control::software));
    }else if(s == "hardware"){
        v = boost::any(flow_control(flow_control::hardware));
    }else{
        throw validation_error(validation_error::invalid_option_value);
    }
}

void validate(boost::any& v, const std::vector<std::string>& val,
        stop_bits* type, int int1) {
    using namespace freejtag;
    using namespace boost::program_options;
    validators::check_first_occurrence(v);
    const std::string& s = validators::get_single_string(val);
    PRINT("Validate stop_bits");
    if(s == "one"){
        v = boost::any(stop_bits(stop_bits::one));
    }else if(s == "onepointfive"){
        v = boost::any(stop_bits(stop_bits::onepointfive));
    }else if(s == "two"){
        v = boost::any(stop_bits(stop_bits::two));
    }else{
        throw validation_error(validation_error::invalid_option_value);
    }
}

} /* namespace freejtag */

} /* namespace uart */

