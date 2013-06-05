/**
 * @file settings.hpp
 * @date Dec 25, 2012
 * @author Arne Wischer <Fettlaus@gmail.com>
 */
template <typename P> const P freejtag::settings::get_value(const char* val) const{
    const std::string str(val);
    return map[val].as<P>();
}
