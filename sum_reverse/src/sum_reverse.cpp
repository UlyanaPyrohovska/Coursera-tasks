#include "test_runner.h"
#include "sum_reverse_sort.h"
#include <algorithm>
#include <iostream>

using namespace std;
int Sum(int x, int y) {
	return x + y;
}

string Reverse(string s) {
	string str;
	str.resize(s.size());
	int j = 0;
	for (int i = s.size() - 1; i >= 0; i--) {
		str[j] = s[i];
		j++;
	}
	return str;
}

void Sort(vector<int> &nums) {
	sort(begin(nums), end(nums));
}
//
//int main() {
//	cout << Reverse("loop") << endl;
//	vector<int> dupa = { 3, 2, 1 };
//	Sort(dupa);
//	cout << dupa << endl;
//	return 0;
//}
