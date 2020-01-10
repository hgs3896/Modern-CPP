#include <iostream>

template<typename T, typename Initializer = T>
class vector {
	T* container;
	std::size_t sz, cap;

public:
	vector() noexcept
		:container(new T[5]), sz(0), cap(5) {
		for (int i = 0; i < cap; ++i)
			container[i] = Initializer;
	}

	vector(std::initializer_list<T>&& arg) noexcept
		:container(new T[arg.size() * 2]), sz(arg.size()), cap(arg.size() * 2) {
		auto i = 0;
		for (auto it = arg.begin(); it != arg.end(); ++it)
			container[i++] = *it;
		for (; i < cap; ++i)
			container[i] = Initializer();
	}

	vector(const vector<T>& copy)
		:container(new T[copy.cap]), sz(copy.sz), cap(copy.cap) {
		for (int i = 0; i < sz; ++i)
			container[i] = copy.container[i];
	}

	vector(vector<T>&& original) noexcept
		:container(original.container), sz(original.sz), cap(original.cap) {
		original.sz = 0;
		original.cap = 0;
		original.container = nullptr;
	}

	const T& operator[](const int idx) const {
		if (idx < 0 || idx >= sz)
			throw std::exception("Index Out of Range");
		return container[idx];
	}

	T& operator[](const int idx) {
		return const_cast<T&>(const_cast<const vector<T>*>(this)->operator[](idx));
	}

	~vector() {
		delete[] container;
	}
};

template<typename Container, typename Index>
// decltype(auto) getItem(Container& container, Index idx) {
auto getItem(Container& container, Index idx) -> decltype(container[idx]) {
	return container[idx];
}

int main() {
	vector<int> x = {1, 2, 3};
	vector<int> y = std::move(x);
	std::cout << getItem(y, 2) << std::endl;
}