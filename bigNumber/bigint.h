#ifndef _BIGINT_H
#define _BIGINT_H

#include <vector>
#include <string>
#include <ostream>


using std::string;
using std::vector;
using std::ostream;

typedef struct BigInt
{
	int size;
	bool positive;
	vector<short> v;
	BigInt(int len = 0):size(len), positive(true), v(len, 0) {}
	BigInt(char t):size(1), positive(true), v(1, t - '0') {}
	BigInt(const string&);
	BigInt(const BigInt&);

	string getStr();
	void set(const string&);
} BigInt;

bool operator<(const BigInt&, const BigInt&);

bool operator>=


(const BigInt&, const BigInt&);

bool operator==(const BigInt&, const BigInt&);

BigInt operator+(const BigInt&, const BigInt&);

BigInt operator-(const BigInt&, const BigInt&);

BigInt operator*(const BigInt&, const BigInt&);

BigInt operator/(const BigInt&, const BigInt&);

BigInt operator%(const BigInt&, const BigInt&);

ostream& operator<<(ostream&, const BigInt&);


#endif // BIGINT_H
