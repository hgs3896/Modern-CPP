#include <boost/timer/timer.hpp>
#include <vector>
#include <atomic>
#include <iostream>

template<typename T, size_t N>
void swap(T(&a)[N], T(&b)[N]) noexcept(noexcept(swap(*a, *b))) {
	for (auto i = 0; i < N; ++i) {
		T&& c = std::move(a[i]);
		a[i] = std::move(b[i]);
		b[i] = std::move(c);
	}	
}

template<typename T>
class Item {
public:
	Item(T n) noexcept : n(n) {};
	Item(const Item<T>&)noexcept = default;
	Item(Item<T>&&)noexcept = default;
	Item<T>& operator=(const Item<T>&) noexcept = default;
	
	~Item() noexcept = default;
private:
	T n;
};

template<typename T>
class Item2 {
public:
	Item2(T n) :n(n) { }
	Item2(const Item2<T>&) = default;
	Item2(Item2<T>&&) = default;
	Item2<T>& operator=(const Item2<T>&) = default;

	~Item2() = default;
private:
	T n;
};

using ItemType = int;

template <typename Type>
void f() noexcept {
	std::vector<Type> v;
	for (auto n = 1000000; n > 0; --n)
		v.push_back(n);
}

template <typename Type>
void g() throw() {
	std::vector<Type> v;
	for (auto n = 1000000; n > 0; --n)
		v.push_back(n);
}

template <typename Type>
void h(){
	std::vector<Type> v;
	for (auto n = 1000000; n > 0; --n)
		v.push_back(n);
}

int main() {
	
	{
		boost::timer::auto_cpu_timer t;
		f<Item<ItemType>>();
	}

	{
		boost::timer::auto_cpu_timer t;
		g<Item<ItemType>>();
	}

	{
		boost::timer::auto_cpu_timer t;
		h<Item<ItemType>>();
	}

	{
		boost::timer::auto_cpu_timer t;
		f<Item2<ItemType>>();
	}

	{
		boost::timer::auto_cpu_timer t;
		g<Item2<ItemType>>();
	}

	{
		boost::timer::auto_cpu_timer t;
		h<Item2<ItemType>>();
	}

	
	{
		std::vector<int> arr{ 0, 1, 5, 302, 2, 3, 5, 6 };
		std::vector<int> arr2{ 0, 1, 5, 102, 2, 3, 5, 6 };
		{
			boost::timer::auto_cpu_timer t;
			swap(arr, arr2);
		}

		{
			boost::timer::auto_cpu_timer t;
			std::swap(arr, arr2);
		}
	}
	
	return 0;
}