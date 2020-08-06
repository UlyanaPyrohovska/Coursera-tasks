#include <iostream>
#include <set>
using namespace std;

set<int>::const_iterator FindNearestElement(const set<int> &numbers,
		int border) {
// set<int>::const_iterator �
// ��� ���������� ��� ������������ ��������� ����� �����
	const auto firs = numbers.lower_bound(border);
	if (firs == begin(numbers)) {
		return firs;
	}
	const auto pop = prev(firs);
	if (firs == end(numbers)) {
		return pop;
	}
	if (border - *pop <= *firs - border) {
		return pop;
	} else {
		return firs;
	}
}

int main() {
	set<int> numbers = { 1, 4, 6 };
	cout << *FindNearestElement(numbers, 0) << " "
			<< *FindNearestElement(numbers, 3) << " "
			<< *FindNearestElement(numbers, 5) << " "
			<< *FindNearestElement(numbers, 6) << " "
			<< *FindNearestElement(numbers, 100) << endl;

	set<int> empty_set;

	cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
	return 0;
}
