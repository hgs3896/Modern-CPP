#include <iostream>
#include <initializer_list>
#include <atomic>
#include "type_helper.hpp"
#include "selective_compile.hpp"

class Widget {
private:
	int x = 0;
	// int y(0); <- �� ���´� non-static member�� �ʱ�ȭ�ε� ��� �Ұ��� ��
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
	/* Modern C++���� �����ϴ� 4���� ������ �ʱ�ȭ ���� */
	COMPILE(true, {
		/* 1. ��ȣ ���� */
		int x = 0;
		/* 2. ������ ���� */
		int y(0);
		/* 3. [new] �߰�ȣ ���� */
		int z{ 0 };
		/* 4. [new] ��ȣ + �߰�ȣ ���� */
		int l = { 0 }; // 3�� ������
	})

	/* ������(Constructor)�� ���� ����(Assignment)�� ���� */
	COMPILE(true, {
		Widget w1; // ������ ȣ��
		Widget w2 = w1; // ���� ������ ȣ��
		w1 = w2; // ���� ������ ȣ��
	})

	/* �߰�ȣ �ʱ�ȭ�� Ư¡1 : Implicit Narrowing Conversion�� �����Ѵ� */
	COMPILE(false, {
		double x = 0.0, y = 2.0, z = 3.0;
		int sum{ x + y + z };
	})

	/* �߰�ȣ �ʱ�ȭ�� Ư¡2: ���� ������ ���� �ؼ�(Most Vexing Parse) �����κ��� �����Ӵ�.
	 * ���� ������ ���� �ؼ�: �������� �ؼ��� �� �ִ� ���� �������� �ؼ��ؾ� �Ѵ�. */
	COMPILE(true, {
		Widget w1; // ������
		Widget w2(); // �Լ� ����
		Widget w3{}; // ������
		Widget w4{ {} }; // �� �߰�ȣ ���� std::initializer_list<bool>�� ����
	})

	/* �߰�ȣ �ʱ�ȭ�� Ư¡3: �����ε��� �Լ��� �ñ״�ó �� �ϳ� �̻��� std::initializer_list<T>������ �޴´ٸ�
	 * �ش� ������ ���ϰ� ��ȣ�Ѵ�. */
	
	// Widget w2{ 10, true };
	
	{
		Widget w1(10, true);
		// 10 -> true�� �ٲٴ� ���� ������ ��ȯ�̹Ƿ� ������ ����
		// Widget w2{ 10, true };
		Widget w3( 10, 5.0 ); 
		// 5.0 -> 5�� �ٲٴ� ���� ������ ��ȯ�̹Ƿ� ������ ����
		// Widget w4{ 10, 5.0 };
	}

}