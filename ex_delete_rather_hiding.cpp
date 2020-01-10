#include <memory>

class W {
public:
	friend int main();
	template<typename T>
	void processPointer(T* ptr) {}
	W() {}
private:
	// C++98 스타일 함수 지우기	
	W(const W&); // private으로 숨기고
	W& operator=(const W&); // 정의하지 않음

	template<>
	void processPointer<void>(void*);
};

class WW {
public:
	// C++11 스타일 함수 지우기
	WW() {};
	WW(const WW&) = delete;
	WW& operator=(const WW&) = delete;
	template<typename T>
	void processPointer(T* ptr) {}
	template<>
	void processPointer<void>(void* ptr) = delete;
};

// 밖에서도 지울 수 있음
// template<> void WW::processPointer<WW>(WW* ptr) = delete;

int main() {
	// 예외
	W x;
	// x.processPointer(&x);
	WW y;
	y.processPointer(&y);	
}