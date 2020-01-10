#include <iostream>
#include <initializer_list>
#include "type_helper.hpp"

/* Declaration
 *
 * template<typename T>
 * void f(ParamType param);
 *
 * f(expr);
 *
 * 컴파일러는 expr를 통해서 두가지 타입(T, ParamType)을 추론한다.
 * 일반적으로 T와 ParamType은 여러 한정사(const, &, &&[reference qualifier])에의해
 * 다른 경우가 많다.
 * 
 * 1. expr을 통해 ParamType에 달린 한정사들을 떼어내면서 T를 추론한다.
 * 2. ParamType에 T를 대입하여 ParamType을 추론한다.
 *
 * 예외: 배열이나 함수 이름은
 * 값으로 전달되면 포인터로 붕괴하여 전달되고,
 * 참조로 전달되면 레퍼런스로 전달된다.
 *
 * 그 외의 주의 사항
 * auto와 템플릿 연역은 std::initializer_list<T>를 초기치로 가정하는지만 다르다.
 * ex) auto x = { 17 }; // std::initializer_list<int>
 * ex) auto getList(){ return { 17 }; } <= 컴파일 에러
 * 함수의 반환 형식이나 람다 매개 변수의 형식은 템플릿 연역이 적용된다.
 */

/* Case 1. Pointer또는 Reference 형식이지만 Universial 참조는 아닌 경우
 * 
 * 만약 expr이 참조형식이면 참조 부분을 무시한다.
 * ParamType과 패턴 매칭을 시켜 T의 형식을 결정한다. */
template<typename T>
void f(T& param) noexcept // param is passed by pointer or reference
{
	printTypeInfo<T>("T");
	printTypeInfo<decltype(param)>("ParamType");
}

/* Case 2. Universial Reference인 경우 
 * => T에 레퍼런스가 추론되는 유일한 경우이다.
 * 만약 expr이 lvalue인 경우 ==> T와 ParamType은 lvalue-reference로 추론된다.
 * 만약 expr이 rvalue인 경우 ==> Case 1의 규칙이 적용된다. */
template<typename T>
void g(T&& param) noexcept // param is passed by universial reference
{
	printTypeInfo<T>("T");
	printTypeInfo<decltype(param)>("ParamType");
}

/* Case 3. Reference 형식이 아닌 경우
 * => 값에 의한 복사!
 * expr에 붙어 있는 reference/const/volatile을 전부 무시한다. 
 * 원본 객체와는 완전히 독립적인 객체(복사본)이기 때문이다.
 *
 * 오해할 수 있는 부분(포인터나 레퍼런스를 전달하는 경우)
 * const char * const hi = "Hello";
 * h(hi); -> T = const char *
 * 포인터 그 자체의 상수성은 무시되지만,
 * 포인터가 가리키는 대상의 상수성은 무시할 수 없다.
 */
template<typename T>
void h	(T param) noexcept // param is still passed by value
{
	printTypeInfo<T>("T");
	printTypeInfo<decltype(param)>("ParamType");
}

int main() {	
	int x = 27;
	int& rx = x;
	const int cx = x;
	const int& rcx = x;

	printTypeInfo<decltype(x)>("x");
	printTypeInfo<decltype(rx)>("rx");
	printTypeInfo<decltype(cx)>("cx");
	printTypeInfo<decltype(rcx)>("rcx");
	printTypeInfo<decltype(27)>("27");

	f(x);
	f(rx);
	f(cx);
	f(rcx);
	// f(27);

	g(x);
	g(rx);
	g(cx);
	g(rcx);
	g(27);

	h(x);
	h(rx);
	h(cx);
	h(rcx);
	h(27);
	return 0;
}