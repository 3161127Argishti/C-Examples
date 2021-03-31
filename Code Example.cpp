#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include<math.h>

using namespace std;


class Rational {
public:
	Rational(int n = 1, int d = 1)
	{
		n = d < 0 ? -n : n; 
		d = d < 0 ? -d : d;
		reduce();
	}
	Rational add(const Rational& a, const Rational& b)
	{
		Rational r;
		r.numerator = a.numerator * b.denominator + a.denominator * b.numerator;
		r.denominator = a.denominator * b.denominator;
		r.reduce();
		return r;
	}
	Rational subtract(const Rational& a, const Rational& b)
	{
		Rational r;
		r.numerator = a.numerator * b.denominator - a.denominator * b.numerator;
		r.denominator = a.denominator * b.denominator;
		r.reduce();
		return r;
	}
	Rational multiply(const Rational& a, const Rational& b)
	{
		Rational r;
		r.numerator = a.numerator * b.numerator;
		r.denominator = a.denominator * b.denominator;
		if (r.denominator != 0)
			r.reduce();
		return r;
	}
	Rational divide(const Rational& a, const Rational& b)
	{
		Rational r;
		r.denominator = a.denominator * b.numerator;
		r.numerator = a.numerator * b.denominator;
		if (r.denominator != 0)
			r.reduce();
		return r;
	}
	Rational print()
	{
		if (denominator == 0)
			cout << "denominator can't be 0" << endl;
		else {
			cout << numerator << "/" << denominator << endl;
		}
	}
	Rational printFloat()
	{
		if (denominator == 0)
			cout <<"denominator can't be 0" << endl;
		else
			cout << numerator / denominator << "." << numerator % denominator << endl;
	}

private:
	int numerator;
	int denominator;
	int gcd(int a, int b) {
		return (a == 0) ? b : gcd(b % a, a);
	}
	void reduce() 
	{
		int k = gcd(numerator, denominator);
		numerator /= k;
		denominator /= k;
	}
};


void all_substr(string input)
{
	string Q, sub;
	int q = 0, i = 0, factorial = 1;
	while (input[i] >= 'a' && input[i] <= 'z') { Q.push_back(input[i]); i++; }
	i++;
	for (int j = i; j < input.size(); j++) q = q * 10 + (input[j] - '0');
	sort(Q.begin(), Q.end());
	factorial = 1;
	for (int k = 1; k <= Q.size() - q; k++) factorial *= k;
	i = -1;
	do {
		i++;
		if (i % factorial != 0) continue;
		for (int t = 0; t < q; t++) cout << Q[t];
		cout << endl;
	} while (next_permutation(Q.begin(), Q.end()));
}

void net_price(vector<string> prod)
{
	string s;
	int t, prod_price, k, count;
	int i = 1;
	while (i < prod.size()) 
	{
		
		count = 1;
		for (int j = i + 1; j < prod.size(); j++)
			if (prod[i] == prod[j])
			{
				count++;
				for (int z = j; z < prod.size()-1; z++)
					prod[z] = prod[z + 1];
				prod.pop_back();
				j--;
			}
		if (count == 1) {i++; continue;}
		s = prod[i];
		prod_price = 0;
		t = s.size() - 1;
		while (t>=0 && s[t] >= '0' && s[t] <= '9')
		{
			k = s[t] - '0';
			prod_price += pow(10, s.size() - t - 1) * k;
			t--;
		}
		s = s.substr(0, t + 1) + to_string(count * prod_price);
		prod[i] = s;
	}

	for (int i = 1; i < prod.size(); i++)
		cout << prod[i] << endl;
}

int main()
{
//***************
//	string input1 = "badc 1";
	string input1 = "badc 2";
//	string input1 = "badc 3";
//	all_substr(input1);                     // 

//***************
	const int size = 10;
	vector<string> input2(size);
	string prices[size] = { 
		"9",
		"BANANA FRIES 12",
		"POTATO CHIPS 30",
		"APPLE JUICE 10",
		"CANDY 5",
		"APPLE JUICE 10",
		"CANDY 5",
		"CANDY 5",
		"CANDY 5",
		"POTATO CHIPS 30"
	};
	for (int i = 0; i < size; i++)
		input2[i] = prices[i];
	
//	net_price(input2);					// 

//****************
	Rational a(4, 6);
	Rational b(1, 3);
	a.print();
	b.print();

	system("pause");
	return 0;
}