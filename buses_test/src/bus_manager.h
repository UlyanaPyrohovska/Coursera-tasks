/*
 * bus_manager.h
 *
 *  Created on: 25 лип. 2020 р.
 *      Author: Ulyana
 */

#ifndef BUS_MANAGER_H_
#define BUS_MANAGER_H_
#pragma once

#include "responses.h"

class BusManager {
public:
	void AddBus(const string &bus, const vector<string> &stops);
	BusesForStopResponse GetBusesForStop(const string &stop) const;
	StopsForBusResponse GetStopsForBus(const string &bus) const;
	AllBusesResponse GetAllBuses() const;
private:
	map<string, vector<string>> buses_to_stops, stops_to_buses;
};
#endif /* BUS_MANAGER_H_ */
