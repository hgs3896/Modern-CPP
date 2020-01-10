#include <tuple>
#include <string>

template<typename T>
constexpr auto toUType(T enumerator) noexcept {
	return static_cast<std::underlying_type_t<T>>(enumerator);
}

int main() {
	{
		// Unscoped Enum
		enum Color {black, white, red};

		// 중괄호 안에 정의된 이름이 이름공간(namespace)를 더럽힌다.
		// auto white = false; 

		// 자동으로 정수로 변환된다.
		int x = white;

		// Tuple Example
		{
			enum UserInfoField {uiName, uiEmail, uiReputation};
			using UserInfo = std::tuple<
				std::string,
				std::string,
				std::string>;
			UserInfo ham{ "Ham", "hgs@h.s", "high" };
			std::get<uiName>(ham);
			std::get<uiEmail>(ham);
			std::get<uiReputation>(ham);
		}
	}

	{
		// Scoped Enum or Enum Class
		enum class Color { black, white, red };

		// 중괄호 안에 정의된 이름이 이름공간(namespace)을 더럽히지 않는다.
		auto white = false;

		auto red = Color::red;
		// 암시적인 정수 변환 안됨
		// int x = Color::black;
		// 명시적인 변환은 허용
		auto x = static_cast<int>(Color::black);

		{
			// 그냥 unscoped enum은 forwarding declaration(전방 선언: 정의를 나중에) 불허
			// why? : 컴파일 시 의존 관계가 늘어나기에 enum의 정의가 변경 되면 전부 컴파일 해야한다.
			// enum Color1;

			// scoped forwarding declaration 허용
			// but, scoped enum의 basic_type은 컴파일러가 언제든지 알 수 있기 때문에 컴파일 의존 관계로부터 자유롭다.
			enum class Color2; 
			enum class Color2 {
				good, fail
			};
			// basic_type을 long으로 지정한다.
			enum class Color3 : long;
			enum class Color3 : long {
				good = 0,
				failed = 1,
				incomplete = 100
			};
		}

		// Tuple Example
		{
			enum class UserInfoField { uiName, uiEmail, uiReputation };
			using UserInfo = std::tuple<
				std::string,
				std::string,
				std::string>;
			UserInfo ham{ "Ham", "hgs@h.s", "high" };
			std::get<toUType(UserInfoField::uiName)>(ham);
			std::get<toUType(UserInfoField::uiEmail)>(ham);
			std::get<toUType(UserInfoField::uiReputation)>(ham);
		}
	}
	
	return 0;
}