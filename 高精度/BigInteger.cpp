#include "BigInteger.h"

BigInteger::BigInteger(long long num = 0) 
{
	*this = num;
}

BigInteger::BigInteger(string& str) 
{ 
	*this = str; 
}

BigInteger& BigInteger::operator = (long long num)
{	
	long long a = abs(num);
	s.clear();
	do 
	{
		s.push_back(a % BASE);
		a /= BASE;
	} while (a > 0);
	if (num >= 0)
		sgn = 1;
	else
		sgn = 0;
	return *this;
}

BigInteger& BigInteger::operator = (string& str)
{
	s.clear();
	sgn = 1;
	if (str[0] == '-')
	{
		str.erase(str.begin());
		sgn = 0;
	}
	int x, len = (str.length() - 1) / WIDTH + 1;
	for (int i = 0; i < len; i++) 
	{
		int end = str.length() - i * WIDTH;
		int start = max(0, end - WIDTH);
		sscanf(str.substr(start, end - start).c_str(), "%d", &x);
		s.push_back(x);
	}
	return *this;
}

BigInteger BigInteger::operator-()
{
	BigInteger tmp = *this;
	tmp.sgn = !(sgn);
	return tmp;
}

BigInteger BigInteger::operator + (const BigInteger& b)
{
	BigInteger c;
	c.s.clear();
	if (this->sgn == b.sgn)
		c.sgn = sgn;
	else
	{
		if (Bigabs(*this) == Bigabs(b))
		{
			c = 0;
			return c;
		}
		c = Bigabs(*this) - Bigabs(b);
		c.sgn = (Bigabs(*this) > Bigabs(b)) ? sgn : b.sgn;
		return c;
	}
	for (int i = 0, g = 0; ; i++) 
	{
		if (g == 0 && i >= s.size() && i >= b.s.size()) 
			break;
		int x = g;
		if (i < s.size()) 
			x += s[i];
		if (i < b.s.size()) 
			x += b.s[i];
		c.s.push_back(x % BASE);
		g = x / BASE;
	}
	return c;
}

BigInteger BigInteger::operator += (const BigInteger& b)
{
	*this = *this + b; 
	return *this;
}

BigInteger &BigInteger::operator ++ ()                       //预自增
{
	*this = *this + 1;
	return *this;
}

BigInteger BigInteger::operator ++ (int x)
{
	BigInteger tmp = *this;
	*this = *this + 1;
	return tmp;
}

BigInteger BigInteger::operator - (const BigInteger& b)
{
	BigInteger c;
	c.s.clear();
	if (*this == b)
	{
		c = 0;
		return c;
	}
	if (sgn == 1 && b.sgn == 1)
		if (*this > b)
		{
			c.sgn = 1;
			for (int i = 0, g = 0; ; i++)
			{
				if (i >= s.size())
					break;
				int x = g;
				x += s[i];
				if (i < b.s.size())
					x -= b.s[i];
				if (x < 0)
				{
					g = -1;
					x = BASE - x;
				}
				else
					g = 0;
				if (!(x == 0 && i == s.size() - 1))
					c.s.push_back(x);
			}
			return c;
		}
		else
		{
			BigInteger t = b;
			c = t - *this;
			c.sgn = 0;
			return c;
		}
	if (sgn == 0 && b.sgn == 0)
	{
		BigInteger t = b;
		return (-t) - (-*this);
	}
	if (sgn == 1 && b.sgn == 0)
	{
		BigInteger t = b;
		return *this + (-t);
	}
	if (sgn == 0 && b.sgn == 1)
	{
		return -((-*this) + b);
	}
}

BigInteger BigInteger::operator -= (const BigInteger& b)
{
	*this = *this - b; 
	return *this;
}

BigInteger &BigInteger::operator -- ()
{
	*this = *this - 1;
	return *this;
}

BigInteger BigInteger::operator -- (int x)
{
	BigInteger tmp = *this;
	*this = *this - 1;
	return tmp;
}

BigInteger BigInteger::operator * (const BigInteger& b)
{
	BigInteger c;
	c.s.clear();
	c.sgn = (sgn == b.sgn);
	if (*this == 0 || b == 0)
	{
		c = 0;
		return c;
	}
	long long x;
	int g = 0;
	int lsize = s.size();
	int rsize = b.s.size();
	for (int i = 0; i != lsize; i++) 
	{
		for (int j = 0; j != rsize; j++) 
		{
			x = static_cast<long long>(s[i]) * b.s[j];
			g = x / BASE;
			if (i + j >= c.s.size()) 
			{
				c.s.push_back(x % BASE);
				if(g != 0) 
					c.s.push_back(g);
			}
			else 
			{
				int t = c.s[i + j] + ( x % BASE );
				g += t / BASE;
				c.s[i + j] = t % BASE;
				if (i + j + 1 == c.s.size()) 
				{
					c.s.push_back(g);
					//if (g / BASE != 0)c.s.push_back(g / BASE); 研究表明这条代码不可能被执行
				}
				else 
				{
					t = c.s[i + j + 1] + g; // g可能为99999999,t<=199999998
					g = t / BASE; // g最多为1
					c.s[i + j + 1] = t % BASE;
					t = 2; // 此时t用作计数
					while (g != 1) 
					{
						if (i + j + t == c.s.size()) 
						{ 
							c.s.push_back(g);
							break;
						}
						if (c.s[i + j + t] != 99999999) 
						{ 
							c.s[i + j + t] += 1; 
							break; 
						}
						c.s[i + j + t] = 0; 
						t++;
					}
				}
			}
		}
	}
	while (c.s.back() == 0 && c.s.size() > 1)
		c.s.erase(c.s.begin() + c.s.size() - 1);
	return c;
}

