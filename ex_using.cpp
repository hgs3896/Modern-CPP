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
	// typename�� template ���� ���ο��� ���� Ÿ���� ���� Ÿ������ ��Ÿ������ �Ѵ�.
	typename MyAllocList_<T>::type xx;
};

int main() {
	MyAllocList<int>;
	MyAllocList_<int>::type;
	Widget<int>;
	return 0;
}