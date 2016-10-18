#ifndef ERROR_TEMP
#define ERROR_TEMP

#include <vector>
#include <map>
#include <iostream>

using std::vector;
using std::map;

template<typename T>
class TemplateError
{

	static vector<int> _list;
public:
	TemplateError() {}
	~TemplateError() {}
	static int get(int index) {
		std::cout << "get:" << index << std::endl;
		if (index >= _list.size())
			return -1;
		return _list[index];
	}

	static void set(int item) {
		std::cout << "set:" << item << std::endl;
		_list.push_back(item);
	}
};

template<typename T>
vector<int> TemplateError<T>::_list;

#endif