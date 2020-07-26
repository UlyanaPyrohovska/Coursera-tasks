#pragma once
#include "bus_manager.h"

void BusManager::AddBus(const string &bus, const vector<string> &stops) {
	buses_to_stops[bus] = stops;
	for (const auto &item : stops) {
		stops_to_buses[item].push_back(bus);
	}
}
BusesForStopResponse BusManager::GetBusesForStop(const string &stop) const {
	BusesForStopResponse basa;
	if (stops_to_buses.count(stop) == 0) {
		return basa;
	} else {
		basa.busesforstop = stops_to_buses.at(stop);
		return basa;
	}
}
StopsForBusResponse BusManager::GetStopsForBus(const string &bus) const {
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
AllBusesResponse BusManager::GetAllBuses() const {
	AllBusesResponse basa;
	basa.all = buses_to_stops;
	return basa;
}
