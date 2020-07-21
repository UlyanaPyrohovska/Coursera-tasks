#include <iostream>
#include <map>
#include <string>
#include <exception>
using namespace std;

template<typename key, typename value>
value& GetRefStrict(map<key, value> &m, key find) {
	if (m.count(find) == 0) {
		throw runtime_error("");
	}
	return m[find];
}

int main() {
	try {
		map<int, string> m = { { 0, "value" } };
		string &item = GetRefStrict(m, 0);
		item = "newvalue";
		cout << m[0] << endl;
	} catch (exception &ex) {
	}

	return 0;
}
