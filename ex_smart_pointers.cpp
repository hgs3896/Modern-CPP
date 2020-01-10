#include <iostream>
#include <memory>

/*
 * Raw Pointer를 사용하기 어려운 이유
 * 1. 선언만 보고 하나의 객체인지, 배열 객체인지 알기 어려움.
 * ex) int *p = new int; int *p = new int[3];
 * 2. 포인터가 가리키는 객체를 코드 작성자가 언제 파괴해야 하는지 알기 어려움.
 * 3. 설령 파괴해야 한다는 것을 알더라도, 어떻게 파괴해야 하는지 알기 어려움.
 * ex) delete p; delete[] p; free(p);
 * 4. delete를 이용해서 파괴해야 함을 알게 되더라도 delete를 이용할 지 delete[]를 이용할 지 어렵다.
 * 단일 객체를 delete[]를 이용하여 파괴할 경우 미정의 행동이 발생한다.
 * 5. 객체를 파괴해야 하고 어떤 방법으로 파괴해야하는 지 알더라도 코드의 모든 경로에서 파괴가 정확히 한 번만 일어난다고 보장하기 어렵다.
 * 파괴가 되지 않는다면 (예외로 인해) 누수가 발생할 것이고,
 * 파괴가 두번 이상된다면 미정의 행동이 발생할 것이다.
 * 6. 포인터가 피지칭 객체를 잃었는지(dangling pointer) 알아내는 방법이 없다.

    => smart pointers(wrapper of raw pointers)
    1) std::auto_ptr : C++98로 물려받은 비권장 기능(이동을 복사로 처리하며 원본은 null값으로 설정됨), 컨테이너에 저장 불가
    2) std::unique_ptr<T>(operator[] 없음), std::unique_ptr<T[]>(operator*, operator-> 없음)
    : 효율적, Move Semantics 지원 =>> 독점적 소유권 의미론(항상 객체를 소유함), 복사 연산 불가(Move-only type)
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
        std::cout << "Car 파괴됨." << std::endl;
    }
};

class Bus : public Vehicle {
public:
    ~Bus() {
        std::cout << "Bus 파괴됨." << std::endl;
    }
};

class Taxi : public Vehicle {
public:
    ~Taxi() {
        std::cout << "Taxi 파괴됨." << std::endl;
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