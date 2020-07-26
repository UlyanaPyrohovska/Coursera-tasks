#ifndef QUERY_H_
#define QUERY_H_
#pragma once
#include <iostream>
#include <string>
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
istream& operator >>(istream &is, Query &q);
#endif /* QUERY_H_ */
