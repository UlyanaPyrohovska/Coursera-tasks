#include <iostream>
#include <iomanip>
#include <algorithm>
#include <set>
#include <sstream>
#include <map>
#include <vector>
#include <exception>
#include <stdexcept>
using namespace std;

class Rational {
public:
	Rational() {
		p = 0;
		q = 1;
	}

	Rational(int numerator, int denominator) {
		if (denominator < 0) {
			if (numerator < 0) {
				numerator = abs(numerator);
				denominator = abs(denominator);
			} else {
				denominator = abs(denominator);
				numerator = numerator - 2 * numerator;
			}
		}
		if (denominator == 0) {
			throw invalid_argument("Invalid argument");
		}
		if (numerator == 0) {
			denominator = 1;
		}
		int k = dup(abs(numerator), abs(denominator));
		p = numerator / k;
		q = denominator / k;
	}

	int Numerator() const {
		return p;
	}

	int Denominator() const {
		return q;
	}

private:
	int dup(int numerator, int denominator) {
		while (numerator > 0 && denominator > 0) {
			if (numerator > denominator)
				numerator = numerator % denominator;
			else
				denominator = denominator % numerator;
		}
		return denominator + numerator;
	}
	int p;
	int q;
};

bool operator ==(const Rational &a, const Rational &b) {
	if ((a.Numerator() == b.Numerator())
			&& (a.Denominator() == b.Denominator())) {
		return true;
	} else {
		return false;
	}

}

Rational operator +(const Rational &a, const Rational &b) {
	int q = (a.Numerator() * b.Denominator() + b.Numerator() * a.Denominator());
	int p = (a.Denominator() * b.Denominator());
	return Rational(q, p);
}

Rational operator -(const Rational &a, const Rational &b) {
	int p = (a.Numerator() * b.Denominator() - b.Numerator() * a.Denominator());
	int q = (a.Denominator() * b.Denominator());
	return Rational(p, q);
}

Rational operator /(const Rational &a, const Rational &b) {
	int p = (a.Numerator() * b.Denominator());
	int q = (b.Numerator() * a.Denominator());
	if (q == 0) {
		throw domain_error("Division by zero");
	}
	return Rational(p, q);
}
Rational operator *(const Rational &a, const Rational &b) {
	int p = (a.Numerator() * b.Numerator());
	int q = (b.Denominator() * a.Denominator());
	return Rational(p, q);
}

istream& operator >>(istream &stream, Rational &a) {
	int n, d;
	char c;
	stream >> n >> c >> d;
	if (stream && c == '/') {
		a = Rational(n, d);
	}
	return stream;
}

ostream& operator <<(ostream &stream, const Rational &a) {
	stream << a.Numerator() << "/" << a.Denominator();
	return stream;
}

bool operator <(const Rational &a, const Rational &b) {
	int r = a.Numerator() * b.Denominator();
	int r1 = b.Numerator() * a.Denominator();
	if (r < r1) {
		return true;
	} else
		return false;
}

bool operator >(const Rational &a, const Rational &b) {
	int r = a.Numerator() * b.Denominator();
	int r1 = b.Numerator() * a.Denominator();
	if (r > r1) {
		return true;
	} else
		return false;
}

int main() {
	try {
		Rational x;
		Rational y;
		char z;
		cin >> x >> z >> y;

		switch (z) {
		case '+':
			cout << x + y;
			break;
		case '-':
			cout << x - y;
			break;
		case '*':
			cout << x * y;
			break;
		case '/':
			cout << x / y;
			break;
		}
	} catch (exception &ex) {
		cout << ex.what() << endl;
	}
	return 0;
}
