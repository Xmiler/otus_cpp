#include <string>
#include <type_traits>

namespace motivation {
	struct SomeStruct {
	public:
		template<typename TT>
		SomeStruct(TT&& value)	: m_value{std::forward<TT>(value)} {}

		SomeStruct(const SomeStruct& rhs) : m_value{rhs.m_value} {

		}
	private:
		std::string m_value;
	};

	void example() {
		SomeStruct value{"trololo"};
		SomeStruct value2{std::string{"trololo"}};

		std::string str{"parampampam"};
		const SomeStruct value3{str};

		// SomeStruct other{value}; // Error... Hm...
		SomeStruct other2{value3}; // It works!!! Hm...
	}
}

// int main() {
// 	motivation::example();

// 	return 0;
// }

struct SomeStruct {

	template<typename TT, 
		typename Fake = 
			typename std::enable_if<
				!std::is_same<typename std::remove_reference<TT>::type, 
					SomeStruct>::value, void>::type
	>
	SomeStruct(TT&& value) : m_value{std::forward<TT>(value)} {

	}

	SomeStruct(const SomeStruct& other) : m_value{other.m_value} {

	}

	const std::string& getValue() const {
		return m_value;
	}

private:
	std::string m_value;
};



int main() {

	SomeStruct first("Hello, World!");
	SomeStruct second = first;

	return 0;
}
