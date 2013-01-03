template <typename P> const P freejtag::settings::get_value(const char* val) const{
	const std::string str(val);
	return map[val].as<P>();
}
