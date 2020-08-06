#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void PrintVectorPart(const vector<int> &numbers) {
	auto item = find_if(begin(numbers), end(numbers), [](int num) {
		return num < 0;
	});
	while (item > begin(numbers)) {
		item--;
		cout << *item << " ";
	}
}

int main() {
	PrintVectorPart( { 6, 1, 8, -5, 4 });
	cout << endl;
	PrintVectorPart( { -6, 1, 8, -5, 4 });  // ничего не выведется
	cout << endl;
	PrintVectorPart( { 6, 1, 8, 5, 4 });
	cout << endl;
	return 0;
}

