#ifndef MAPOFITEMS_H
#define MAPOFITEMS_H

#include "Item.h"

#include <vector>
using std::vector;

class MapOfItems {

private:

	vector<Item> vectorOfItems;
	//vector<Item> vectorCopy;
	//vector<Item> tour;

	int currentTime = 0;

	int smallestNextTime = 3600;

public:

	void addItem(Item item) {
		vectorOfItems.push_back(item);
	}

	int size() {
		return vectorOfItems.size();
	}


	vector<Item> getTour(double walkingSpeed) {

		vector<Item> tour;
		vector<Item> vectorCopy = vectorOfItems;  // would this be resetting vector every time?

		while (currentTime < 3600) {

			while (vectorCopy.empty() == false) {

				Item nextAvailableItem = vectorCopy.front();

				// Checks every item at this point.
				int i;
				int indexWinner = 0;
				for (i = 0; i < vectorCopy.size(); i++) {
					if (vectorCopy[i].getSecsPastHour() < nextAvailableItem.getSecsPastHour()) {

						nextAvailableItem = vectorCopy[i];
						indexWinner = i;

					}
				}

				tour.push_back(nextAvailableItem);						// increase tour

				currentTime = nextAvailableItem.getSecsPastHour();		// increase currentTime	// = or +=?

				vectorCopy.erase(vectorCopy.begin() + indexWinner);		// erase element

				if (currentTime >= 3600) {
					return tour;
				}

				nextAvailableItem = vectorCopy.front();					// important reset nextAvailableItem to be something in vectorCopy
				Item nextAvailableItemNext = vectorCopy.front();
				int timeWOULDBeVisited;
				int timeWOULDBeVisitedSMALLEST;
				int indexToErase;


				while (vectorCopy.empty() == false) {

					timeWOULDBeVisitedSMALLEST = ((tour.back().distanceTo(vectorCopy.front())/walkingSpeed) + currentTime);

					if (timeWOULDBeVisitedSMALLEST >= 3600) {
						return tour;
					}

					int x;
					int indexWinner2;


					for (x = 0; x < vectorCopy.size(); x++) {

						timeWOULDBeVisited = ((tour.back().distanceTo(vectorCopy[x]))/walkingSpeed) + currentTime;

						if (timeWOULDBeVisited > (vectorCopy[x].getSecsPastHour() + 900)) { // IF VISIT WOULD BE TOO LATE, ITEM GONE...

							vectorCopy.erase(vectorCopy.begin()+x); // TOO LATE, WON'T BE NEEDED.
							nextAvailableItem = vectorCopy.front();	// important reset nextAvailableItem to be something in vectorCopy
							continue; // GET OUT OF LOOP HERE, GO TO NEXT ITERATION --- MUST MUST MUST

						}

						else if (timeWOULDBeVisited < vectorCopy[x].getSecsPastHour()) {	// IF VISIT WOULD BE TOO EARLY, WAIT FOR ITEM...

							//This is okay. but we would set visit(I)/timeWouldBeVisited to the time at which I appears.
							timeWOULDBeVisited = vectorCopy[x].getSecsPastHour();
							//currentTime = vectorCopy[i].getSecsPastHour();

						}

						if (timeWOULDBeVisited < timeWOULDBeVisitedSMALLEST) {

							timeWOULDBeVisitedSMALLEST = timeWOULDBeVisited;
							nextAvailableItem = vectorCopy[x];
							indexToErase = x;
						}

					}

					tour.push_back(nextAvailableItem);						// increase tour

					nextAvailableItem = vectorCopy.front();	// important reset nextAvailableItem to be something in vectorCopy

					if (timeWOULDBeVisitedSMALLEST >= 3600) {
						return tour;
					}


					currentTime = timeWOULDBeVisitedSMALLEST;				// increase currentTime

					vectorCopy.erase(vectorCopy.begin() + indexToErase);	// erase element

				}

				return tour;
			}

		}

	}

};

// don't write any code below this line

#endif
