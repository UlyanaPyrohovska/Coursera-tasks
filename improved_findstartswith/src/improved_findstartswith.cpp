#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

template<typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin,
		RandomIt range_end, const string &prefix) {
	int siz = prefix.size();
	string pref = prefix;
	const auto iter = lower_bound(range_begin, range_end, pref);
	char next_prefix = static_cast<char>(pref[siz - 1] + 1);
	string nextik = pref;
	nextik[siz - 1] = next_prefix;
	const auto iter1 = lower_bound(range_begin, range_end, nextik);
	return {iter, iter1};
}

int main() {
	const vector<string> sorted_strings = { "a", "c", "d" };
	const auto mo_result = FindStartsWith(begin(sorted_strings),
			end(sorted_strings), "c");
	for (auto it = mo_result.first; it != mo_result.second; ++it) {
		cout << *it << " ";
	}
	cout << endl;

	const auto mt_result = FindStartsWith(begin(sorted_strings),
			end(sorted_strings), "mt");
	cout << (mt_result.first - begin(sorted_strings)) << " "
			<< (mt_result.second - begin(sorted_strings)) << endl;

	const auto na_result = FindStartsWith(begin(sorted_strings),
			end(sorted_strings), "na");
	cout << (na_result.first - begin(sorted_strings)) << " "
			<< (na_result.second - begin(sorted_strings)) << endl;

	return 0;
}
