#include "bigint.h"

#include <stdexcept>

static void rmBeginZero(BigInt& big)
{
	int i = 0;
	for(; i < big.size; ++i) {
		if (big.v[i])
			break;
	}
	if (i == big.size) {
		big.size = 1;
		big.v = vector<short>(1, 0);
		return;
	}
	big.v.erase(big.v.begin(), big.v.begin() + i);
	big.size = big.v.size();
}

BigInt::BigInt(const string& s)
{
	if (s.size() == 0) {
		this->positive = true;
		this->v.resize(0, 0);
		this->size = 0;
	}
	else {
		set(s);
	}
}

BigInt::BigInt(const BigInt& big)
{
	this->positive = big.positive;
	this->size = big.size;
	this->v = big.v;
}

string BigInt::getStr()
{
	string s;
	if (positive) {
		s.resize(size, '0');
		for(int i = 0; i < size; ++i)
			s[i] = '0' + v[i];
		return s;
	}
	s.resize(size + 1, '0');
	s[0] = '-';
	int i = 1;
	for(int j = 0; j < size; ++j)
		s[i++] = '0' + v[j];
	return s;
}

void BigInt::set(const string& s)
{
	int i = 0, j = 0, len = s.size();
	positive = true;
	if (s[0] == '-') {
		positive = false;
		i = 1;
	}
	size = len - i;
	v.resize(size, 0);
	for(; i < len; ++i)
		v[j++] = s[i] - '0';
	rmBeginZero(*this);
}

bool operator<(const BigInt& left, const BigInt& right)
{
	for(int i = 0; i < left.size; ++i) {
		if (left.v[i] < right.v[i])
			return true;
		if (left.v[i] > right.v[i])
			return false;
	}
	return false;
}

bool operator>(const BigInt& left, const BigInt& right)
{
	for(int i = 0; i < left.size; ++i) {
		if (left.v[i] > right.v[i])
			return true;
		if (left.v[i] < right.v[i])
			return false;
	}
	return false;
}

bool operator==(const BigInt& left, const BigInt& right)
{
	for(int i = 0; i < left.size; ++i) {
		if (left.v[i] != right.v[i])
			return false;
	}
	return true;
}

BigInt operator+(const BigInt& left, const BigInt& right)
{
	BigInt result;
	if (left.positive == right.positive) {
		result.positive = left.positive;
		int size = (left.size > right.size ? left.size : right.size) + 1;
		int i = size - 1, l = left.size - 1, r = right.size - 1;
		int t, carry = 0;
		vector<short>  v(size, 0);
		while(l >= 0 && r >= 0) {
			t = left.v[l--] + right.v[r--] + carry;
			carry = t / 10;
			v[i--] = t % 10;
		}
		while(l >= 0) {
		    t = left.v[l--] + carry;
		    carry = t / 10;
		    v[i--] = t % 10;
		}
		while(r >= 0) {
		    t = right.v[r--] + carry;
		    carry = t / 10;
		    v[i--] = t % 10;
		}
		if (carry > 0)
			v[i] = carry;

		result.size = v.size();
		result.v = v;
		rmBeginZero(result);
		return result;
	}
	else {
		if (left.positive) {
			BigInt t = right;
			t.positive = true;
			return left - right;
		}
		else {
			BigInt t = left;
			t.positive = true;
			return right - t;
		}
	}
}

BigInt operator-(const BigInt& left, const BigInt& right)
{
	BigInt result;
	if (left.positive == right.positive) {
		vector<short> v;
		const BigInt *lptr, *rptr;
		if (right.size > left.size) {
			v.resize(right.size, 0);
			result.positive = !right.positive;
			lptr = &right;
			rptr = &left;
		}
		else if(left.size > right.size) {
			v.resize(left.size, 0);
			result.positive = left.positive;
			lptr = &left;
			rptr = &right;
		}
		else {
			v.resize(left.size, 0);
			if (left > right) {
				result.positive = left.positive;
				lptr = &left;
				rptr = &right;
			}
			else {
				result.positive = !right.positive;
				lptr = &right;
				rptr = &left;
			}
		}
		int i = v.size() - 1, l = lptr->size - 1, r = rptr->size - 1;
		int t, borrow = 0;
		while(l >= 0 && r >= 0) {
			t = lptr->v[l--] - rptr->v[r--] - borrow;
			borrow = 0;
			if (t < 0) {
				t += 10;
				borrow = 1;
			}
			v[i--] = t;
		}
		while(l >= 0) {
		    t = lptr->v[l--] - borrow;
		    borrow = 0;
		    if (t < 0) {
		    	t += 10;
		    	borrow = 1;
		    }
		    v[i--] = t;
		}
		while(r >= 0) {
		    t = rptr->v[l--] - borrow;
		    borrow = 0;
		    if (t < 0) {
		    	t += 10;
		    	borrow = 1;
		    }
		    v[i--] = t;
		}

		result.size = v.size();
		result.v = v;
		rmBeginZero(result);
		return result;
	}
	else {
		if (left.positive) {
			BigInt t = right;
			t.positive = true;
			return left + t;
		}
		else {
			BigInt t = right;
			t.positive = false;
			return left + t;
		}
	}
}

BigInt operator*(const BigInt& left, const BigInt& right)
{
	if (left.v[0] == 0 || right.v[0] == 0)
		return BigInt(1);

	int len = left.size + right.size;
	BigInt r(len);
	r.positive = left.positive == right.positive ? true : false;
	const BigInt *lptr = &left, *rptr = &right;
	if (right.size > left.size) {
		lptr = &right;
		rptr = &left;
	}
	int i = rptr->size - 1, l = lptr->size;
	for(; i >= 0; --i) {
		short t = rptr->v[i];
		if (t) {
			int k = len - rptr->size + i, j = lptr->size - 1;
			int tmp, carry = 0;
			while(j >= 0) {
				tmp = t * lptr->v[j--] + carry + r.v[k];
				carry = tmp / 10;
				r.v[k--] = tmp % 10;
			}
			if (carry)
				r.v[k] = carry;
		}
	}

	rmBeginZero(r);
	return r;
}

BigInt operator/(const BigInt& left, const BigInt& right)
{
	if (right.v[0] == 0)
		throw;
	if (left.v[0] == 0 || right.size > left.size)
		return BigInt(1);

	bool positive = left.positive == right.positive ? true : false;

	if (right.size == left.size) {
		 if(left > right) {
		 	int s = 1;
		 	//fuho
		 	BigInt r = left - right;
		 	while(r > right)
		 	    r = r -right;
		 	BigInt r(1);
		 	r.positive = positive;
		}
		else if(left < right) {
			return BigInt(1);
		}
		else {
			BigInt r(1);
			r.positive = positive;
			r.v = vector<short>(1, 1);
			return r;
		}

		int  s = 1;
		BigInt r = left - right;
		while(r.positive && r.size == right.size) {
			r = r - right;
			++s;
		}
		r.size = 1;
		r.positive = positive;
		r.v = r.positive ? vector<short>(1, s) : vector<short>(1, s - 1);
		return r;
	}
	else {

	}
	return BigInt();
}

BigInt operator%(const BigInt& left, const BigInt& right)
{
	BigInt r;
	return r;
}

ostream& operator<<(ostream& out, const BigInt& big)
{
	if (!big.positive)
		out << "-";
	for(int i = 0; i < big.size; ++i)
		out << big.v[i];
	return out;
}
