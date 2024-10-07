#include "People.h"
void Person::fillInterests() {
    random_device rd;
    std::mt19937 genr(rd());
    std::normal_distribution<double> fit((strength+speed+stamina)/3.0, 10);
    std::normal_distribution<double> str(strength, 10);
    std::normal_distribution<double> spe(speed, 10);
    std::normal_distribution<double> sta(stamina, 10);
    std::normal_distribution<double> cha(charisma, 10);
    std::normal_distribution<double> inte(intel, 10);
    std::normal_distribution<double> de(dexterity, 10);

    fit(rd) + str(rd) + spe(rd) + sta(rd) + cha(rd) + inte(rd) + de(rd);
    fit_interest = fit(rd);
    str_interest = str(rd);
    spe_interest = spe(rd);
    char_interest = cha(rd);
    intel_interest = inte(rd);
    dex_interest = de(rd);
    double interest_sum = fit_interest + str_interest +spe_interest + char_interest + intel_interest + dex_interest;

    fit_interest /= interest_sum;
    str_interest /= interest_sum;
    spe_interest /= interest_sum;
    char_interest /= interest_sum;
    intel_interest /= interest_sum;
    dex_interest /= interest_sum;

}
Person::Person(Person* father, Person* mother, string name, int year) {
    occ = "useless";
    // cout << "are we here" << endl;
    this->birth_year = year;
    this->ethnic = new Ethnicity(father->ethnic, mother->ethnic);
    this->dna = new Dna(father->dna, mother->dna);

    for (int i = 0; i < 4; i++) {
        Dna* dn = new Dna(father->reprod[i], mother->reprod[i], false);
        this->reprod.push_back(dn);
    }

    this->father = father;
    this->mother = mother;
    age = 0;
    this->first_name = name;
    this->name = father->name + " " + name;
    this->family_name = father->family_name;
    father->children.push_back(this);
    mother->children.push_back(this);

    int divisor = 18;

    height = dna->actual_stats[0]/divisor; // linear growth
    strength = dna->actual_stats[1]/divisor; // linear growth
    speed = dna->actual_stats[2]/divisor; // linear growth
    stamina = dna->actual_stats[3]/divisor; // linear growth
    weight = dna->actual_stats[5]/divisor; // linear growth
    charisma = dna->actual_stats[4]; // max at start (can develop)
    willpower = dna->actual_stats[6]; // max at start (can develop)
    intel = dna->actual_stats[7]/divisor; // linear growth
    melanin = dna->actual_stats[8]; // max at start // unchangable
    parental = dna->actual_stats[9]/divisor; // linear growth
    compassion = dna->actual_stats[10]; // max at shart
    dexterity = dna->actual_stats[11]/divisor;

    fillInterests();
    hunger = weight + height;
    // cout << "make it to the end" << endl;
}