BigInteger BigInteger::operator *= (const BigInteger& x)
{
	*this = *this * x; 
	return *this;
}

BigInteger BigInteger::operator / (const long long& b)
{
	BigInteger c;
	c.s.clear();
	if (b == 0)
	{
		cout << "Error: Divided by 0" << endl;
		exit(1);
	}
	if (*this == 0)
	{
		c = 0;
		return c;
	}
	c.sgn = (sgn == (b > 0));
	for (int i = s.size(); i > 0; i--)
		c.s.push_back(0);
	for (int i = s.size() - 1; i > 0; i--)
	{
		c.s[i - 1] = (s[i] + c.s[i]) % abs(b) * BASE;
		c.s[i] = (s[i] + c.s[i]) / abs(b);
	}
	c.s[0] = (s[0] + c.s[0]) / abs(b);
	while ((c.s.back()) == 0 && c.s.size() > 1)
		c.s.erase(c.s.begin() + c.s.size() - 1);
	return c;
}

BigInteger BigInteger::operator /= (const long long& b)
{
	*this = *this / b;
	return *this;
}

BigInteger BigInteger::operator / (const BigInteger& b)
{
	BigInteger c;
	c.s.clear();
	if (b == 0)
	{
		cout << "Error: Divided by 0" << endl;
		exit(1);
	}
	if (*this == 0)
	{
		c = 0;
		return c;
	}
	BigInteger t1 = Bigabs(*this), t2 = Bigabs(b);
	if (t1 < t2)
	{
		c = 0;
		return c;
	}
	if (t1 == t2)
	{
		c = 1;
		return c;
	}
	BigInteger l = 0, r = t1+1;
	c = (l + r) / 2;
	while (t1 >= c * t2 + t2 || c * t2 > t1)
	{
		if (t1 < c * t2) 
			r = c;
		else if (t1 > c * t2) 
			l = c;
		c = (l + r) / 2;
	}
	c.sgn = (sgn == b.sgn);
	return c;
}

BigInteger BigInteger::operator /= (const BigInteger& b)
{
	*this = *this / b;
	return *this;
}

BigInteger BigInteger::operator % (const BigInteger& b)
{
	BigInteger c;
	c.s.clear();
	c = *this - *this / b * b;
	return c;
}

BigInteger BigInteger::operator %= (const BigInteger& b)
{
	*this = *this % b;
	return *this;
}

bool BigInteger::operator < (const BigInteger& b) const
{
	if (sgn < b.sgn)
		return true;
	if (sgn > b.sgn)
		return false;
	if (sgn)
	{
		if (s.size() != b.s.size())
			return s.size() < b.s.size();
		for (int i = s.size() - 1; i >= 0; i--)
			if (s[i] != b.s[i])
				return s[i] < b.s[i];
		return false; //相等
	}
	else
	{
		if (s.size() != b.s.size())
			return s.size() > b.s.size();
		for (int i = s.size() - 1; i >= 0; i--)
			if (s[i] != b.s[i])
				return s[i] > b.s[i];
		return false; //相等
	}
}

bool BigInteger::operator > (const BigInteger& b) const 
{ 
	return b < *this;
}

bool BigInteger::operator <= (const BigInteger& b) const 
{ 
	return !(b < *this); 
}

bool BigInteger::operator >= (const BigInteger& b) const 
{ 
	return !(*this < b); 
}

bool BigInteger::operator != (const BigInteger& b) const 
{ 
	return *this < b || b < *this;
}

bool BigInteger::operator == (const BigInteger& b) const 
{ 
	return !(*this < b) && !(b < *this); 
}

BigInteger Bigabs(const BigInteger &num)
{
	BigInteger tmp = num;
	tmp.sgn = 1;
	return tmp;
}

ostream& operator << (ostream& out, const BigInteger& x) 
{
	if (x.sgn == 0)
		out << '-';
	out << x.s.back();
	for (int i = x.s.size() - 2; i >= 0; i--) 
	{
		char buf[20];
		sprintf(buf, "%08d", x.s[i]);
		for (int j = 0; j < strlen(buf); j++) 
			out << buf[j];
	}
	return out;
}

istream& operator >> (istream& in, BigInteger& x) 
{
	string s;
	if (!(in >> s)) 
		return in;
	x = s;
	return in;
}
