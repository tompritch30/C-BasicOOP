#include <string>
#include <utility>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

class Pizza {
private:
    bool isCooked;
    int weight;

public:
    Pizza(int weight);
    void cook();

    int getWeight();
};

Pizza::Pizza(int _weight): weight(_weight), isCooked(false) {

}

void Pizza::cook() {
    cout << "Pizza is now cooked" << endl;
    weight *= 0.85;
    isCooked = true;
}

int Pizza::getWeight() {
    return weight;
}


class Drone {
private:
    enum Location{LAT, LON, ALT};
    double lat;
    double lon;
    double alt;
    int cruisingAlt;
    Pizza * load;
    map<Location, double> home;

    void releaseLoad();

    void flyOperation(double finalLat, double finalLon, double finalAlt);

public:
    explicit Drone(double _lat, double _lon, double _alt);
    void flyTo(double lat, double lon, double alt);

    void setCruisingAlt(double alt);

    void returnHome();

    bool addItem(Pizza* pizza);

};

Drone::Drone(double _lat, double _lon, double _alt) : lat(_lat), lon(_lon), alt(_alt), cruisingAlt(100) {
    home[LAT] = lat;
    home[LON] = lon;
    home[ALT] = alt;
}


void Drone::flyTo(double finalLat, double finalLon, double finalAlt) {
    if (load != nullptr) {
        flyOperation(finalLat, finalLon, finalAlt);

        releaseLoad();
    } else {
        cout << "Not flying without a load " << endl;
    }

}

void Drone::flyOperation(double finalLat, double finalLon, double finalAlt) {
    alt = cruisingAlt;
    cout << "Cruising at: " << cruisingAlt << endl;
    lat = finalLat;
    lon = finalLon;
    alt = finalAlt;
    cout << "Arrived at: " << lat << ":" << lon << " at altitude: " << alt << endl;
}

void Drone::setCruisingAlt(double newAlt) {
    cruisingAlt = newAlt;
}

void Drone::returnHome() {
    alt = cruisingAlt;
    flyOperation(home[LAT], home[LON], home[ALT]);
}

bool Drone::addItem(Pizza* pizza) {
    if (pizza->getWeight() < 500) {
        load = pizza;
        return true;
    }
    return false;
}

void Drone::releaseLoad() {
    cout << "Dropped load" << endl;
    load = nullptr;
}

//int main() {
//    // cout << "test";
//
//    Pizza margPizza = Pizza(512);
//    margPizza.cook();
//    double lat = 51.5010;
//    double lon = -0.1919;
//    double alt = 0.0;
//
//    Drone drone = Drone(lat,lon,alt);
//    bool canAddPizza = drone.addItem(&margPizza);
//    cout << (canAddPizza ? "added pizza" : "too heavy") << endl;
//
//    drone.flyTo(51.4988, -.1919, 31.5);
//    // release pizza?
//    drone.setCruisingAlt(80.0);
//    drone.returnHome();
//
//    return 0;
//};