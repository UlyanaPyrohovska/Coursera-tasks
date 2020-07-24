#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template<class T>
ostream& operator <<(ostream &os, const vector<T> &s) {
	os << "{";
	bool first = true;
	for (const auto &x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template<class T>
ostream& operator <<(ostream &os, const set<T> &s) {
	os << "{";
	bool first = true;
	for (const auto &x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template<class K, class V>
ostream& operator <<(ostream &os, const map<K, V> &m) {
	os << "{";
	bool first = true;
	for (const auto &kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = { }) {
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string &hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template<class TestFunc>
	void RunTest(TestFunc func, const string &test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		} catch (exception &e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		} catch (...) {
			++fail_count;
			cerr << "Unknown exception caught" << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

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

void Testing() {
	Rational drop;
	AssertEqual(drop.Numerator(), 0, "num = 0");
	AssertEqual(drop.Denominator(), 1, "denum = 1");
	Rational drop1(6, 18);
	AssertEqual(drop1.Numerator(), 1, "num = 1");
	AssertEqual(drop1.Denominator(), 3, "denum = 3");
	Rational drop2(5, -6);
	AssertEqual(drop2.Numerator(), -5, "num = -5");
	AssertEqual(drop2.Denominator(), 6, "denum = 6");
	Rational drop3(-3, -6);
	AssertEqual(drop3.Numerator(), 1, "num = 1");
	AssertEqual(drop3.Denominator(), 2, "denum = 2");
	Rational drop4(0, -6);
	AssertEqual(drop4.Numerator(), 0, "num = 0");
	AssertEqual(drop4.Denominator(), 1, "denum = 1");
}
int main() {
	TestRunner runner;
	runner.RunTest(Testing, "Testing");
	return 0;
}
