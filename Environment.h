#ifndef Environment_H
#define Environment_H
#include "People.h"

class Environment {
    public:
    int year = 0;

    int gridsize = 0;
    class Sector {
        public:
        PossibleFoods* foods = new PossibleFoods();

        Sec* sec = nullptr;

        string name = "base";
        Peoples* peeps;
        int year = 0;

        // Unlocked knowledge
    
        Sector(string name = "base") {
            sec = new Sec();
            peeps = new Peoples();
        };
        Sector(string name, double temp, double sun, double soil) {
            this->name = name;
            sec = new Sec(temp, sun, soil);
            peeps = new Peoples();
        };

        void simulate(int n, int& year) {
            int starting = peeps->alive_pop();
            cout << "Sector simulate call" << endl;
            peeps->simulate(n, this->year, sec);
            int ending = peeps->alive_pop();
            cout << "growth rate: " << (ending - starting)/(starting*1.0) * 100 << "%" << endl;
        };
    };

    Sector* mapping[2][2];
    map<string, Sector*> storage;

    Environment(int gridsize_) : gridsize(gridsize_) {
        mapping[0][0] = new Sector("meadow");
        mapping[1][0] = new Sector("tundra", 60, 10, 20);
        mapping[0][1] = new Sector("safari", 80, 80, 45);
        mapping[1][1] = new Sector("grassland", 72, 50, 90);

        storage["meadow"] = mapping[0][0];
        storage["tundra"] = mapping[1][0];
        storage["safari"] = mapping[0][1];
        storage["grassland"] = mapping[1][1];
    }



    ~Environment() {
        for (int i = 0; i < gridsize; ++i) {
            for (int j = 0; j < gridsize; ++j) {
                delete mapping[i][j];
            }
        }
    }

    void simulate(int n) {

        // for (auto& elem : storage) {
        //     cout << "Environment simulate call" << endl;
        //     elem.second->simulate(n, year);
        //     year += n;
        // }

        mapping[0][0]->simulate(n, year);
        mapping[0][1]->simulate(n, year);
        mapping[1][0]->simulate(n, year);
        mapping[1][1]->simulate(n, year);

        year += n;
    }
};

#endif