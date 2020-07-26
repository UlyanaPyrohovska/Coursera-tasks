#include "responses.h"

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
