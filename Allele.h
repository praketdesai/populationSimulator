#ifndef Allele_H
#define Allele_H

#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <ctime>
#include <string>
#include <vector>
using namespace std;


class Allele {

    public:

    double expression; // a number that multiplies by the base value (whatever that may be for whatever specific trait)
    double mfratio; // the ratio that is applied to the base value is the gender of the creature is f
    bool dominant; // is the allele dominant?
    double mut = 0.05;

    Allele(double expression, double mfratio, bool dominant) {
        this->expression = expression;
        this->mfratio = mfratio;
        this->dominant = dominant;
    } 
    // need a copy constructor

    Allele(Allele& other) {
        this->expression = other.expression;
        this->dominant = other.dominant;
        this->mfratio = other.mfratio;
    }

    Allele& operator=(Allele& other) {
        Allele* allele = new Allele(other.expression, other.mfratio, other.dominant);
        return *allele;
    }

    void mutate() {
        // cout << "Mutate called" << endl;
        random_device rm;
        std::mt19937 genr(rm());
        std::normal_distribution<double> distribution(1, mut);

        this->expression = this->expression * distribution(genr);
    }

};


#endif