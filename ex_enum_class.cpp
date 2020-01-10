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

		// �߰�ȣ �ȿ� ���ǵ� �̸��� �̸�����(namespace)�� ��������.
		// auto white = false; 

		// �ڵ����� ������ ��ȯ�ȴ�.
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

		// �߰�ȣ �ȿ� ���ǵ� �̸��� �̸�����(namespace)�� �������� �ʴ´�.
		auto white = false;

		auto red = Color::red;
		// �Ͻ����� ���� ��ȯ �ȵ�
		// int x = Color::black;
		// ������� ��ȯ�� ���
		auto x = static_cast<int>(Color::black);

		{
			// �׳� unscoped enum�� forwarding declaration(���� ����: ���Ǹ� ���߿�) ����
			// why? : ������ �� ���� ���谡 �þ�⿡ enum�� ���ǰ� ���� �Ǹ� ���� ������ �ؾ��Ѵ�.
			// enum Color1;

			// scoped forwarding declaration ���
			// but, scoped enum�� basic_type�� �����Ϸ��� �������� �� �� �ֱ� ������ ������ ���� ����κ��� �����Ӵ�.
			enum class Color2; 
			enum class Color2 {
				good, fail
			};
			// basic_type�� long���� �����Ѵ�.
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