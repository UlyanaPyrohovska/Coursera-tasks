#include <iostream>
using namespace std;

int main() {
	int N = 0;
	uint64_t R = 0;
	uint64_t W = 0;
	uint64_t H = 0;
	uint64_t D = 0;
	uint64_t sum = 0;
	cin >> N >> R;
	for (int i = 0; i < N; i++) {
		cin >> W >> H >> D;
		uint64_t lop = W * H * D;
		sum += lop * R;
	}
	cout << sum << endl;
	return 0;
}
