#include <string>
#include <iostream>


namespace igtl{

	using namespace std;

	struct igstring_traits:public char_traits<char> {

		static bool eq(char c1, char c2) {
			return toupper(c1) == toupper(c2);
		}

		static bool ne(char c1, char c2) {
			return toupper(c1) != toupper(c2);
		}

		static bool lt(char c1, char c2){
			return toupper(c1) < toupper(c2);
		}

		static int compare(const char* s1, const char* s2, size_t size) {
			char a, b;
			while (*s1 && *s2 && size) {
				a = toupper(*s1);
				b = toupper(*s2);
				if (a == b) {
					++s1;
					++s2;
					--size;
				}
				else if (a > b)
					return 1;
				else
					return -1;
			}
			if (size == 0)
				return 0;

			if (*s1)
				return 1;

			return -1;
		}

		static const char* find(const char* s, int n, char a) {
			while (n-- > 0 && ne(*s, a))
				++s;
			return s;
		}
	};

	typedef basic_string<char, igstring_traits> igString;

	ostream& operator << (ostream& os, igString& ig) {
		os << ig.c_str();
		return os;
	}

	void test(){
		igString str = "ABc";
		igString str2 = "abc";
		if (str == str2)
			std::cout << "the same one" << std::endl;
		else
			std::cout << "the not same" << std::endl;

		std::cout << str;
	}
}
