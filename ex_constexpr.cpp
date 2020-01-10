#include <iostream>

constexpr int pow(int base, int exp) noexcept {
	return (exp == 0 ? 1 : base * pow(base, exp - 1));
}

class Point {
public:
	constexpr Point(double x = 0, double y = 0) noexcept :x(x), y(y) {};
	constexpr double getX() const noexcept {
		return x;
	}
	constexpr double getY() const noexcept {
		return y;
	}
	constexpr double setX(double x) noexcept {
		this->x = x;
		return x;
	}
	constexpr double setY(double y) noexcept {
		this->y = x;
		return x;
	}	
private:
	double x, y;
};

constexpr Point middlePoint(Point a, Point b) noexcept {
	Point p{ (a.getX() + b.getX()) / 2, (a.getY() + b.getY()) / 2 };
	return p;
}

int main() {
	constexpr auto x = pow(2, 30);
	constexpr auto p = Point{ 1, 0 };
	constexpr auto q = Point{ 0, 1 };
	constexpr auto r = middlePoint(p, q);
	return 0;
}