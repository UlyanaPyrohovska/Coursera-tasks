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

class Person {
public:
	void ChangeFirstName(int year, const string &first_name) {
		// добавить факт изменения имени на first_name в год year
		firstname[year] = first_name;
	}
	void ChangeLastName(int year, const string &last_name) {
		// добавить факт изменения фамилии на last_name в год year
		secondname[year] = last_name;
	}
	string GetFullName(int year) {
		// получить имя и фамилию по состоянию на конец года year
		bool f1 = false;
		bool f2 = false;
		string name, surname;
		int bin = firstname.begin()->first;
		for (int i = year; i >= bin; --i) {
			if (firstname.count(i)) {
				name = firstname[i];
				f1 = 1;
				break;
			}
		}
		bin = secondname.begin()->first;
		for (int i = year; i >= bin; --i) {
			if (secondname.count(i)) {
				surname = secondname[i];
				f2 = 1;
				break;
			}

		}

		if (f1 && f2)
			return name + " " + surname;
		else {
			if (f1)
				return name + " with unknown last name";
			else {
				if (f2)
					return surname + " with unknown first name";
				else
					return "Incognito";
			}
		}

	}
private:
	// приватные поля
	map<int, string> firstname;
	map<int, string> secondname;
};

void TestChangeFirstName() {
	Person person;
	AssertEqual(person.GetFullName(1), "Incognito", "Incognito");
	person.ChangeFirstName(1, "sup");
	AssertEqual(person.GetFullName(1), "sup with unknown last name",
			"key: 1, value: sup");
	person.ChangeFirstName(-500, "bol");
	AssertEqual(person.GetFullName(-500), "bol with unknown last name",
			"key: -500, value: bol");
	person.ChangeFirstName(3, "cop");
	AssertEqual(person.GetFullName(3), "cop with unknown last name",
			"key: 3, value: cop");
	person.ChangeLastName(1, "olegovich");
	AssertEqual(person.GetFullName(3), "cop olegovich",
			"key: 3, value: olegovich");
	person.ChangeLastName(2, "aleksi");
	AssertEqual(person.GetFullName(3), "cop aleksi", "key: 3, value: aleksi");
	Person person1;
	person1.ChangeLastName(5, "tupa");
	AssertEqual(person1.GetFullName(5), "tupa with unknown first name",
			"key: 5, value: tupa");
	person1.ChangeLastName(1, "lupa");
	AssertEqual(person1.GetFullName(6), "tupa with unknown first name",
			"key: 5, value: tupa");
}

int main() {
	TestRunner runner;
	runner.RunTest(TestChangeFirstName, "TestChangeFirstName");

	Person person;
	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : { 1900, 1965, 1990 }) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : { 1969, 1970 }) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : { 1969, 1970 }) {
		cout << person.GetFullName(year) << endl;
	}
	return 0;
}
