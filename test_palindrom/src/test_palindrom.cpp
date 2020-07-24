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

bool IsPalindrom(const string &str) {
	int k = str.size() - 1;
	int m = 0;
	while (k > m) {
		if (str[m++] != str[k--])
			return false;
	}
	return true;
}
void Testall() {
	Assert(IsPalindrom(""), "Is  palindrome");
	Assert(IsPalindrom(" "), "Is  palindrome");
	Assert(IsPalindrom("lool"), "Is  palindrome");
	Assert(IsPalindrom("o"), "Is  palindrome");
	Assert(IsPalindrom("1"), "Is  palindrome");
	Assert(!IsPalindrom("madaM"), "Not a palindrome");
	Assert(!IsPalindrom("leveL"), "Not a palindrome");
	Assert(!IsPalindrom("Level"), "Not a palindrome");
	Assert(!IsPalindrom("level "), "Not a palindrome");
	Assert(!IsPalindrom(" llevell"), "Not a palindrome");
	Assert(IsPalindrom("top pot"), " is palindrome");
	Assert(IsPalindrom("l e v e l"), "Is palindrome");
	Assert(IsPalindrom("l  e  v  e  l"), "Is palindrome");
	Assert(!IsPalindrom(" lev e  l   "), "Is not palindrome");
	Assert(!IsPalindrom("mada m"), "Is not palindrome");
	Assert(!IsPalindrom("   madam  "), "Is not palindrome");
	Assert(IsPalindrom("MADAM"), "Is  palindrome");
	Assert(IsPalindrom("o lol o"), "Is  palindrome");
	Assert(!IsPalindrom(" madam"), "Is not palindrome");
	Assert(!IsPalindrom(" madrydam"), "Is not palindrome");
	Assert(IsPalindrom("wasitacaroracatisaw"), "Is  palindrome");
	Assert(IsPalindrom("   tutneotmfmtoentut   "), "Is  palindrome");
	Assert(IsPalindrom(""), "empty string");
	Assert(IsPalindrom("a"), "string a");
	Assert(IsPalindrom(" sus "), "spaces");
	Assert(!IsPalindrom("sus "), "spaces");
	Assert(!IsPalindrom("madame"), "madame");
	Assert(!IsPalindrom("pamagap"), "pamagap");
	Assert(IsPalindrom("level"), "level");
	Assert(IsPalindrom("wasitacaroracatisaw"), "wasitacaroracatisaw");
	Assert(!IsPalindrom("kasitacaroracatisaw"), "asitacaroracatisaw");
	Assert(!IsPalindrom("  pop   "), "isnt");
}
int main() {
	TestRunner runner;
	runner.RunTest(Testall, "Testall");
	return 0;
}
