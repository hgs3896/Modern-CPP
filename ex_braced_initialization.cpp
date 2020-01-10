#include <iostream>
#include <initializer_list>
#include <atomic>
#include "type_helper.hpp"
#include "selective_compile.hpp"

class Widget {
private:
	int x = 0;
	// int y(0); <- 이 형태는 non-static member의 초기화로도 사용 불가능 함
	int z{ 0 };
	int l = { 0 };
public:
	Widget() noexcept {
	}
	Widget(const Widget& copy) noexcept {
	}
	Widget(Widget&& copy) noexcept {
	}
	Widget& operator=(const Widget& copy) noexcept {
		return *this;
	}
	Widget&& operator=(Widget&& copy) noexcept {
		return std::move(*this);
	}
	Widget(int i, bool j) noexcept {
	}
	Widget(int i, double j) noexcept {
	}
	Widget(std::initializer_list<bool> item) noexcept{
	}
};

int main() {
	/* Modern C++에서 제공하는 4가지 형태의 초기화 구문 */
	COMPILE(true, {
		/* 1. 등호 형태 */
		int x = 0;
		/* 2. 생성자 형태 */
		int y(0);
		/* 3. [new] 중괄호 형태 */
		int z{ 0 };
		/* 4. [new] 등호 + 중괄호 형태 */
		int l = { 0 }; // 3과 동일함
	})

	/* 생성자(Constructor)와 대입 연산(Assignment)의 차이 */
	COMPILE(true, {
		Widget w1; // 생성자 호출
		Widget w2 = w1; // 복사 생성자 호출
		w1 = w2; // 대입 연산자 호출
	})

	/* 중괄호 초기화의 특징1 : Implicit Narrowing Conversion을 금지한다 */
	COMPILE(false, {
		double x = 0.0, y = 2.0, z = 3.0;
		int sum{ x + y + z };
	})

	/* 중괄호 초기화의 특징2: 가장 성가신 구문 해석(Most Vexing Parse) 문제로부터 자유롭다.
	 * 가장 성가신 구문 해석: 선언으로 해석할 수 있는 것은 선언으로 해석해야 한다. */
	COMPILE(true, {
		Widget w1; // 생성자
		Widget w2(); // 함수 선언
		Widget w3{}; // 생성자
		Widget w4{ {} }; // 빈 중괄호 쌍을 std::initializer_list<bool>로 받음
	})

	/* 중괄호 초기화의 특징3: 오버로딩된 함수의 시그니처 중 하나 이상이 std::initializer_list<T>형식을 받는다면
	 * 해당 버전을 강하게 선호한다. */
	
	// Widget w2{ 10, true };
	
	{
		Widget w1(10, true);
		// 10 -> true로 바꾸는 것은 좁히기 변환이므로 허용되지 않음
		// Widget w2{ 10, true };
		Widget w3( 10, 5.0 ); 
		// 5.0 -> 5로 바꾸는 것은 좁히기 변환이므로 허용되지 않음
		// Widget w4{ 10, 5.0 };
	}

}