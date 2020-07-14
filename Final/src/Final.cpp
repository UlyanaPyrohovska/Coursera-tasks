#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>

using namespace std;

class Date {
public:
	Date() {
		Y = 0;
		M = 0;
		D = 0;
	}
	Date(int Year, int Month, int Day) {
		if (Month <= 0 || Month > 12) {
			cout << "Month value is invalid: " << Month << endl;
			Y = 0;
			M = 0;
			D = 0;
		} else {
			if (Day <= 0 || Day > 31) {
				cout << "Day value is invalid: " << Day << endl;
				Y = 0;
				M = 0;
				D = 0;
			} else {
				Y = Year;
				M = Month;
				D = Day;
			}
		}
	}
	int GetYear() const {
		return Y;
	}
	int GetMonth() const {
		return M;
	}
	int GetDay() const {
		return D;
	}
private:
	int D;
	int M;
	int Y;
};

bool operator<(const Date &lhs, const Date &rhs) {
	if (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth()) {
		return lhs.GetDay() < rhs.GetDay();
	} else {
		if (lhs.GetYear() == rhs.GetYear()) {
			return lhs.GetMonth() < rhs.GetMonth();
		} else {
			return lhs.GetYear() < rhs.GetYear();
		}
	}
}

class Database {
public:
	void AddEvent(const Date &date, const string &event) {
		data[date].insert(event);
	}
	void DeleteEvent(const Date &date, const string &event) {
		auto it = data.find(date);
		if (it != data.cend()) {
			auto it2 = it->second.find(event);
			if (it2 != it->second.cend()) {
				it->second.erase(it2);
				cout << "Deleted successfully" << endl;
			} else {
				cout << "Event not found" << endl;
			}
		} else {
			cout << "Event not found" << endl;
		}
	}
	void DeleteDate(const Date &date) {
		auto it = data.find(date);
		if (it != data.cend()) {
			cout << "Deleted " << it->second.size() << " events" << endl;
			data.erase(date);
		} else {
			cout << "Deleted 0 events" << endl;
		}
	}

	void Find(const Date &date) const {
		auto it = data.find(date);
		if (it != data.cend()) {
			for (const string &str : it->second) {
				cout << str << endl;
			}
		}
	}

	void Print() const {
		for (auto it : data) {
			for (auto it1 : it.second) {
				cout << setw(4) << setfill('0') << it.first.GetYear() << "-"
						<< setw(2) << it.first.GetMonth() << "-" << setw(2)
						<< it.first.GetDay();
				cout << " " << it1 << endl;
			}
		}
	}
private:
	map<Date, set<string>> data;
};

Date pick(string s) {
	int y, m, d;
	char ch1, ch2;
	string isnull;
	istringstream stream(s);
	if (stream >> y && stream >> ch1 && stream >> m && stream >> ch2
			&& stream >> d && !(stream >> isnull)) {
		if (ch1 == '-' && ch2 == '-') {
			return Date(y, m, d);
		}
	} else {
		cout << "Wrong date format: " << s << endl;
	}
	return Date();
}
bool operator ==(Date a, Date b) {
	if (a.GetDay() == b.GetDay() && a.GetMonth() == b.GetMonth()
			&& a.GetYear() == b.GetYear()) {
		return true;
	} else
		return false;
}
int main() {
	vector<string> shit;
	string s("");
	string Event("");
	string data1;

	Database db;
	string command;
	while (getline(cin, command)) {
		{
			shit.clear();
			istringstream stream(command);
			while (getline(stream, s, ' ')) {
				shit.push_back(s);
			}
		}
		Date data;
		if (shit.size() >= 1) {
			if (shit[0] == "Add") {
				data = pick(shit[1]);
				if (data.GetDay() == 0 && data.GetMonth() == 0
						&& data.GetYear() == 0) {
					continue;
				} else {
					db.AddEvent(data, shit[2]);
				}
			} else {
				if (shit[0] == "Del") {
					data = pick(shit[1]);
					if (data.GetDay() == 0 && data.GetMonth() == 0
							&& data.GetYear() == 0) {
						continue;
					} else {
						if (shit.size() == 2) {
							db.DeleteDate(data);
						} else {
							db.DeleteEvent(data, shit[2]);
						}
					}
				} else {
					if (shit[0] == "Find") {
						data = pick(shit[1]);
						if (data.GetDay() == 0 && data.GetMonth() == 0
								&& data.GetYear() == 0) {
							continue;
						} else {
							db.Find(data);
						}
					} else {
						if (shit[0] == "Print") {
							db.Print();
						} else {
							if (shit.size() == 0) {
								cout << endl;
							} else {
								cout << "Unknown command: " << shit[0] << endl;
							}
						}
					}
				}
			}
		}
		shit.clear();
	}
}
