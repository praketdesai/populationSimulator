#ifndef Encounter_H
#define Encounter_H

#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <ctime>
#include <string>
#include <vector>
using namespace std;
class Encounter {
    public:
    string type;
    double food = 0;
    double nutrition_mult = .72;
    double strength_diff = 60;
    double speed_diff = 60;
    double stamina_diff = 50;
    double intel_diff = 50;
    double dexterity_diff = 50;
    double weight_factor = 0;
    double height_factor = 0;
    double chance = .001;
    double death_chance = 1;

    Encounter() {};

};
#endif