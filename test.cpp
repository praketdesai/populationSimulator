#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <ctime>
#include <string>
#include <vector>
#include "Dna.h"
#include "Archetype.h"
#include "Environment.h"

using namespace std;

int main() {
    Environment env = Environment(2);
    vector<Peoples*> maping = {env.mapping[0][0]->peeps, env.mapping[0][1]->peeps, env.mapping[1][0]->peeps, env.mapping[1][1]->peeps};
    Peoples* peeps = env.mapping[0][0]->peeps;
    for (auto& peep : maping) {
        for (int i = 0; i < 5000; i++) {
            peep->createPerson("large", 20, "black");
            peep->createPerson("lanky", 20, "nether");
            peep->createPerson("large", 20, "brown");
            peep->createPerson("regular", 20, "white");
            peep->createPerson("mantis", 20, "matriarch");
            peep->createPerson("dwarf", 20, "dwarf");
        }
    }


    

    // for (auto elem : peeps->people) {
    //     // elem->print_actual();
    //     for (int i = 0; i < 10; i++) {
    //         // elem->print_actual();
    //         env.envo[0]->simulate(10);
    //     }
    //     // elem->print_actual();
        
    // }
    // peeps->print_death_causes();
    
    char input;
    cout << "your options: \n r: simulate n years \n m: change sectors \n d: print demographics of the current sector \n p: print an individual person \n h: print the top people of a certain metric \n f: print someones children \n a: print someones parents \n u: print the stats of the academics \n s: save the current sector to a file \n";

    cin >> input;
    
    while (input != 'q') {
        cout << endl << "year: " << env.mapping[0][0]->year << endl;
        if (input == 'm'){
            int in;
            cout << "what sector do you want to view (0, 1, 2, 3): ";
            cin >> in;

            cout << "welcome to the " << env.mapping[in/2][in%2]->name << "\n";
            peeps = maping[in];
        } else if (input == 'r'){

            int in;

            cout << "many years to simulate: ";
            cin >> in;
            env.simulate(in);
            int count = peeps->print_death_causes();
            // peeps->print_military();

            cout << count << " people died in the last years" << endl;
            
        } else if (input == 'd') {
            peeps->demographics(peeps->people);
            // peeps->demographics(peeps->military, true);
           
        } else if (input == 'p') {
            int in;
            int detail;
            cout << "who do you want to print? ";
            cin >> in;
            cout << "what level of complexity in print : 0 for simple, 1 for full stats";
            cin >> detail;
            if (detail) {
                peeps->find_person(to_string(in))->print_actual();
            } else {
                peeps->print_person(to_string(in));
            }
        } else if (input == 'h') {
            int in;
            int al;
            int met;
            int detail;
            cout << "how many people should be returned ";
            cin >> in;
            cout << "alive or alive+dead ";
            cin  >> al;
            cout << "what metric do you want to sort by " << endl;
            cout << "0 : height" << endl;
            cout << "1 : strength" << endl;
            cout << "2 : speed" << endl;
            cout << "3 : stamina" << endl;
            cout << "4 : charisma" << endl;
            cout << "5 : weight" << endl;
            cout << "6 : will power" << endl;
            cout << "7 : intel" << endl;
            cout << "8 : melanin" << endl;
            cout << "9 : parental" << endl;
            cout << "10: memory" << endl;
            cout << "11: dexterity" << endl << endl;

            cin >> met;
            cout << "0 for detail, 1 for compact ";
            cin >> detail;
            if (detail != 0 && detail != 1) continue;
            peeps->highest_in_the_room(in, al, met, detail);
            
        } else if (input == 'f') {
            int in;
            cout << "whose children do you want to see " << endl;
            cin >> in;
            peeps->family_tree(to_string(in));
        } else if (input == 'a') {
            int in;
            cout << "whose parents do you want to see " << endl;
            cin >> in;
            peeps->print_parents(to_string(in));
        } else if (input == 'u') {
            cout << "academics stats" << '\n';
            peeps->demographics(peeps->academics);
        } else if (input == 's') {
            cout << "what file do you want to print to?" << endl;
            string filename;
            cin >> filename;
            peeps->populate_data(filename);
        }
        cout << "Grand Population: " << peeps->people.size() << endl;
        cout << "Current Population: " << peeps->alive_pop() << endl;
        cout << "your options: \n r: simulate n years \n m: change sectors \n d: print demographics of the current sector \n p: print an individual person \n h: print the top people of a certain metric \n f: print someones children \n a: print someones parents \n u: print the stats of the academics \n s: save the current sector to a file \n";

        cin >> input;


    }
}