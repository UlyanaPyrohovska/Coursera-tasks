#include <iostream>
#include <vector>
using namespace std;

void Print(vector<int> y) {
	for (int l : y)
		cout << l << " ";
	cout << endl;
}

int main() {
	int k = 0;
	int64_t sum = 0;
	int av = 0;

	cin >> k;
	vector<int64_t> temp(k);
	vector<int> lup;

	for (int64_t &i : temp)
		cin >> i;

	for (size_t i = 0; i < temp.size(); i++) {
		sum += temp[i];
	}

	av = sum / k;

	for (size_t i = 0; i < temp.size(); i++) {
		if (temp[i] > av)
			lup.push_back(i);
	}
	cout << lup.size() << endl;
	Print(lup);
	return 0;
}
