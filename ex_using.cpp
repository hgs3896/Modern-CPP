#include <list>

template<typename T>
class MyAlloc {

};

template<typename T>
using MyAllocList = std::list<T, MyAlloc<T>>;

template<typename T>
struct MyAllocList_ {
	typedef std::list<T, MyAlloc<T>> type;
};
template <typename T>
class Widget {
private:
	MyAllocList<T> x;
	// typename은 template 선언 내부에서 의존 타입이 실제 타입임을 나타내도록 한다.
	typename MyAllocList_<T>::type xx;
};

int main() {
	MyAllocList<int>;
	MyAllocList_<int>::type;
	Widget<int>;
	return 0;
}