Person::Person(Dna* dna, string name, int age, vector<Dna*> rep, string race, string occupation): dna(dna), name(name), age(age), reprod(rep){
    occ = occupation;
    ethnic = new Ethnicity();
    this->first_name = name;
    this->family_name = name;
    ethnic->ethnic_data[race] = 100;
    int divisor = 18;
    if (age >= 18) {
        divisor = 1;
    }

    height = dna->actual_stats[0]/divisor; // linear growth
    strength = dna->actual_stats[1]/divisor; // linear growth
    speed = dna->actual_stats[2]/divisor; // linear growth
    stamina = dna->actual_stats[3]/divisor; // linear growth
    weight = dna->actual_stats[5]/divisor; // linear growth
    // cout << name << " gained " << dna->actual_stats[5]/divisor << " pounds and now weighs a regular " << weight <<  endl;
    charisma = dna->actual_stats[4]; // max at start (can develop)
    willpower = dna->actual_stats[6]; // max at start (can develop)
    intel = dna->actual_stats[7]/divisor; // lienar growth
    melanin = dna->actual_stats[8]; // max at start // unchangable
    parental = dna->actual_stats[9]/divisor; // linear growth
    compassion = dna->actual_stats[10]; // max at shart
    dexterity = dna->actual_stats[11]/divisor;

    fillInterests();
    hunger = weight + height;
};
string Person::save_person() {
    stringstream line;
    string c = ",";

    line << "s_" + name << c;
    line << age << c;
    line << birth_year << c;
    line << first_name << c;
    line << "s_" + family_name << c;
    if (father == nullptr) {
        line << "" << c;
        line << "" << c;          
    } else {
        line << father->name << c;
        line << mother->name << c;
    }

    line << alive << c;
    line << death_cause << c;
    line << occ << c;
    line << height << c;
    line << strength << c;
    line << speed << c;
    line << stamina << c;
    line << weight << c;
    line << charisma << c;
    line << willpower << c;
    line << intel << c;
    line << melanin << c;
    line << parental << c;
    line << compassion << c;
    line << dexterity << c;
    line << weapon_prof << c;
    line << wealth << c;
    line << academic << c;
    line << farmer << c;
    line << fighter << c;
    line << hunter << c;
    line << merchant << c;
    line << ruler << c;
    line << years_service;
    return line.str();
}

 void Person::work(pair<bool, Person*>& ruler) {
        find_job();
        // cout << "here" << endl;
        if (ruler.second == nullptr){
            ruler.second = this;

        } else if (ruler.first == false) {
            if (ruler.second->ruler < this->ruler) {
                ruler.second = this;

            }
        }

        proficiency[occ]++;

    }

    void Person::find_job() {
        // input states which jobs are open in that population
        // gatherer stats


        academic = intel * 10 + willpower * 5;
        farmer = strength * 3 + stamina * 3 + willpower * 9;
        fighter = strength * 3 + speed * 2.25 + stamina * 1 + willpower * 2 + intel * 1.25 +  dexterity * 1 + (dexterity+weapon_prof) * 2 ;
        hunter = strength * 2.25 + speed * 2.25 + stamina * 2.25 + willpower * 2 + intel * 1.25 +  dexterity * 3 + (dexterity+weapon_prof) * 2 ;
        merchant = charisma * 7 + intel * 3 + 70 * 7 - (2 *compassion);
        ruler = strength * 2 + speed * 2 + stamina * 2 + charisma * 3 + willpower * 3 + height + (dexterity+weapon_prof) * 2;

        // if (!all_jobs["academic"].first || !all_jobs["academic"].second) { // checks if job is unlocked or if there are open roles in that job
        //     academic = 0;
        // }
        // if (!all_jobs["farmer"].first || !all_jobs["farmer"].second) {
        //     farmer = 0;
        // }
        // if (!all_jobs["hunter"].first || !all_jobs["hunter"].second) {
        //     hunter = 0;
        // }
        // if (!all_jobs["fighter"].first || !all_jobs["fighter"].second) {
        //     fighter = 0;
        // }
        // if (!all_jobs["merchant"].first || !all_jobs["merchant"].second) {
        //     merchant = 0;
        // }

        // if ((academic > farmer) && (academic > fighter) && (academic > hunter) && (academic > gatherer) && (academic > merchant)) {
        //     occ = "academic";
        //     return;
        // } else if ((fighter > farmer ) && (fighter > hunter) && (fighter > gatherer) && (fighter > merchant))

    };

    void Person::aging_process(Sec* sec, pair<bool, Person*>& ruler) {
        
        if (!alive) {
            return; //bro is dead, sorry
        }
        double mod = 1;
        random_device rd;
        std::mt19937 genr(rd());
        std::normal_distribution<double> distribution(5, 1);

        set_hunger();
        // cout << name << " has " << hunger << " hunger and " << food << " food" << endl; 
        double divisor = 18.0;
        if (age < 17) {
            height += (dna->actual_stats[0]/divisor);
            strength += (dna->actual_stats[1]/divisor);
            speed += dna->actual_stats[2]/divisor; // linear growth
            stamina += dna->actual_stats[3]/divisor; // linear growth
            weight += dna->actual_stats[5]/divisor; // linear growth
            intel += dna->actual_stats[7]/divisor;
            // cout << "weight gain " << dna->actual_stats[5]/divisor << " to total " << weight << endl;
            parental += dna->actual_stats[9]/divisor; // linear growth
            dexterity += dna->actual_stats[11]/divisor;
            yuhnow = 0;
        }
        if (age == 17) {
            this->find_job();
            if (occ == "useless") {
                occ = "gatherer";
            }
            
        }
        if (age > 19 && age < 40) {
            if (occ == "useless") {
                find_job();
            }
            yuhnow += distribution(genr)/2;
        }
        if (age < 27) {
            strength *= .989375 + willpower/8000;
            speed *= .989375 + willpower/8000;
            stamina *= .989375 + willpower/8000;
        }

        if (age > 27) {
            strength *= .988 + willpower/8000;
            speed *= .987 + willpower/8000;
            stamina *= .987 + willpower/8000;
            parental *= 1.002;
            charisma -= .2;
        }

        if (age > 38) {
            strength *= .988 + willpower/8000;
            speed *= .987 + willpower/8000;
            stamina *= .987 + willpower/8000;
            willpower *= .995;
        }

        if (age > 55) {
            if (occ == "fighter" || occ == "hunter") {
                wealth += 5000; //retirement fund for military
                occ = "retired";
            }
            strength *= .995;
            speed *= .995;
            stamina *= .995;
            dexterity *= .995;
            height -= .035;
            weight -= 1;
        }

        if (age > 70) {
            occ = "retired";
            intel *= .90 + willpower/1000;
        }

        this->risks();

        // chance of encounters and metrics upping necessary, this will be done in the environment tab

        // ten opportunities to obtain food // if enough food to satisfy hunger is achieved other opportunies are not required
        // one opportunity to get diseased
        // one opportunity to get accidental died
        // five opportunities shab
        age++;

        // cout << "running disease chance\n";

        disease_chance(sec);
        // activities of the year will happen here;

        int initiative = willpower/10 - 5;

        // cout << "running work\n";
        work(ruler);
        initiative--;

        // cout << "buying food\n";
        buy_food(true);

        if (hunger+child_hunger > food) {
            bool hunt_ = false;
            if (hunter > 975) {
                hunt_ = true;
            }

            while (initiative > 0 && hunger+child_hunger > food) {
                // cout << "hunt attempt\n";
                if (hunt_) {
                    hunt(sec);
                } else {
                    gather(sec);
                }
                initiative--;
            }
        }
        // vector<string> strategy = analyze();

        check_hunger();
    
    }

    void Person::risks() {
        if (height > 67) {
            this->disease = .001 + pow(weight - 150, 2)/750000 + pow(1.06, (height-67)*3) * .001;
            disease *= age/10;
        } else {
            this->disease = .001 + pow(weight - 150, 2)/750000 + pow(1.06, 0) * .001;
            disease *= age/10;
        }
        if (age < 60) {
            this->accidental = .001 + (150 - (intel + dexterity))/15000;
        } else {
            this->accidental = .001 + (150 - (intel + dexterity))/1500 + pow(1.01, age-60)/100;
        }
    }
    void Person::print_base() {
        cout << "Age: " << age << endl;
        dna->print_base();
    }

    void Person::print_compact() {
        cout << "name: " << name << " occupation: " << occ << endl;
        cout << "birth year: " << birth_year << " AD " << endl;
        alive ? cout << "alive" : cout << "dead";
        cout << endl;
        cout << "gender: ";
        dna->gender ? cout << "male" : cout << "female";
        cout << endl;
        cout << "age: " << age << endl;
        if (mother == nullptr || father == nullptr) {
            cout << "height: " << height << endl;
        } else {
            cout << "height: " << height << " - mother height: " << mother->height << " - father height: " << father->height << endl;
        }
        
        cout << "weight: " << weight << endl;
        cout << "base weight: " << dna->actual_stats[5] << endl << endl;
        ethnic->print_ethnicity();
    }

    void Person::print_actual() {
        cout << "stats:" << endl;
        cout << "gender: ";
        dna->gender ? cout << "male" : cout << "female";
        cout << endl;

        cout << "age: " << age << endl;
        cout << "height: " << height << endl;
        cout << "strength: " << strength << endl;
        cout << "speed: " << speed << endl;
        cout << "stamina: " << stamina << endl;
        cout << "weight: " << weight << endl;
        cout << "charisma: " << charisma << endl;
        cout << "willpower: " << willpower << endl;
        cout << "intel: " << intel << endl;
        cout << "melanin: " << melanin << endl;
        cout << "parental: " << parental << endl;
        cout << "compassion: " << compassion << endl;
        cout << "dexterity: " << dexterity << endl;
        ethnic->print_ethnicity();
        cout << "wealth:" << wealth << endl;
        cout << "occupation: " << occ << endl;
        cout << endl;

    }

    void Person::disease_chance(Sec* sec) {
        random_device rm;
        std::mt19937 genr(rm());
        std::uniform_real_distribution<double> distribution(0, 1);

        double probs_s = disease + (melanin - sec->sunlight)/100.0;
        double probs_d = disease + (sec->sunlight - melanin)/100.0;

        if (probs_s > distribution(genr)) {
            this->alive = false;
            this->death_cause = "skin cancer";
            return;
        } else if (probs_d > distribution(genr)) {
            this->alive = false;
            this->death_cause = "vitamin deficiency";
            return;
        }
    };

    void Person::set_hunger() {
        hunger += (weight + height); // hunger is added here
        child_hunger = 0;
        for (auto child : children) {
            if (child->age < 18) {
                if (this->dna->gender && !child->mother->alive) {
                    child_hunger += (child->hunger * (parental/100) * 1.25);
                } else if (!this->dna->gender && !child->father->alive) {
                    child_hunger += (child->hunger * (parental/100) * 1.25);
                } else {
                    child_hunger += (child->hunger * (parental/100) * .75);
                }
            }
        }
    }

    void Person::check_hunger() {

        for (auto child: children) {
            int mult = 1.25;
            if (child->father->alive && child->mother->alive) {
                mult = .75;
            }
            double c_hung = child->hunger + child->weight + child->height;
            if (food - ((c_hung + c_hung/(age+1)) * (parental/100) * .75) > 0) {
                child->food += ((c_hung + c_hung/(age+1)) * (parental/100) * .75);
                food -= ((c_hung + c_hung/(age+1)) * (parental/100) * .75);
                // cout << name << " gave " << ((c_hung + c_hung/(age+1)) * (parental/100) * .75) << " food to " << child->name << " who has " << child->hunger << " hunger and " << child->food << " food" << endl;
            }
        }

        historical_food_data = food;
        hunger -= food;
        food = 0;


        if (hunger < 0) {
            if (hunger < -1000 && age > 17) {
                yuhnow+=5;
            } else if (age > 17) {
                yuhnow += hunger/-200;
            }
            double max_weight = dna->actual_stats[5] + 5;
            if (age < 17) {
                max_weight = (age+1) * dna->actual_stats[5]/18 + 5;
            }
            if (max_weight > weight) {
                if (weight - hunger > max_weight) {
                    weight = max_weight;
                    // cout << name << " now weighs " << weight <<  endl;
                } else {
                    weight -= hunger;
                }
            }
        hunger = 0;
        }

        if (hunger > 0) {
            // cout << name << " is hungry and wants " << hunger << " food" << endl;
            double weight_loss = hunger;
            weight -= hunger/10;
            strength -= weight_loss/75;
            hunger /= 2;
        }

        if (hunger > 300) {
            alive = false;
            // cout << name << " died of hunger at age " << age << endl;
            this->death_cause = "starvation";
        }

        if ((weight/2.205)/pow((height * .0254), 2) < 12) {
            alive = false;
            // cout << name << " died of underweightness " << age << endl;
            this->death_cause = "lack of mass";
        }       
    }

    // TODO
    vector<string> Person::analyze() {
        // At some point I want a machine learning algorithm here, but for right now a decision tree is good
        
        // compute priorities

        // number of actions that can be performed is willpower/10 rounded down

        // get food, spend time w family, train etc.., recompute priorities after each action

        double gather, hunt, eat, cook, buy_food, explore, spendTime, ponder, hypothesize, work = 0.0;
        vector<string> ans = {"Eat"};
        return ans;
        // action heirarchy priority one is work/occupation
        // this will provide with money, hunter can be a profession
        // after work, a character will either buy food to satisfy their hunger, gather or hunt
        // if food object cooked != true, and character has unlocked cook, then cook the food
        

    }

    void Person::fight(Food* animal) {

    }

    double Person::gather(Sec* sec) {
        food += sec->gatherFood->quantity;
        return food;
    }


    double Person::hunt(Sec* sec) {

        int attempt = 0;
        random_device rd;
        std::mt19937 genr(rd());
        std::normal_distribution<double> find(.5, .2);
        std::uniform_real_distribution<double> success(0, 1);

        while (this->food < hunger + child_hunger && attempt < 10) {
            // cout << "hunting\n";
            double search = find(genr) + proficiency["hunting"];
            if (search > 1 - sec->preyFood->abundance) {
                double thresh = success(genr);
                double suitability = differential(sec->preyFood->diff, sec->preyFood->diff_imp);
                // cout << "predef suit " << suitability << endl;

                suitability = 1/(1 + pow(exp(1), -suitability/10)); //use sigmoid to create probability
                // cout << "thresh " << thresh << " suit " << suitability << endl;
                if (suitability > thresh) {
                    // cout << "gained food, now " << name << " has " << food << endl; 
                    this->food += sec->preyFood->quantity;
                    proficiency["hunting"] += .005;
                } else if (suitability + .3 < thresh){
                    alive = false;
                    this->death_cause = sec->preyFood->name + " while hunting";
                }

            } else if (search < sec->predatorFood->abundance) {
                double thresh = success(genr);
                double suitability = differential(sec->preyFood->diff, sec->preyFood->diff_imp);

                suitability = 1/(1 + pow(exp(1), -suitability/10)); //use sigmoid to create probability

                if (suitability > thresh) {
                    this->food += sec->predatorFood->quantity;
                    proficiency["hunting"] += .005;
                } else if (suitability + .3 < thresh){
                    alive = false;
                    this->death_cause = sec->predatorFood->name + " while hunting";
                }
            }
            attempt++;
        }
        return food;
    }