#pragma once
#include <iostream>
#include <boost/type_index.hpp>

template<typename T>
auto printTypeInfo(const char* explanation) noexcept
{
	using boost::typeindex::type_id_with_cvr;
	std::cout << explanation << ": " << type_id_with_cvr<T>().pretty_name() << std::endl;
}