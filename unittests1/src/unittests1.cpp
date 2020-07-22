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

int GetDistinctRealRootCount(double a, double b, double c) {

}
void TestTwoRoots() {
	AssertEqual(GetDistinctRealRootCount(1, -2, -3), 2,
			"case 1, -2, -3 has two roots");
	AssertEqual(GetDistinctRealRootCount(-1, -2, 15), 2,
			"case -1, -2, 15 has two roots");
	AssertEqual(GetDistinctRealRootCount(1, 9, 0), 2,
			"case 1, 9, 0 has two roots");
	AssertEqual(GetDistinctRealRootCount(1, 0, -16), 2,
			"case 1, 0, -16 has two roots");
}
void TestOneRoot() {
	AssertEqual(GetDistinctRealRootCount(1, 12, 36), 1,
			"case 1, 12, 36 has one root");
	AssertEqual(GetDistinctRealRootCount(4, 4, 1), 1,
			"case 4, 4, 1 has one root");
}
void TestNoRoots() {
	AssertEqual(GetDistinctRealRootCount(2, 0, 5), 0,
			"case 2, 0, 5 has no roots");
	AssertEqual(GetDistinctRealRootCount(3, 2, 6), 0,
			"case 3, 2, 6 has no roots");
}
void TestLinear() {
	AssertEqual(GetDistinctRealRootCount(0, 2, 4), 1,
			"case 0, 2, 4 is lin has one root");
	AssertEqual(GetDistinctRealRootCount(0, 3, -6), 1,
			"case 0, 3, -6 is lin has one root");
}
void TestNull() {
	AssertEqual(GetDistinctRealRootCount(0, 0, 4), 0,
			"case 0, 0, 4 has no root");
	AssertEqual(GetDistinctRealRootCount(0, 0, 20), 0,
			"case 0, 0, 20 has no real root");
	AssertEqual(GetDistinctRealRootCount(0, 0, -84), 0,
			"case 0, 0, -84 has no real root");
}
int main() {
	TestRunner runner;
	runner.RunTest(TestTwoRoots, "TestTwoRoots");
	runner.RunTest(TestOneRoot, "TestOneRoot");
	runner.RunTest(TestNoRoots, "TestNoRoots");
	runner.RunTest(TestLinear, "TestLinear");
	runner.RunTest(TestNull, "TestNull");

	return 0;
}
