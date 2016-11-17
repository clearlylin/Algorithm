#include <iostream>
#include "impl.h"

int main(int argc, char const *argv[])
{
	std::cout << "range(10)" << std::endl;
	for(auto i : FOR::range(10))
		std::cout << i << " ";
	std::cout << std::endl;

	std::cout << "range(2, 10)" << std::endl;
	for(auto i : FOR::range(2, 10))
		std::cout << i << " ";
	std::cout << std::endl;

	std::cout << "range(2, 10, 2)" << std::endl;
	for(auto i : FOR::range(2, 10, 2))
		std::cout << i << " ";
	std::cout << std::endl;
	return 0;
}