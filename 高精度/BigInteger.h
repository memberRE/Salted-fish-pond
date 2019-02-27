#define _CRT_SECURE_NO_WARNINGS                           //VS特色(不安全您马呢？)
#ifndef BigInteger_h
#define BigInteger_h
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

class BigInteger
{
public:
	static const int BASE = 100000000;
	static const int WIDTH = 8;

	vector<long long> s;

	bool sgn;

	BigInteger(long long);
	BigInteger(string&);

	BigInteger& operator = (long long);
	BigInteger& operator = (string&);

	BigInteger operator -  ();

	BigInteger operator +  (const BigInteger&);
	BigInteger operator += (const BigInteger&);
	BigInteger& operator ++ ();
	BigInteger operator ++ (int);
	BigInteger operator -  (const BigInteger&);
	BigInteger operator -= (const BigInteger&);
	BigInteger& operator -- ();
	BigInteger operator -- (int);
	BigInteger operator *  (const BigInteger&);
	BigInteger operator *= (const BigInteger&);
	BigInteger operator /  (const long long&);
	BigInteger operator /= (const long long&);
	BigInteger operator /  (const BigInteger&);
	BigInteger operator /= (const BigInteger&);
	BigInteger operator %  (const BigInteger&);
	BigInteger operator %= (const BigInteger&);

	bool operator <  (const BigInteger&) const;
	bool operator >  (const BigInteger&) const;
	bool operator <= (const BigInteger&) const;
	bool operator >= (const BigInteger&) const;
	bool operator != (const BigInteger&) const;
	bool operator == (const BigInteger&) const;

};

BigInteger Bigabs(const BigInteger&);

ostream& operator << (ostream&, const BigInteger&);
istream& operator >> (istream&, BigInteger&);
#endif // !BigInteger_h
