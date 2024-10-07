#ifndef Archetype_H
#define Archetype_H

#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <ctime>
#include <string>
#include <vector>
#include <map>
#include "Dna.h"
using namespace std;


class Archetypes {
    public:
    class Archetype {
        public:
        string name = "Base";
        vector<double> gen_diff = {.95, .81, .92, 1.1, 1, 1, 1, 1, 1, 1.2, 1.05, 1}; // generic values
        vector<double> inital_values = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; // generic values;
        vector<double> desire_m = {6, 10, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
        vector<double> desire_mc = {.1, .01, .01, .01, .01, .01, .01, .01, .2, .01, .01, .01};
        vector<double> desire_f = {14, 30, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
        vector<double> desire_fc = {.2, .01, .01, .01, .01, .01, .01, .01, .2, .01, .01, .01};



        Archetype() {};
        Archetype(vector<double> initial, vector<double> gender_diff, string name) {
            this->inital_values.clear();
            this->gen_diff.clear();
            for (auto elem : initial) {
                this->inital_values.push_back(elem);
            }
            for (auto elem : gender_diff) {
                this->gen_diff.push_back(elem);
            }
            this->name = name;
        }


    };

    map<string, Archetype*> mapo;

    Archetypes() {
        
        vector<double> lb_iv = {1.087, 1.133, 1.040, 1.067, .867, 1.2, 1.02, .8, .8, 1, .933, .933}; // large boi values;
        vector<double> lb_gd = {.95, .79, .92, 1.1, 1, 1, 1, 1, 1, 1.2, 1.05, 1}; // large boi values
        Archetype* largeBois = new Archetype(lb_iv, lb_gd, "Large Bois");
        mapo.insert(std::pair("large", largeBois));

        Archetype* regular = new Archetype();
        mapo.insert(std::pair("regular", regular));

        vector<double> ln_iv = {1.087, .933, 1.133, 1.133, .867, .8, 1.05, .9, .5, 1, .933, .933}; // lanky boi values;
        vector<double> ln_gd = {.95, .79, .92, 1.1, 1, 1, 1, 1, 1, 1.2, 1.05, 1}; // lanky boi values
        Archetype* lanky = new Archetype(ln_iv, ln_gd, "Lanky");
        mapo.insert(std::pair("lanky", lanky));


        vector<double> m_iv = {1, .867, .933, .933, .933, .933, 1.133, 1, 1, 1, .933, .933}; // mantis values;
        vector<double> m_gd = {1.029, 1.077, 1.286, 1.286, 1.214, 1.143, 1, 1.067, 1, 1.077, 1, 1}; // mantis values
        Archetype* mantis = new Archetype(m_iv, m_gd, "Mantis");
        mapo.insert(std::pair("mantis", mantis));

        vector<double> dw_iv = {.85, 1.2, .933, .933, .933, .933, 1.133, 1, 0.08, 1, .933, .933}; // dwarf values;
        vector<double> dw_gd = {.95, .90, 1,1 , 1, 1, 1, 1.067, 1, 1.077, 1, 1}; // dwarf values
        Archetype* dwarf = new Archetype(dw_iv, dw_gd, "Half Blood");
        mapo.insert(std::pair("dwarf", dwarf));
    }
    




};

#endif