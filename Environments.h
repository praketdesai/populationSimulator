#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <ctime>
#include <string>
#include <vector>
#include "Dna.h"
#include "Archetype.h"
#include "People.h"

class Environments {
    public: //class to contain all the environments that are currently in action
    int year = 0;



    class Environment {
        public:
        int supported_population = 1500;
        string name = "base";
        int year = 0;
        double migration_chance = .02;
        Peoples* peoples = new Peoples();
        map<string, Encounter*> encount; // map from the encounter pointer to the base chance of that encounter occuring
        
        Environment() {
            peoples->encount = encount; // setting the pointers equal


            Encounter* cancer = new Encounter();
            cancer->type = "disease";

            encount["disease"] = cancer; //chance of cancer is .001;

            Encounter* accident = new Encounter();
            accident->type = "accident";

            Encounter* engine = new Encounter();
            engine->type = "engineering";

            encount["accident"] = accident;

            Encounter* food = new Encounter();
            food->type = "food";
            food->chance = 1;
            food->strength_diff = 80;
            food->speed_diff = 60;
            food->death_chance = .05; // affected by the differentials in strength and speed, only applied when food cannot be achieved;
            food->food = 500;
            food->nutrition_mult = .89; 

            encount["food_hunt"] = food;

            Encounter* food2 = new Encounter();
            food2->type = "food";
            food2->chance = 1;
            food2->strength_diff = 60;
            food2->speed_diff = 60;
            food2->death_chance = 0; // affected by the differentials in strength and speed, only applied when food cannot be achieved;
            food2->food = 400;
            food2->nutrition_mult = .75; 

            encount["food_grown"] = food2;

            Encounter* food3 = new Encounter();
            food3->type = "food";
            food3->chance = 1;
            food3->strength_diff = 80;
            food3->speed_diff = 80;
            food3->stamina_diff = 80;
            food3->death_chance = 0; // affected by the differentials in strength and speed, only applied when food cannot be achieved;
            food3->food = 1000;
            food3->nutrition_mult = .75; 

            encount["food_gather"] = food3;
        }

        

        double food_availabilty = .5;
        double nutrition_value = .97;
        double hostile_encounter_chance = .12;

        void simulate(int n = 1) { // simulates the protocal for n years
            int starting = peoples->alive_pop();
            peoples->simulate(n, year, encount, supported_population);
            int ending = peoples->alive_pop();
            cout << "growth rate: " << (ending - starting)/(starting*1.0) * 100 << "%" << endl;
            // while (n != 0) {
            //     year++;
            //     int childs = peoples->reproduction(year);
            //     // cout << "New Children: " << childs << endl;
            //     for (auto elem : peoples->people) {
            //         // run the enivironmenal factors here before aging, aging will weed out those who did not survive
            //         // for (int i = 0; i < 5; i++) {
            //         //     if (elem->age < 16) continue;
            //         //     elem->encounter(encount["food_gather"]);
            //         // }
            //         elem->work(encount);
            //         cout << "past here" << endl;
            //         elem->encounter(encount["disease"]);
            //         elem->encounter(encount["accident"]);
                    
            //         elem->aging_process();
            //     }
            //     n--;
            // }
        }

    };

    vector<Environment*> envo;

    // Environments contains pointers to all populations that exist in the program

    map<Peoples*, Environment*> mappy;

    Environments() {
        Environment* norm = new Environment();
        envo.push_back(norm);
    }

    void addEnvironment(Environment* env) {
        envo.push_back(env);
    }

    void immigration() {
        random_device rm;


    }

    void combat(Person* soldier1, Person* soldier2, int pressure) {

    };

    void war(Peoples* off, Peoples* def) {
        // should allow 2 v 1 combat, stats that matter here are strength, speed, dexterity, willpower? and stamina
        // calculate a pressure rating for the people with less soldiers

        // winner of the war takes a portion of the population of the opposing peoples.

        // Military* army = off->military;
    }

};