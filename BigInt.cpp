#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include<math.h>

using namespace std;

class BigInt {
public:
	BigInt(string a = "")
	{
		str = a;
	}
	bool operator < (BigInt const& a)
	{
		int m = 0;
		if (str[0] == '-' && a.str[0] != '-') return true;
		else if (str[0] != '-' && a.str[0] == '-') return false;
		if (str[0] == '-' && a.str[0] == '-') m++;
		if (m && str.size() < a.str.size()) return false;
		if (m && str.size() > a.str.size()) return true;
		if (!m && str.size() < a.str.size()) return true;
		if (!m && str.size() > a.str.size()) return false;
		for (int i = m; i < str.size(); i++)
			if (m && str[i] < a.str[i]) return false;
			else if (str[i] < a.str[i]) return true;
			else if (m && str[i] > a.str[i]) return true;
			else if (str[i] > a.str[i]) return false;
		return false;
	}
	bool operator > (BigInt const& a)
	{
		int m = 0;
		if (str[0] == '-' && a.str[0] != '-') return false;
		else if (str[0] != '-' && a.str[0] == '-') return true;
		if (str[0] == '-' && a.str[0] == '-') m++;
		if (m && str.size() < a.str.size()) return true;
		if (m && str.size() > a.str.size()) return false;
		if (!m && str.size() < a.str.size()) return false;
		if (!m && str.size() > a.str.size()) return true;
		for (int i = m; i < str.size(); i++)
			if (m && str[i] > a.str[i]) return false;
			else if (str[i] > a.str[i]) return true;
			else if (m && str[i] < a.str[i]) return true;
			else if (str[i] < a.str[i]) return false;
		return false;
	}
	bool operator == (BigInt const& a)
	{
		if (str.size() > a.str.size() || str.size() < a.str.size()) return false;
		for (int i = 0; i < str.size(); i++)
			if (str[i] > a.str[i] || str[i] < a.str[i]) return false;
		return true;
	}
	BigInt operator + (BigInt const& a)
	{
		int m = 0;
		if (str[0] == '-' && a.str[0] != '-')
		{
			BigInt b = a;
			BigInt c;
			c.str = str.substr(1, str.size() - 1);
			return b - c;
		}
		else if (str[0] != '-' && a.str[0] == '-')
		{
			BigInt b;
			b.str = a.str.substr(1, a.str.size() - 1);
			return (*this) - a.str.substr(1, a.str.size() - 1);
		}
		else if (str[0] == '-' && a.str[0] == '-')
		{
			BigInt m, b, c;
			b.str = str.substr(1, str.size() - 1);
			c.str = a.str.substr(1, a.str.size() - 1);
			m.str = "-" + (b + c).str;
			return m;
		}
		int c = 0, d = 0, s_size = 0, i = 0;
		BigInt b;
		if (str.size() < a.str.size() || str.size() == a.str.size())
		{
			i = str.size() - 1;
			s_size = a.str.size() - str.size();
		}
		else
		{
			i = a.str.size() - 1;
			s_size = str.size() - a.str.size();
		}
		for (; i >= 0; i--)
		{
			d = c;
			if (str.size() < a.str.size()) d += (str[i] - '0') + (a.str[i + s_size] - '0');
			if (a.str.size() <= str.size()) d += (a.str[i] - '0') + (str[i + s_size] - '0');
			if (d > 9)
			{
				b.str = to_string(d % 10) + b.str;
				if (c == 0) c++;
			}
			else
			{
				b.str = to_string(d) + b.str; c = 0;
			}
		}
		for (int j = s_size - 1; j >= 0; j--)
		{
			if (str.size() < a.str.size()) d = (a.str[j] - '0') + c;
			else if (a.str.size() < str.size()) d = (str[j] - '0') + c;
			if (d > 9)
			{
				b.str = to_string(d % 10) + b.str;
				if (c == 0) c++;
			}
			else
			{
				b.str = to_string(d) + b.str; c = 0;
			}
		}
		if (d > 9) b.str = "1" + b.str;
		return b;
	}
	BigInt operator - (BigInt const& a)
	{
		if ((*this) == a)
		{
			return BigInt("0");
		}
		if (str[0] == '-' && a.str[0] != '-')
		{
			BigInt b;
			b.str = "-" + a.str;
			return (*this) + b;
		}
		if (str[0] != '-' && a.str[0] == '-')
		{
			BigInt b;
			b.str = a.str.substr(1, a.str.size() - 1);
			return (*this) + b;
		}
		if (str[0] == '-' && a.str[0] == '-')
		{
			BigInt b, c;
			b.str = str.substr(1, str.size() - 1);
			c.str = a.str.substr(1, a.str.size() - 1);
			return c - b;
		}
		int c = 0, d;
		BigInt b;
		if ((*this) < a)
		{
			BigInt m = a;
			m.str = "-" + (m - (*this)).str;
			return m;
		}
		int s_size, i;
		if (str.size() < a.str.size() || str.size() == a.str.size())
		{
			i = str.size() - 1;
			s_size = a.str.size() - str.size();
		}
		else
		{
			i = a.str.size() - 1;
			s_size = str.size() - a.str.size();
		}
		for (; i >= 0; i--)
		{
			d = (str[i + s_size] - '0') - (a.str[i] - '0') - c;
			if (d < 0)
			{
				b.str = to_string(10 + d) + b.str;
				if (c == 0) c++;
			}
			else
			{
				b.str = to_string(d) + b.str;
				c = 0;
			}
		}
		for (int j = s_size - 1; j >= 0; j--)
		{
			d = (str[j] - '0') - c;
			if (d < 0)
			{
				b.str = to_string(10 + d) + b.str;
				if (c == 0) c++;
			}
			else
			{
				b.str = to_string(d) + b.str;
				c = 0;
			}
		}
		if (b.str[0] == '0') b.str = b.str.substr(1, b.str.size() - 1);
		return b;
	}
	BigInt operator * (BigInt const& a)
	{
		if (str[0] == '-' && a.str[0] != '-')
		{
			BigInt c;
			c.str = str.substr(1, str.size() - 1);
			c = c * a;
			c.str = "-" + c.str;
			return c;
		}
		else if (str[0] != '-' && a.str[0] == '-')
		{
			BigInt c;
			c.str = a.str.substr(1, a.str.size() - 1);
			c = c * (*this);
			c.str = "-" + c.str;
			return c;
		}
		else if (str[0] == '-' && a.str[0] == '-')
		{
			BigInt c, d;
			c.str = str.substr(1, str.size() - 1);
			d.str = a.str.substr(1, a.str.size() - 1);
			return c * d;
		}
		if ((*this) < a)
		{
			BigInt b = a;
			return b * (*this);				//swap
		}
		int t = 0;
		BigInt b, q;
		for (int i = a.str.size() - 1; i >= 0; i--)
		{
			t = 0;
			b.str = "";
			for (int j = str.size() - 1; j >= 0; j--)
			{
				b.str = to_string((((a.str[i] - '0') * (str[j] - '0')) + t) % 10) + b.str;
				t = (a.str[i] - '0') * (str[j] - '0') / 10;
			}
			if (t) b.str = to_string(t) + b.str;
			b.str += string(i, '0');
			q.str += (b + q).str;
		}
		return q;
	}
	BigInt operator / (BigInt const& a)
	{
		if (str[0] == '-' && a.str[0] != '-')
		{
			BigInt c;
			c.str = str.substr(1, str.size() - 1);
			c = c / a;
			c.str = "-" + c.str;
			return c;
		}
		else if (str[0] != '-' && a.str[0] == '-')
		{
			BigInt c;
			c.str = a.str.substr(1, a.str.size() - 1);
			c = c / (*this);
			c.str = "-" + c.str;
			return c;
		}
		else if (str[0] == '-' && a.str[0] == '-')
		{
			BigInt c, d;
			c.str = str.substr(1, str.size() - 1);
			d.str = a.str.substr(1, a.str.size() - 1);
			return c / d;
		}
		if ((*this) < a)
		{
			BigInt b("0");
			return b;
		}
		int div = 0, r = 0;
		BigInt m, res;
		do {
			if (m.str[0] == '0')
			{
				res.str = res.str + '0';
				m.str = "";
				continue;
			}
			if (m < a)
			{
				m.str += str[r];
				r++; continue;
			}
			div = 0;
			while ((m - a).str[0] != '-')
			{
				m = m - a;
				if (m.str[0] == '0') m.str = "";
				div++;
			}
			res.str = res.str + to_string(div);
		} while (r < str.size());
		div = 0;
		while ((m - a).str[0] != '-')
		{
			m = m - a;
			div++;
		}
		return res.str + to_string(div);
	}

	void print()
	{
		for (int i = 0; i < str.size(); i++)
			cout << str[i];
		cout << endl;
	}
private:
	string str;
};


int main()
{
//	BigInt a = BigInt("234278477388299839288377266677");
//	BigInt b = BigInt("475883992884857488277488372738");
//	BigInt a = BigInt("28");
//	BigInt b = BigInt("6");
//	(a + b).print();
//	(a - b).print();
//	(a * b).print();
//	(a / b).print();
//	cout << (a < b) << endl;
//	cout << (a > b) << endl;
//	cout << (a == b) << endl;
	system("pause");
	return 0;
}