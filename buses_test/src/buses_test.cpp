#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

enum class QueryType {
	NewBus, BusesForStop, StopsForBus, AllBuses
};

struct Query {
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

istream& operator >>(istream &is, Query &q) {
	int sup = 0;
	string s;
	is >> s;
	q.stops.clear();
	if (s == "NEW_BUS") {
		q.type = QueryType::NewBus;
	} else {
		if (s == "BUSES_FOR_STOP") {
			q.type = QueryType::BusesForStop;
		} else {
			if (s == "STOPS_FOR_BUS") {
				q.type = QueryType::StopsForBus;
			} else {
				if (s == "ALL_BUSES") {
					q.type = QueryType::AllBuses;
				}
			}
		}
	}
	if (q.type == QueryType::NewBus) {
		is >> q.bus;
		is >> sup;
		for (int i = 0; i < sup; i++) {
			is >> q.stop;
			q.stops.push_back(q.stop);
		}
	} else {
		if (q.type == QueryType::BusesForStop) {
			is >> q.stop;
			q.stops.clear();
		} else {
			if (q.type == QueryType::StopsForBus) {
				is >> q.bus;
				q.stops.clear();
			}
			q.stops.clear();
		}
	}
	return is;
}

struct BusesForStopResponse {
	vector<string> busesforstop;
};

ostream& operator <<(ostream &os, const BusesForStopResponse &r) {
	if (r.busesforstop.empty()) {
		os << "No stop" << endl;
	} else {
		for (const string &bus : r.busesforstop) {
			os << bus << " ";
		}
		os << endl;
	}
	return os;
}

struct StopsForBusResponse {
	string bus;
	vector<string> stopsforbuses;
	map<string, vector<string>> busesfor;
};

ostream& operator <<(ostream &os, const StopsForBusResponse &r) {
	if (r.stopsforbuses.empty()) {
		os << "No bus" << endl;
	} else {
		for (const string &stop : r.stopsforbuses) {
			os << "Stop " << stop << ": ";
			if (r.busesfor.at(stop).size() == 1) {
				os << "no interchange";
			} else {
				for (const string &other_bus : r.busesfor.at(stop)) {
					if (r.bus != other_bus) {
						os << other_bus << " ";
					}
				}
			}
			os << endl;
		}
	}
	return os;
}

struct AllBusesResponse {
	map<string, vector<string>> all;
};

ostream& operator <<(ostream &os, const AllBusesResponse &r) {
	if (r.all.empty()) {
		os << "No buses" << endl;
	} else {
		for (const auto &item : r.all) {
			os << "Bus " << item.first << ": ";
			for (const string &stop : item.second) {
				os << stop << " ";
			}
			os << endl;
		}
	}
	return os;
}

class BusManager {
public:
	void AddBus(const string &bus, const vector<string> &stops) {
		buses_to_stops[bus] = stops;
		for (const auto &item : stops) {
			stops_to_buses[item].push_back(bus);
		}
	}

	BusesForStopResponse GetBusesForStop(const string &stop) const {
		BusesForStopResponse basa;
		if (stops_to_buses.count(stop) == 0) {
			return basa;
		} else {
			basa.busesforstop = stops_to_buses.at(stop);
			return basa;
		}
	}
	StopsForBusResponse GetStopsForBus(const string &bus) const {
		StopsForBusResponse basa;
		basa.bus = bus;
		if (buses_to_stops.count(bus) == 0) {
			return basa;
		} else {
			basa.stopsforbuses = buses_to_stops.at(bus);
			for (auto item : buses_to_stops.at(bus)) {
				if (stops_to_buses.count(item) == 0) {
					continue;
				} else {
					basa.busesfor[item] = stops_to_buses.at(item);
				}
			}
			return basa;
		}

	}

	AllBusesResponse GetAllBuses() const {
		AllBusesResponse basa;
		basa.all = buses_to_stops;
		return basa;
	}
private:
	map<string, vector<string>> buses_to_stops, stops_to_buses;
};

int main() {
//	int q;
//	cin >> q;
//
//	map<string, vector<string>> buses_to_stops, stops_to_buses;
//
//	for (int i = 0; i < q; ++i) {
//		string operation_code;
//		cin >> operation_code;
//
//		if (operation_code == "NEW_BUS") {
//
//			string bus;
//			cin >> bus;
//			int stop_count;
//			cin >> stop_count;
//			vector<string> &stops = buses_to_stops[bus];
//			stops.resize(stop_count);
//			for (string &stop : stops) {
//				cin >> stop;
//				stops_to_buses[stop].push_back(bus);
//			}
//
//		} else if (operation_code == "BUSES_FOR_STOP") {
//
//			string stop;
//			cin >> stop;
//			if (stops_to_buses.count(stop) == 0) {
//				cout << "No stop" << endl;
//			} else {
//				for (const string &bus : stops_to_buses[stop]) {
//					cout << bus << " ";
//				}
//				cout << endl;
//			}
//
//		} else if (operation_code == "STOPS_FOR_BUS") {
//
//			string bus;
//			cin >> bus;
//			if (buses_to_stops.count(bus) == 0) {
//				cout << "No bus" << endl;
//			} else {
//				for (const string &stop : buses_to_stops[bus]) {
//					cout << "Stop " << stop << ": ";
//					if (stops_to_buses[stop].size() == 1) {
//						cout << "no interchange";
//					} else {
//						for (const string &other_bus : stops_to_buses[stop]) {
//							if (bus != other_bus) {
//								cout << other_bus << " ";
//							}
//						}
//					}
//					cout << endl;
//				}
//			}
//
//		} else if (operation_code == "ALL_BUSES") {
//
//			if (buses_to_stops.empty()) {
//				cout << "No buses" << endl;
//			} else {
//				for (const auto &bus_item : buses_to_stops) {
//					cout << "Bus " << bus_item.first << ": ";
//					for (const string &stop : bus_item.second) {
//						cout << stop << " ";
//					}
//					cout << endl;
//				}
//			}
//
//		}
//	}
	int query_count;
	Query q;

	cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type) {
		case QueryType::NewBus:
			bm.AddBus(q.bus, q.stops);
			break;
		case QueryType::BusesForStop:
			cout << bm.GetBusesForStop(q.stop) << endl;
			break;
		case QueryType::StopsForBus:
			cout << bm.GetStopsForBus(q.bus) << endl;
			break;
		case QueryType::AllBuses:
			cout << bm.GetAllBuses() << endl;
			break;
		}
	}

	return 0;
}
