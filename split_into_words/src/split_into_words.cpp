#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

vector<string> SplitIntoWords(const string &str) {
	// ������� ������, � ������� ����� ��������� �����
	vector<string> result;

	// ��� ��� ��������� ����� ������������ ������� �� �������� ����� ������
	// str_begin ����� ��������� ������
	auto str_begin = begin(str);
	// str_end ������ ����� ��������� �� ����� ������ (������� �� �����������)
	const auto str_end = end(str);

	// � ����� ��� ������� ����������, ��� ��� ������������ ������ ��������� ��� �
	// ������� break
	while (true) {

		// ������� ������ ������ � ������� ������� ������
		auto it = find(str_begin, str_end, ' ');

		// ������������ [str_begin, it) � ��������� �����
		result.push_back(string(str_begin, it));

		if (it == str_end) {
			// ���� �������� ������ ���, ���� ���� ���������.
			// ��������� ����� ��� ���������
			break;
		} else {
			// ����� ������ ������ ����� ������� � ������ ���������� �����.
			// ���� � �������� str_begin
			str_begin = it + 1;
		}

	}

	return result;
}

int main() {
	string s = "C pook hook";

	vector<string> words = SplitIntoWords(s);
	cout << words.size() << " ";
	for (auto it = begin(words); it != end(words); ++it) {
		if (it != begin(words)) {
			cout << "/";
		}
		cout << *it;
	}
	cout << endl;

	return 0;
}
