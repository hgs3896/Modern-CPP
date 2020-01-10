#include <iostream>
#include <memory>

/*
 * Raw Pointer�� ����ϱ� ����� ����
 * 1. ���� ���� �ϳ��� ��ü����, �迭 ��ü���� �˱� �����.
 * ex) int *p = new int; int *p = new int[3];
 * 2. �����Ͱ� ����Ű�� ��ü�� �ڵ� �ۼ��ڰ� ���� �ı��ؾ� �ϴ��� �˱� �����.
 * 3. ���� �ı��ؾ� �Ѵٴ� ���� �˴���, ��� �ı��ؾ� �ϴ��� �˱� �����.
 * ex) delete p; delete[] p; free(p);
 * 4. delete�� �̿��ؼ� �ı��ؾ� ���� �˰� �Ǵ��� delete�� �̿��� �� delete[]�� �̿��� �� ��ƴ�.
 * ���� ��ü�� delete[]�� �̿��Ͽ� �ı��� ��� ������ �ൿ�� �߻��Ѵ�.
 * 5. ��ü�� �ı��ؾ� �ϰ� � ������� �ı��ؾ��ϴ� �� �˴��� �ڵ��� ��� ��ο��� �ı��� ��Ȯ�� �� ���� �Ͼ�ٰ� �����ϱ� ��ƴ�.
 * �ı��� ���� �ʴ´ٸ� (���ܷ� ����) ������ �߻��� ���̰�,
 * �ı��� �ι� �̻�ȴٸ� ������ �ൿ�� �߻��� ���̴�.
 * 6. �����Ͱ� ����Ī ��ü�� �Ҿ�����(dangling pointer) �˾Ƴ��� ����� ����.

    => smart pointers(wrapper of raw pointers)
    1) std::auto_ptr : C++98�� �������� ����� ���(�̵��� ����� ó���ϸ� ������ null������ ������), �����̳ʿ� ���� �Ұ�
    2) std::unique_ptr<T>(operator[] ����), std::unique_ptr<T[]>(operator*, operator-> ����)
    : ȿ����, Move Semantics ���� =>> ������ ������ �ǹ̷�(�׻� ��ü�� ������), ���� ���� �Ұ�(Move-only type)
    3) std::shared_ptr : 
    4) std::weak_ptr : 
*/

class Vehicle {
public:
    virtual ~Vehicle() = default;
};

class Car : public Vehicle {
public:
    ~Car() {
        std::cout << "Car �ı���." << std::endl;
    }
};

class Bus : public Vehicle {
public:
    ~Bus() {
        std::cout << "Bus �ı���." << std::endl;
    }
};

class Taxi : public Vehicle {
public:
    ~Taxi() {
        std::cout << "Taxi �ı���." << std::endl;
    }
};

template<typename... Ts>
std::unique_ptr<Vehicle> getVehicle(const char* name, Ts&&... param) {
    auto ptr = std::unique_ptr<Vehicle>();
    if (name == "Car") {
        ptr.reset(new Car(std::forward(param)...));
    }
    else if (name == "Bus") {
        ptr.reset(new Bus(std::forward(param)...));
    }else if (name == "Taxi") {
        ptr.reset(new Taxi(std::forward(param)...));
    }
    return ptr;
}

int main() {
    auto car = getVehicle("Car");
    {
        auto bus = getVehicle("Bus");
        auto taxi = getVehicle("Taxi");
        car = std::move(taxi);
    }
    
	return 0;
}