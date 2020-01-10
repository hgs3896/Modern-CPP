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
 * �����Ϸ��� expr�� ���ؼ� �ΰ��� Ÿ��(T, ParamType)�� �߷��Ѵ�.
 * �Ϲ������� T�� ParamType�� ���� ������(const, &, &&[reference qualifier])������
 * �ٸ� ��찡 ����.
 * 
 * 1. expr�� ���� ParamType�� �޸� ��������� ����鼭 T�� �߷��Ѵ�.
 * 2. ParamType�� T�� �����Ͽ� ParamType�� �߷��Ѵ�.
 *
 * ����: �迭�̳� �Լ� �̸���
 * ������ ���޵Ǹ� �����ͷ� �ر��Ͽ� ���޵ǰ�,
 * ������ ���޵Ǹ� ���۷����� ���޵ȴ�.
 *
 * �� ���� ���� ����
 * auto�� ���ø� ������ std::initializer_list<T>�� �ʱ�ġ�� �����ϴ����� �ٸ���.
 * ex) auto x = { 17 }; // std::initializer_list<int>
 * ex) auto getList(){ return { 17 }; } <= ������ ����
 * �Լ��� ��ȯ �����̳� ���� �Ű� ������ ������ ���ø� ������ ����ȴ�.
 */

/* Case 1. Pointer�Ǵ� Reference ���������� Universial ������ �ƴ� ���
 * 
 * ���� expr�� ���������̸� ���� �κ��� �����Ѵ�.
 * ParamType�� ���� ��Ī�� ���� T�� ������ �����Ѵ�. */
template<typename T>
void f(T& param) noexcept // param is passed by pointer or reference
{
	printTypeInfo<T>("T");
	printTypeInfo<decltype(param)>("ParamType");
}

/* Case 2. Universial Reference�� ��� 
 * => T�� ���۷����� �߷еǴ� ������ ����̴�.
 * ���� expr�� lvalue�� ��� ==> T�� ParamType�� lvalue-reference�� �߷еȴ�.
 * ���� expr�� rvalue�� ��� ==> Case 1�� ��Ģ�� ����ȴ�. */
template<typename T>
void g(T&& param) noexcept // param is passed by universial reference
{
	printTypeInfo<T>("T");
	printTypeInfo<decltype(param)>("ParamType");
}

/* Case 3. Reference ������ �ƴ� ���
 * => ���� ���� ����!
 * expr�� �پ� �ִ� reference/const/volatile�� ���� �����Ѵ�. 
 * ���� ��ü�ʹ� ������ �������� ��ü(���纻)�̱� �����̴�.
 *
 * ������ �� �ִ� �κ�(�����ͳ� ���۷����� �����ϴ� ���)
 * const char * const hi = "Hello";
 * h(hi); -> T = const char *
 * ������ �� ��ü�� ������� ���õ�����,
 * �����Ͱ� ����Ű�� ����� ������� ������ �� ����.
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