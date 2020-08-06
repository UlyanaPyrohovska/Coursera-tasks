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
	RandomIt tripple1 = ours.begin() + (ours.end() - ours.begin()) / 3;
	RandomIt tripple2 = tripple1 + (ours.end() - tripple1) / 2;
	MergeSort(ours.begin(), tripple1);
	MergeSort(tripple1, tripple2);
	MergeSort(tripple2, ours.end());
	vector<typename RandomIt::value_type> timing;
	merge(ours.begin(), tripple1, tripple1, tripple2, back_inserter(timing));
	merge(timing.begin(), timing.end(), tripple2, ours.end(), range_begin);
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
