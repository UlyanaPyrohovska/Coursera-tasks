#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

string retired(int year, const map<int, string> &stati) {
	string name;
	auto popa = stati.upper_bound(year);
	if (popa != stati.begin()) {
		name = (--popa)->second;
	}
	return name;
}

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
		string name, surname;
		name = retired(year, firstname);
		surname = retired(year, secondname);
		if (!name.empty() && !surname.empty())
			return name + " " + surname;
		if (surname.empty() && name.empty())
			return "Incognito";
		if (surname.empty())
			return name + " with unknown last name";
		return surname + " with unknown first name";
	}
private:
// приватные поля
	map<int, string> firstname;
	map<int, string> secondname;
};

int main() {
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

