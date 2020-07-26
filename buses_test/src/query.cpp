#include "query.h"

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
