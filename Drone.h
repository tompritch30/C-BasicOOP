//
// Created by thoma on 22/04/2024.
//

#ifndef PPP_DRONE_H
#define PPP_DRONE_H


class Drone {

public:
    explicit Drone(double lat, double longlitude, double altitude);

    void flyTo(double lat, double lon, double alt);

    void setCruisingAlt(double alt);

    void returnHome();
};


#endif //PPP_DRONE_H
