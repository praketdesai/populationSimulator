#ifndef OBJECT_H
#define OBJECT_H
#include <vector>
#include <string>
using namespace std;
class Object { // wrapper for all types of objects, food items, weapons, artifacts etc

    public:
    Object() {};
    string name;

    virtual std::vector<double> gather(double desired) {
        //Object use protocol
        return {0,0};
    }
    

};

class Food : public Object{
    public:
    bool hostile = false;
    double abundance = .46;
    string name = "berries";
    double quantity = 150;
    int yearsTillExpire;
    double nutrition;
    bool cookable;
    bool cooked;
    double cook_multiplier;
    vector<double> diff =     { 70,  60, 60, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70};
    vector<double> diff_imp = {.05, .45, .5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};

    // flee success determined by speed and stamina
    // fight success determined by strength, speed, dexterity, stamina. Win results in the meat from the animal as well.


    Food(string type, double abundance_, bool hostile_) {
        name = type;
        abundance = abundance_;
        hostile = hostile_;
    }

    std::vector<double> gather(double desired) override {
        // returns the amount of food added in the first index, and the nutrition quality of the food in the next
        if (desired > quantity) {
            desired = quantity;
        }
        quantity -= desired;

        return {quantity, quantity * nutrition};
    }
};

// Gathering generates food, but while gathering there is chance of finding prey animal or predator animal and having to fight or flee.
class PossibleFoods {
    public:
    Food* gatherObject;
    Food* preyObject;
    Food* predatorObject;

    // map<string, Food*> everything;


};


#endif