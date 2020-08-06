#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

enum class Gender {
	FEMALE, MALE
};

struct Person {
	int age;  // возраст
	Gender gender;  // пол
	bool is_employed;  // имеет ли работу
};
template<typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
	if (range_begin == range_end) {
		return 0;
	}
	vector<typename InputIt::value_type> range_copy(range_begin, range_end);
	auto middle = begin(range_copy) + range_copy.size() / 2;
	nth_element(begin(range_copy), middle, end(range_copy),
			[](const Person &lhs, const Person &rhs) {
				return lhs.age < rhs.age;
			}
	);
	return middle->age;
}
void PrintStats(vector<Person> persons) {
	auto fem_bound = partition(begin(persons), end(persons),
			[](const Person &pers) {
				return pers.gender == Gender::FEMALE;
			});
	auto fem_empl = partition(begin(persons), fem_bound,
			[](const Person &pers) {
				return pers.is_employed;
			});
	auto man_empl = partition(fem_bound, end(persons), [](const Person &pers) {
		return pers.is_employed;
	});
	cout << "Median age = " << ComputeMedianAge(begin(persons), end(persons))
			<< endl;
	cout << "Median age for females = "
			<< ComputeMedianAge(begin(persons), fem_bound) << endl;
	cout << "Median age for males = "
			<< ComputeMedianAge(fem_bound, end(persons)) << endl;
	cout << "Median age for employed females = "
			<< ComputeMedianAge(begin(persons), fem_empl) << endl;
	cout << "Median age for unemployed females = "
			<< ComputeMedianAge(fem_empl, fem_bound) << endl;
	cout << "Median age for employed males = "
			<< ComputeMedianAge(fem_bound, man_empl) << endl;
	cout << "Median age for unemployed males = "
			<< ComputeMedianAge(man_empl, end(persons)) << endl;
}

// Это пример функции, его не нужно отправлять вместе с функцией PrintStats

int main() {
	vector<Person> persons = { { 31, Gender::MALE, false }, { 40,
			Gender::FEMALE, true }, { 24, Gender::MALE, true }, { 20,
			Gender::FEMALE, true }, { 80, Gender::FEMALE, false }, { 78,
			Gender::MALE, false }, { 10, Gender::FEMALE, false }, { 55,
			Gender::MALE, true }, };
	PrintStats(persons);
	return 0;
}

