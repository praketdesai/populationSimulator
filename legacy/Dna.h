#ifndef Dna_H
#define Dna_H

#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <ctime>
#include <string>
#include <vector>
#include "Gene.h"
using namespace std;

// Weight formula before base weight is 150 - 5*(heightPotential - 69)

class Dna {
    public:
    vector<Gene*> seq;
    vector<Gene*> des;
    bool gender;
    int gender_chance = 50; // chance that offspring will be a male;
    vector<string> stat_names = {"Height Potential", "Base Strength", "Base Speed", "Base Stamina", "Base Charisma",
     "Base Weight", "Will Power", "Base Intelligence", "Melanin", "Parental Instinct", "Compassion", "Dexterity"};
    vector<double> base_stats = {69, 70, 75, 75, 75, 150, 75, 75, 75, 65, 75, 75};
    vector<double> actual_stats = {0,0,0,0,0,0,0,0,0,0,0,0};



    Dna(vector<Gene*> seqr, bool gender, bool metric = true) : gender(gender) {
        if (metric) {
            for (auto gene : seqr) {
                // cout << "Here" << endl;
                this->seq.push_back(new Gene(gene->allele1, gene->allele2));
            }
            for (int i = 0; i < 12; i++) {
                if (i == 1) { 
                    actual_stats[5] = (base_stats[5] + ((base_stats[0] - 69) * 5)) * seq[5]->phenotypic_expression(gender);
                    actual_stats[1] = (base_stats[1] + (actual_stats[5]-160)/2.5) * seq[1]->phenotypic_expression(gender);
                    actual_stats[2] = (base_stats[2] - (actual_stats[5]-160)/2) * seq[2]->phenotypic_expression(gender);
                    actual_stats[3] = (base_stats[3] - (actual_stats[5]-160)/1.75) * seq[3]->phenotypic_expression(gender);
                    continue;
                } else if (i == 2 || i == 3 || i == 5) {
                    continue;
                }
                actual_stats[i] = base_stats[i] * seq[i]->phenotypic_expression(gender);
            }
        } else {
            for (auto gene : seqr) {
                // cout << "Here" << endl;
                this->seq.push_back(new Gene(gene->allele1, gene->allele2));
            }
            for (int i = 0; i < 12; i++) {
                actual_stats[i] = seq[i]->phenotypic_expression(gender);
            }
        }
    };

    Dna(Dna* par1, Dna* par2, bool metric = true) {
        // cout << "here" << endl;
        for (int i = 0; i < par1->seq.size(); i++) {
            seq.push_back(new Gene(par1->seq[i], par2->seq[i])); // creating a new gene for each of the characteristics
        }


        if (metric) {
            random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> distribution(0, 200);

            this->gender = distribution(gen) < (par1->gender_chance + par2->gender_chance);

            this->gender_chance = (par1->gender_chance + par2->gender_chance)/2 + distribution(gen)/100 - 1;
            for (int i = 0; i < 12; i++) {
                if (i == 1) { 
                    actual_stats[5] = (base_stats[5] + ((base_stats[0] - 69) * 5)) * seq[5]->phenotypic_expression(gender);
                    actual_stats[1] = (base_stats[1] + (actual_stats[5]-160)/2.5) * seq[1]->phenotypic_expression(gender);
                    actual_stats[2] = (base_stats[2] - (actual_stats[5]-160)/2) * seq[2]->phenotypic_expression(gender);
                    actual_stats[3] = (base_stats[3] - (actual_stats[5]-160)/1.75) * seq[3]->phenotypic_expression(gender);
                    continue;
                } else if (i == 2 || i == 3 || i == 5) {
                    continue;
                }
                actual_stats[i] = base_stats[i] * seq[i]->phenotypic_expression(gender);
            }
        } else {
            for (int i = 0; i < 12; i++) {
                actual_stats[i] = seq[i]->phenotypic_expression(gender);
            }
        }
        // cout << "end" << endl;
    }

    ~Dna() {
        for (auto gene : seq) {
            delete gene;
        }
    }

    void print_base() {
        cout << "The person is ";
        gender ? cout << "male" : cout << "female";
        cout << endl;
        for (int i = 0; i < 12; i++) {
            // cout << seq[i]->phenotypic_expression(gender)  << endl;
            if (i == 1) { 
                double weight = (base_stats[5] + ((base_stats[0] - 69) * 5)) * seq[5]->phenotypic_expression(gender);
                double strength = (base_stats[1] + (weight-160)/2.5) * seq[1]->phenotypic_expression(gender);
                double speed = (base_stats[2] - (weight-160)/2) * seq[2]->phenotypic_expression(gender);
                double stamina = (base_stats[3] - (weight-160)/1.75) * seq[3]->phenotypic_expression(gender);
                cout << stat_names[1] << ": "<< strength << endl;
                cout << stat_names[2] << ": "<< speed << endl;
                cout << stat_names[3] << ": "<< stamina << endl;
                cout << stat_names[5] << ": "<< weight << endl;
                continue;
            } else if (i == 2 || i == 3 || i == 5) {
                continue;
            }
            cout << stat_names[i] << ": "<< base_stats[i] * seq[i]->phenotypic_expression(gender) << endl;
        }
        cout << endl;
    }
};

#endif