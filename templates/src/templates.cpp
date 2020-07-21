#include <vector>
#include <map>
#include <iostream>
#include <utility>
using namespace std;

template<class first, class second> pair<first, second> operator*(
		const pair<first, second> &p1, const pair<first, second> &p2);
template<typename key, typename value> map<key, value> operator *(
		const map<key, value> t1, const map<key, value> t2);

template<typename T> vector<T> operator *(const vector<T> &v1,
		const vector<T> &v2);

template<class T> auto Sqr(const T &x);

template<class T> auto Sqr(const T &x) {
	return x * x;
}
template<class first, class second>
pair<first, second> operator*(const pair<first, second> &p1,
		const pair<first, second> &p2) {
	pair<first, second> p3;
	p3.first = Sqr(p1.first);
	p3.second = Sqr(p1.second);
	return p3;
}
template<typename T>
vector<T> operator *(const vector<T> &v1, const vector<T> &v2) {
	vector<T> v3(v1.size());
	int j = 0;
	for (auto it : v1) {
		v3[j] = Sqr(it);
		j++;
	}
	return v3;
}
template<typename key, typename value>
map<key, value> operator *(const map<key, value> t1, const map<key, value> t2) {
	map<key, value> m3 = t1;
	for (auto it : t1) {
		m3.at(it.first) = Sqr(it.second);
	}
	return m3;
}
int main() {
	// Пример вызова функции
	vector<int> v = { 1, 2, 3 };
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = { { 4, { 2, 2 } }, { 7, { 4, 3 } } };
	cout << "map of pairs:" << endl;
	for (const auto &x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second
				<< endl;
	}
}
