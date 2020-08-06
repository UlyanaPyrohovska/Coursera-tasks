#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n = 0;
	vector<int> poop;
	cin >> n;
	for (int i = n; i > 0; i--) {
		poop.push_back(i);
	}
	do {
		for (auto item : poop) {
			cout << item << ' ';
		}
		cout << endl;
	} while (prev_permutation(begin(poop), end(poop)));
	return 0;
}
