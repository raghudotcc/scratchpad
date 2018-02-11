/* overloaded_ostream.cc
 * util methods to ease logging of stl data structures to output stream
 * works only when template paramter is a primitive type
 * you may not need all of them, you just need whichever ds you
 * are implementing from the standard template library
 */

template <typename T>
std::ostream & operator<< (std::ostream& out, const std::vector<T> &out_vector)
{
	auto vector_iterator = out_vector.begin();
	for (;vector_iterator != out_vector.end(); ++vector_iterator) {
		out << (*vector_iterator) << std::endl;
	}
}

template <typename T1, typename T2>
std::ostream & operator<< (std::ostream& out, const std::pair<T1, T2> &out_pair)
{
	out << out_pair.first << ", " << out_pair.second << std::endl;
}

template <typename T1, typename T2>
std::ostream & operator<< (std::ostream& out, const std::map<T1, T2> &out_map)
{
	auto map_iterator = out_map.begin();
	for (;map_iterator != out_map.end(); ++map_iterator) {
		out << map_iterator->first << ", " << map_iterator->second << std::endl;
	}
}

template <typename T1, typename T2>
std::ostream & operator<< (std::ostream& out, const std::unordered_map<T1, T2> &out_unordered_map)
{
	auto map_iterator = out_unordered_map.begin();
	for (;map_iterator != out_unordered_map.end(); ++map_iterator) {
		out << map_iterator->first << ", " << map_iterator->second << std::endl;
	}
}

template <typename T>
std::ostream & operator<< (std::ostream& out, const std::set<T> &out_set)
{
	auto set_iterator = out_set.begin();
	for (;set_iterator != out_set.end(); ++set_iterator) {
		out << (*set_iterator) << std::endl;
	}
}

template <typename T>
std::ostream & operator<< (std::ostream& out, const std::unordered_set<T> &out_unordered_set)
{
	auto set_iterator = out_unordered_set.begin();
	for (;set_iterator != out_unordered_set.end(); ++set_iterator) {
		out << (*set_iterator) << std::endl;
	}
}
