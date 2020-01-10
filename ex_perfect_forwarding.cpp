#include <iostream>
#include <string>
#include <assert.h>
#include "type_helper.hpp"

class Person {
public:
	template<
		typename T,
		typename = std::enable_if_t<
		!std::is_base_of_v<Person, std::decay_t<T>>
		&&
		!std::is_integral_v<std::remove_reference_t<T>>
		>
	>
	explicit Person(T&& name) {
		static_assert(std::is_constructible<std::string, T>::value, "Unavailable to construct an object into std::string.");
		std::cout << "Perfect Constructor: " << std::forward<T>(name) << std::endl;
	}

	explicit Person(int idx) {
		std::cout << "Constructor by an integer : " << idx << std::endl;
	}
};

int main() {
	std::string str = "Hello";
	auto x = Person(std::move(str)); // Perfect Constructor
	auto y = Person(std::move(x)); // Auto-constructed Move Constructor
	auto z = Person("hi"); // Perfect Constructor
}