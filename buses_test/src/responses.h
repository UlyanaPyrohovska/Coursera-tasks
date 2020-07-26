#ifndef RESPONSES_H_
#define RESPONSES_H_
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
struct BusesForStopResponse {
	vector<string> busesforstop;
};
struct StopsForBusResponse {
	string bus;
	vector<string> stopsforbuses;
	map<string, vector<string>> busesfor;
};
struct AllBusesResponse {
	map<string, vector<string>> all;
};
ostream& operator <<(ostream &os, const BusesForStopResponse &r);
ostream& operator <<(ostream &os, const StopsForBusResponse &r);
ostream& operator <<(ostream &os, const AllBusesResponse &r);

#endif /* RESPONSES_H_ */
