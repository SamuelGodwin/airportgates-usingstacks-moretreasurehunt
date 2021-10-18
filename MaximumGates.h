#ifndef MAXIMUM_GATES_H
#define MAXIMUM_GATES_H

#include <vector>
using std::vector;

int maximumGates(vector<int> arrives, vector<int> departs) {

	int gatesUsed = 0;

	int arrivalMin = 0;
	int departureMin = 0;

	int maxGatesOpen = 0;

	// while there are still things in arrivals...
	while (arrives.size() != 0) {
		// find arrivalMin and departureMin.
		for (int x = 0; x < arrives.size(); x++) {
			if (arrives[x] < arrives[arrivalMin]) {arrivalMin = x;}

			if (departs[x] < departs[departureMin]) {departureMin = x;}
		}

		if (arrives[arrivalMin] < departs[departureMin]) {
			// remove arrivalMin from arrives and increment gatesUsed.
			arrives.erase(arrives.begin() + arrivalMin);
			gatesUsed++;

			// tracks highest number of gates used.
			if (gatesUsed > maxGatesOpen) {maxGatesOpen = gatesUsed;}
		}

		else {
			// remove departureMin from departs and decrement gatesUsed.
			departs.erase(departs.begin() + departureMin);
			gatesUsed--;
		}
	}
	return maxGatesOpen;
}

// Do not write any code below this line
#endif
