#ifndef Gene_H
#define Gene_H

#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <ctime>
#include <string>
#include <vector>
#include "Allele.h"
using namespace std;

class Gene {
    public:
    vector<Allele*> all;
    Allele* allele1;
    Allele* allele2;

    Gene(Allele* all1, Allele* all2) : allele1(all1), allele2(all2)  {
        // cout << "IS this function called, if so good, allele1 allele2 function called" << endl;
        all.push_back(all1);
        all.push_back(all2);
    };
    Gene(Gene* par1, Gene* par2) {
        random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(0, 1);
        int pa1 = distribution(gen);
        int pa2= distribution(gen);

        Allele* temp = par1->all[pa1];
        Allele* al1 = new Allele(temp->expression, temp->mfratio, temp->dominant);
        this->allele1 = al1;
        this->allele1->mutate();


        Allele* temp2 = par2->all[pa2];
        Allele* al2 = new Allele(temp2->expression, temp2->mfratio, temp2->dominant);
        this->allele2 = al2;
        this->allele2->mutate();

        all.push_back(allele1);
        all.push_back(allele2);
    }

    ~Gene() {
        for (auto elem : this->all) {
            delete elem;
        }
    }

    double phenotypic_expression(bool gender) {
        bool dom1 = allele1->dominant;
        bool dom2 = allele1->dominant;
        double pre_gender = 0.0;
        double gen_mod = 1;
        if (dom1 xor dom2) {
            if (dom1) {
                pre_gender = allele1->expression;

                if (!gender) {
                    gen_mod = allele1->mfratio;
                }
            } else {
                pre_gender = allele2->expression;
                
                if (!gender) {
                    gen_mod = allele2->mfratio;
                }
            }
        } else {
            pre_gender = (allele1->expression + allele2->expression)/2.0;
            if (!gender) {
                gen_mod = (allele1->mfratio + allele2->mfratio)/2.0;
            }
            
        }
        return pre_gender * gen_mod;
    }


};

#endif