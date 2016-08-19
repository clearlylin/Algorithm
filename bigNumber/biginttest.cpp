#include "bigint.h"

#include <iostream>

using namespace std;




int main(int argc, char const *argv[])
{
	string a = "789456123654987456321456987456321",
	b = "7896541236547896541236457489";
	BigInt left(a), right(b);
	BigInt r = left + b;
	string sr = r.getStr();
	string c = "789464020196224004217998223913810";
	if (sr == c)
		std::cout <<"1 result is right" << std::endl;
	else
		std::cout <<"1 result is erro" << std::endl;


	a = "123456987789654123987456321852741369", b = "1234566987741258963214785963258741369874521456987";
	c = "1234566987741382420202575617382728826196374198356";
	left.set(a), right.set(b);
	r = left + right;
	if (r.getStr() == c)
		std::cout <<"2 result is right" << std::endl;
	else {
		std::cout << r.getStr() << std::endl;
		std::cout << c << std::endl;
		std::cout <<"2 result is erro" << std::endl;
	}

	a = "9999", b = "1111", c = "11110";
	left.set(a), right.set(b);
	r = left + right;
	if (r.getStr() == c)
		std::cout <<"3 result is right" << std::endl;
	else
		std::cout <<"3 result is erro" << std::endl;

	r = left -right;
	c = "8888";
	if (r.getStr() == c)
		std::cout <<"4 result is right" << std::endl;
	else
		std::cout <<"4 result is erro" << std::endl;
	r = right - left;
	c = "-8888";
	if (r.getStr() == c)
		std::cout <<"5 result is right" << std::endl;
	else
		std::cout <<"5 result is erro" << std::endl;

	left.set("-98"), right.set("99");
	r = left + right;
	if (r.getStr() == "1")
		std::cout << "7 right" << std::endl;

	r = left * right;
	std::cout << r.getStr()<<std::endl;

	a = "123456987789654123987456321852741369", b = "1234566987741258963214785963258741369874521456987";
	left.set(a), right.set(b);
	r = left * right;
	std::cout << r.getStr() << std::endl;
	return 0;
}