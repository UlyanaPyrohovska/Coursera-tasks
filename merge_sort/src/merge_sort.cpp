#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if (range_end - range_begin < 2) {
		return;
	}
	vector<typename RandomIt::value_type> ours(range_begin, range_end);
	RandomIt middle = ours.begin() + (ours.end() - ours.begin()) / 2;
	MergeSort(ours.begin(), middle);
	MergeSort(middle, ours.end());
	merge(ours.begin(), middle, middle, ours.end(), range_begin);
}

int main() {
	vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1, 5 };
	MergeSort(begin(v), end(v));
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;
	return 0;
}
