#ifndef ITEM_H
#define ITEM_H

#include <iostream>
using std::ostream;

#include <cmath>

#include <string>
using std::string;

using std::cout;
using std::endl;

class Item {

private:
    double latitude;
    double longitude;

    string id;
    int secsPastHour;

public:
    Item(const double latIn, const double longIn,
         const string & idIn, const int secsIn)
        : latitude(latIn), longitude(longIn),
          id(idIn), secsPastHour(secsIn) {
    }

    double distanceTo(const Item & other) const {

        static constexpr double PI = 3.14159265358979323846;
        static constexpr double R = 6373000;

        const double lat1 = latitude * (PI / 180.0);
        const double lon1 = longitude * (PI / 180.0);

        const double lat2 = other.latitude * (PI / 180.0);
        const double lon2 = other.longitude * (PI / 180.0);

        const double dlon = lon2 - lon1;
        const double dlat = lat2 - lat1;
        const double a = pow((sin(dlat/2)), 2) + cos(lat1) * cos(lat2) * pow((sin(dlon/2)), 2);
        const double c = 2 * atan2( sqrt(a), sqrt(1-a) );
        const double distance = R * c;

        return distance;
    }

    int getSecsPastHour() const {
        return secsPastHour;
    }

    void write(ostream & o) const {
        o << "{" << latitude << ", " << longitude << ", \"" << id << "\", " << secsPastHour << "}";
    }
};

ostream & operator<<(ostream & o, const Item & i) {
    i.write(o);
    return o;
}


// don't write any code below this line

#endif

