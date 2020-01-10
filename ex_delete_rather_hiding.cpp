#include <memory>

class W {
public:
	friend int main();
	template<typename T>
	void processPointer(T* ptr) {}
	W() {}
private:
	// C++98 ��Ÿ�� �Լ� �����	
	W(const W&); // private���� �����
	W& operator=(const W&); // �������� ����

	template<>
	void processPointer<void>(void*);
};

class WW {
public:
	// C++11 ��Ÿ�� �Լ� �����
	WW() {};
	WW(const WW&) = delete;
	WW& operator=(const WW&) = delete;
	template<typename T>
	void processPointer(T* ptr) {}
	template<>
	void processPointer<void>(void* ptr) = delete;
};

// �ۿ����� ���� �� ����
// template<> void WW::processPointer<WW>(WW* ptr) = delete;

int main() {
	// ����
	W x;
	// x.processPointer(&x);
	WW y;
	y.processPointer(&y);	
}