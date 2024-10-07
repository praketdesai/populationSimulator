#ifndef ELEMENTAL_H
#define ELEMENTAL_H


class Power {
    double intensity = 100;
    double control = 100;
    double type1 = 88;
    double type2 = 74;

    double blast() {
        return intensity;
    }
};

class Fire: public Power {
    double smoke;
    double fire;
    

};

class Earth: public Power {
    double rock;
    double metal;
    double nature;

};

class Water: public Power {
    double ice;
    double water;

};

class Air: public Power {
    double lightning;
    double wind;

};

#endif