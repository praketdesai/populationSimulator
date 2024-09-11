#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include "Dna.h"
#include "Archetype.h"
#include "Encounter.h"
// #include "Tool.h"
using namespace std;


class Occupation {
    // gatherer, hunter, fighter, academic, ruler , useless
    string occ = "useless";
    Occupation(string occupation) {
        occ = occupation;
    }

    

};

struct Data {
    public:
    vector<vector<double>> data = {{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}};
    int year = 0;
};

class Tool {
        public:
        string tool_class = "farming";
        double attack = 21;
        double defense = 30;
        double efficiency_increase = 1;
        double speed_decrease = 0;
        double range = 0;

        Tool() {}
    };

class Tools {
    public:


    double knowledge = 0.0;
    map<string, Tool*> too;
    Tools() {

    }

    void unlock_sword() {
        Tool* sword = new Tool();
        sword->tool_class = "weapon";
        sword->attack = 79; // base metrics, experience with weapons and dexterity level impacts this in battle
        sword->defense = 66;

        too.insert(std::pair("sword", sword));
    }

    void unlock_hoe() {
        Tool* hoe = new Tool();
        hoe->tool_class = "farming";
        hoe->efficiency_increase = 1.3;

        too.insert(std::pair("hoe", hoe));
    }
    
    void add_knowledge(double info) {
        knowledge += info;
    }

};

class Ethnicity {
    public:
    map <string, double> ethnic_data;
    Ethnicity() {}
    Ethnicity(Ethnicity* father, Ethnicity* mother) {
        for (auto& item : father->ethnic_data) {
            ethnic_data[item.first] += item.second/2.0;
        }
        for (auto& item : mother->ethnic_data) {
            ethnic_data[item.first] += item.second/2.0;
        }
    }

    void print_ethnicity() {
        for (const auto& item : ethnic_data) {
            cout << item.first << ": " << item.second << "%" << "  -  ";
        }
        cout << endl;
    }
};

class Person {
    public:
    int birth_year = 0;
    int age = 0;
    Person* father = nullptr;
    Person* mother = nullptr;
    vector<Person*> children;
    Dna* dna;
    vector<Dna*> reprod;



    bool alive = true;
    string death_cause = "alive";
    // actual metrics
    // environmental factors

    string name = "0";
    string first_name = "0";
    string family_name = "0";
    double food_intake = 1;
    double nutrition = 1;
    double upbringing_status = 1;
    double care = 1;
    double historical_food_data = 0;

    double social_status = 0.0;
    vector<Person*> friends = {};

    string occ = "useless";
    double salary = 0;
    map<string, double> proficiency; // proficiency in tools (where relevant)
    vector<Tool*> tools = {};


    // risks
    double disease;
    double accidental;


    // genetics based

    // etnicity data


    Ethnicity* ethnic = nullptr;


    double height = 0;
    double strength;
    double speed;
    double stamina;
    double weight;
    double charisma;
    double willpower;
    double intel;
    double melanin;
    double parental;
    double compassion;
    double dexterity;
    double weapon_prof;
    vector<double*> real = {&height, &strength, &speed, &stamina, &charisma, &weight, &willpower, &intel, &melanin, &parental, &compassion, &dexterity};

    // variable metrics
    double wealth = 0.0; // can be used to buy food from farmers && hunters
    double food = 0.0;
    double hunger = 0.0;
    double child_hunger = 0.0;
    double yuhnow = 0;

    // job suitibility

    double academic;
    double farmer;
    double fighter;
    double hunter;
    double merchant;
    double gatherer;
    double ruler;

    double years_service = 0; //military 



    Person(Person* father, Person* mother, string name, int year = 0) {
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
        intel = dna->actual_stats[7]; // max at start (can develop)
        melanin = dna->actual_stats[8]; // max at start // unchangable
        parental = dna->actual_stats[9]/divisor; // linear growth
        compassion = dna->actual_stats[10]; // max at shart
        dexterity = dna->actual_stats[11]/divisor;

        hunger = weight + height;
        // cout << "make it to the end" << endl;
    }



    Person(Dna* dna, string name, int age, vector<Dna*> rep, string race = "basic", string occupation = "gatherer"): dna(dna), name(name), age(age), reprod(rep){
        occ = occupation;
        ethnic = new Ethnicity();
        this->first_name = name;
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
        intel = dna->actual_stats[7]; // max at start (can develop)
        melanin = dna->actual_stats[8]; // max at start // unchangable
        parental = dna->actual_stats[9]/divisor; // linear growth
        compassion = dna->actual_stats[10]; // max at shart
        dexterity = dna->actual_stats[11]/divisor;

        hunger = weight + height;
    };

    ~Person() {
        delete ethnic;
    }
    void risks() {
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

    void work(map<string, Encounter*>& encount, pair<bool, Person*>& ruler) {
        find_job();
        // cout << "here" << endl;
        if (ruler.second == nullptr){
            ruler.second = this;

        } else if (ruler.first == false) {
            if (ruler.second->ruler < this->ruler) {
                ruler.second = this;

            }
        }

        if (occ == "useless" || occ == "retired") {
            if (occ == "retired") {
                wealth += 300;
            }
            return;
        } else if (occ == "hunter") {
            for (int i = 0; i < 4; i++) {
                this->encounter(encount["food_hunt"]);
            }
            strength += .2;
            speed += .2;
            stamina += .2;
            wealth += food - child_hunger - hunger;  
        } else if (occ == "farmer") {
            for (int i = 0; i < 4; i++) {
                this->encounter(encount["food_growth"]);
            }
            wealth += food - child_hunger - hunger;          
        } else if (occ == "fighter") {
            years_service++;
            strength += .2;
            speed += .2;
            stamina += .2;
            wealth += salary;
        } else if (occ == "academic") {
            intel += .1;
            // this->encounter(encount["engineering"]);
            wealth += salary;

        } else if (occ == "gatherer") {
            for (int i = 0; i < 4; i++) {
                this->encounter(encount["food_gather"]);
            }    
        }
        proficiency[occ]++;

    }

    void occupation_impact() { // this is probably useless

    };

    void find_job() {
        // input states which jobs are open in that population
        // gatherer stats


        academic = intel * 10 + willpower * 5;
        farmer = strength * 3 + stamina * 3 + willpower * 9;
        fighter = strength * 3 + speed * 2.25 + stamina * 1 + willpower * 2 + intel * 1.25 +  dexterity * 1 + (dexterity+weapon_prof) * 2 ;
        hunter = strength * 2.25 + speed * 2.25 + stamina * 2.25 + willpower * 2 + intel * 1.25 +  dexterity * 3 + (dexterity+weapon_prof) * 2 ;
        merchant = charisma * 7 + intel * 3 + 70 * 7 - (2 *compassion);
        gatherer = 975;
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

    void aging_process(int supported_pop, double current_pop) {
        // cout << name << " has " << hunger << " hunger and " << food << " food" << endl; 
        double mod = 1;
        if (supported_pop != 0 && current_pop > supported_pop) {
            mod = pow(current_pop/supported_pop, .5);
        }
        random_device rd;
        std::mt19937 genr(rd());
        std::normal_distribution<double> distribution(5, 1);
        if (!alive) {
            return; //bro is dead, sorry
        }
        hunger += (weight + height) * mod; // hunger is added here
        double divisor = 18.0;
        if (age < 17) {
            height += (dna->actual_stats[0]/divisor);
            strength += (dna->actual_stats[1]/divisor);
            speed += dna->actual_stats[2]/divisor; // linear growth
            stamina += dna->actual_stats[3]/divisor; // linear growth
            weight += dna->actual_stats[5]/divisor; // linear growth
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

        // activities of the year will happen here;
        

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

        food += wealth;

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

        
        if (food > (hunger + 1000)) {
            wealth = food - hunger - 1000;
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
        // cout << endl;
        // cout << name << " is ";
        // alive ? cout << "alive" << endl : cout << "dead" << endl;
        // cout << "age: " << age << endl;
        // cout << "hunger: " << hunger << endl;
        // cout << "food: " << food << endl;
        // cout << "weight: " << weight << endl;
        // cout << "strength: " << strength << endl;
        // cout << "speed: " << speed << endl;
        // cout << endl;
        // cout << endl;
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
        

        occupation_impact();

        

        
    }

    void new_item() {

    }

    bool encounter(Encounter* sit) {
        if (!alive) {
            return false;
        }
        random_device rm;
        std::mt19937 genr(rm());
        std::uniform_real_distribution<double> distribution(0, 1);

        if (sit->type == "disease") {
            double probs = sit->chance + this->disease;
            // cout << probs << " for disease" << endl;
            if (probs > distribution(genr)) {
                this->alive = false;
                // cout << this->name << " died of disease at age " << age  << endl;
                this->death_cause = sit->type;
                return true;
            }
        } else if (sit->type == "accident") {
            double probs = sit->chance + this->accidental;
            // cout << probs << " for accident" << endl;
            if (probs > distribution(genr)) {
                this->alive = false;
                // cout << this->name << " died of an accident at age " << age  << endl;
                this->death_cause = sit->type;
                return true;
            }
        } else if (sit->type == "food") {
            double probs = sit->chance;
            if (probs > distribution(genr)) {
                double strdiff = (strength - sit->strength_diff);
                double speediff = (speed - sit->speed_diff);
                double stamidiff = (stamina - sit->stamina_diff);
                double inteldiff = (intel - sit->stamina_diff);
                double dexdiff = (dexterity - sit->dexterity_diff);

                vector<double> diffs = {strdiff, speediff, stamidiff, inteldiff, dexdiff};
                double power = 0;
                for (auto elem : diffs) {
                    if (elem > 0) {
                        power += elem;
                    } else {
                        power -= ((elem * elem)/2);
                    }
                }

                double rand = distribution(genr);
                rand *= 100;
                rand -=100;
                // cout << "RAND: "<< rand << " POWER: " << power << " at age " << age << endl;;
                if (rand > power) {
                    double death = distribution(genr);
                    if (death < sit->death_chance) {
                        // cout << this->name << " died while looking for food at the age of " << age  << endl;
                        this->death_cause = "looking for food";
                        alive = false;
                    }
                } else {
                    double take_home = (power - rand + 20)/100;
                    if (take_home > 1) {
                        take_home = 1;
                    }
                    take_home *= sit->food;
                    food += take_home;
                    // cout << name << " took home " << take_home << " food" << endl;
                    this->nutrition += take_home * sit->nutrition_mult;
                }
            }
        } else if (sit->type == "engineering") {
            random_device rm;
            std::mt19937 genr(rm());
            std::uniform_real_distribution<double> distribution(0, 1);

            double luck = distribution(genr);

            double probs = (intel * 10 + willpower * 5)/1000;
            probs = pow(probs, 2);

            probs *= .01;

            if (luck < probs) {
                cout << "discovery: " << endl;
                new_item();
            }
            
        }
        return false;
        
    }

    void print_base() {
        cout << "Age: " << age << endl;
        dna->print_base();
    }

    void print_compact() {
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

    void print_actual() {
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
};
class Peoples {
    public:
    
    map<string, Encounter*> encount; // map from the encounter pointer to the base chance of that encounter occuring

    vector<Person*> military; // capped role
    vector<Person*> academics; // capped role
    pair<bool, Person*> ruler = pair(false, nullptr);
    Tools* tools;
    Data* origin = nullptr;
    vector<Data*> data;
    int save_number = 0;



    int fighter_c = 0;
    int academic_c = 0;

    double fighter_max_ratio = .1;
    double academic_ratio = .0;

    double fighter_salary = 1000;
    double academic_salary = 500;

    bool fighter = false;
    bool academic = false;

    struct Comparator {
        int metric = 0;
        bool operator()(Person* one, Person* two) const {
            return (*(one->real[metric]) > *(two->real[metric]));
        }
    };

    struct WealthComp {
        bool operator()(Person* one, Person* two) const {
            return (one->wealth) > (two->wealth);
        }
    };

    struct Fighter {
        bool operator()(Person* one, Person* two) const {
            return (one->fighter) > (two->fighter);
        }
    };

    struct Academic {
        bool operator()(Person* one, Person* two) const {
            return (one->academic) > (two->academic);
        }
    };

    vector<Person*> people;
    Archetypes storage;

    Peoples() {
        storage = Archetypes();

    };

    ~Peoples() {
        for (auto elem : people) {
            delete elem;
        }
        for (auto elem : data) {
            delete elem;
        }
    }

    vector<Person*> clear_junk(vector<Person*> arr, string keep = "fighter") {
        vector<Person*> newarr;

        for (auto elem : arr) {
            if (elem->occ == keep && elem->alive) {
                newarr.push_back(elem);
            }
        }

        return newarr;
    }

    void select_soldiers_and_academics(bool preference = true) {
        string opp;
        string self;
        int count;
        // cout << military.size() << " ";
        // cout << academics.size() << '\n';
        int cut_fighters = fighter_c/10;
        int cut_academics = academic_c/10;

        // cut the bottom 10% of both fields
        military = clear_junk(military, "fighter");
        academics = clear_junk(academics, "academic");

        for (int i = cut_fighters; i < military.size(); i++) {
            military[i]->occ = "retired";
        }

        for (int i = cut_academics; i < academics.size(); i++) {
            academics[i]->occ = "useless";
        }

        military = clear_junk(military, "fighter");
        academics = clear_junk(academics, "academic");



        if (preference) {
            sort(people.begin(), people.end(), Fighter());
            count = fighter_c;
            opp = "academic";
            self = "fighter";
            // cout << "here 56" << endl;
            for (auto elem : people) {
                // cout << "here 1" << endl;
                if (elem->occ != opp && elem->occ != self) {
                    // cout << "here 2" << endl;
                    military.push_back(elem);
                    elem->occ = "fighter";
                    elem->salary = fighter_salary;
                    if (military.size() >= count) break;
                }
            }
            count = academic_c;
            sort(people.begin(), people.end(), Academic());
            for (auto elem : people) {
                if (elem->occ != opp && elem->occ != self) {
                    academics.push_back(elem);
                    elem->occ = "academic";
                    elem->salary = academic_salary;
                    if (academics.size() >= count) break;
                }
            }


        } else {
            sort(people.begin(), people.end(), Academic());
            count = academic_c;
            opp = "fighter";
            self = "academic";
            for (auto elem : people) {
                if (elem->occ != opp && elem->occ != self) {
                    academics.push_back(elem);
                    elem->occ = "academic";
                    elem->salary = academic_salary;
                    if (academics.size() >= count) break;
                }
            }
            sort(people.begin(), people.end(), Fighter());
            count = fighter_c;
            for (auto elem : people) {
                if (elem->occ != opp && elem->occ != self) {
                    military.push_back(elem);
                    elem->occ = "fighter";
                    elem->salary = fighter_salary;
                    if (military.size() >= count) break;
                }
            }
            // print_military();
        }



        
    }

    void print_military() {
        sort(military.begin(), military.end(), Fighter());
        for (auto per : military) {
            cout << per->first_name << ": " << per->fighter << " " << per->occ << " " << per->academic << endl;
        }
    }

    void createPerson(string type, int age, string race = "basic") {
        
        vector<double> gender_diff = storage.mapo.at(type)->gen_diff;
        vector<double> initial_value = storage.mapo.at(type)->inital_values;
        vector<double> me_vals = storage.mapo.at(type)->desire_m;
        vector<double> mc_vals = storage.mapo.at(type)->desire_mc;
        vector<double> fe_vals = storage.mapo.at(type)->desire_f;
        vector<double> fc_vals = storage.mapo.at(type)->desire_fc;

        random_device rd;
        std::mt19937 genr(rd());
        std::normal_distribution<double> distribution(0, .05);

        random_device rd2;
        std::mt19937 genr2(rd2());
        std::uniform_int_distribution<int> heads_tails(0, 1);

        vector<Allele*> allele_list;
        


        for (int i = 0; i < 24; i++) {
            Allele* al = new Allele(initial_value[i/2] + distribution(genr), gender_diff[i/2], heads_tails(genr2));
            allele_list.push_back(al);
        }
        for (int i = 0; i < 24; i++) {
            Allele* al = new Allele(me_vals[i/2] + distribution(genr), 1, heads_tails(genr2));
            allele_list.push_back(al);
        }
        for (int i = 0; i < 24; i++) {
            Allele* al = new Allele(mc_vals[i/2] + distribution(genr), 1, heads_tails(genr2));
            allele_list.push_back(al);
        }
        for (int i = 0; i < 24; i++) {
            Allele* al = new Allele(fe_vals[i/2] + distribution(genr), 1, heads_tails(genr2));
            allele_list.push_back(al);
        }
        for (int i = 0; i < 24; i++) {
            Allele* al = new Allele(fc_vals[i/2] + distribution(genr), 1, heads_tails(genr2));
            allele_list.push_back(al);
        }

        vector<Gene*> gene_list;
        vector<Gene*> me;
        vector<Gene*> mc;
        vector<Gene*> fe;
        vector<Gene*> fc;


        for (int i = 0; i < 120; i = i+2) {
            Gene* ge = new Gene(allele_list[i], allele_list[i+1]);
            if (i < 24) {
                gene_list.push_back(ge);
            } else if (i < 48) {
                me.push_back(ge);
            } else if (i < 72) {
                mc.push_back(ge);
            } else if (i < 96) {
                fe.push_back(ge);
            } else {
                fc.push_back(ge);
            }
            
        }
        bool gender_ = heads_tails(genr2);
        Dna* pers = new Dna(gene_list, gender_);
        Dna* me_ = new Dna(me, gender_, false);
        Dna* mc_ = new Dna(mc, gender_, false);
        Dna* fe_ = new Dna(fe, gender_, false);
        Dna* fc_ = new Dna(fc, gender_, false);

        vector<Dna*> dnas = {me_, mc_, fe_, fc_};

        Person* persona = new Person(pers, to_string(people.size()), age, dnas, race);

        people.push_back(persona);
    }

    int print_death_causes() {
        int deaths = 0;
        cout << endl;
        map<string, int> count;
        map<string, double> total;
        map<string, double> weight;
        map<string, double> height;

        for (auto elem : people) {
            if (elem->death_cause != "alive") {
                deaths++;
            }
            if (count.find(elem->death_cause) == count.end()) {
                count[elem->death_cause] = 1;
                total[elem->death_cause] = elem->age;
                weight[elem->death_cause] = elem->weight;
                height[elem->death_cause] = elem->height;
            } else {
                count[elem->death_cause] = count[elem->death_cause] + 1;
                total[elem->death_cause] += elem->age;
                weight[elem->death_cause] += elem->weight;
                height[elem->death_cause] += elem->height;
            }
        }

        for (auto elem = count.begin(); elem != count.end(); ++elem) {
            cout << elem->second << " deaths by " << elem->first <<  ", the average age of death was " << total[elem->first]/elem->second;
            cout << " the average weight was " << weight[elem->first]/elem->second << " and the average height was " << height[elem->first]/elem->second << endl;
        }
        return deaths;
    }

    double wants(Person* one, Person* two) {
        double value = 0.0;
        if (one->hunger + one->child_hunger > 0) {
            double hungerfact = (two->historical_food_data - two->hunger - two->child_hunger)/1000;
            if (hungerfact > .20) {
                hungerfact = .20;
            }
            value += hungerfact;
        }

        int effect = 0;
        int power = 1;

        if (!one->dna->gender) {
            effect = 2;
            power = 3;
        }

        double one_h = *(one->real[0]);
        double two_h = *(two->real[0]);

        // cout << "one height " <<  one_h << " two height " << two_h << " factor " << one->reprod[effect]->actual_stats[0] - 10 << endl;

        
        double height_imp = abs(*(two->real[0]) - (*(one->real[0]) + one->reprod[effect]->actual_stats[0] - 10));
        // cout << height_imp << endl;


        height_imp /= 100;

        height_imp = one->reprod[power]->actual_stats[0] - height_imp;
        // cout << height_imp << endl;

        // cout << "height: " << one->height << " " << two->height << " " << height_imp << endl;

        if (height_imp < -one->reprod[power]->actual_stats[0]) {
            height_imp = -one->reprod[power]->actual_stats[0];
        }

        value += height_imp;

        for (int i = 1; i < 12; i++) {
            
            double valuee = *(two->real[i]) - (*(one->real[i]) + one->reprod[effect]->actual_stats[i] - 20);
            double add = valuee/20000;

            // cout << *(one->real[i]) << " " << *(two->real[i]) << " " << add << endl;

            if (add > one->reprod[power]->actual_stats[i]) {
                add = one->reprod[power]->actual_stats[i];
            } else if (add < -one->reprod[power]->actual_stats[i]) {
                add = -one->reprod[power]->actual_stats[i];
            }
            value += add;
        }
        // cout << value << endl;
        return value * 100;
    }

    bool match(Person* m, Person* f) { // no superficial impact, solely chramisa // adding societal impact
        random_device rd;
        std::mt19937 genr(rd());
        std::normal_distribution<double> distribution(50, 15);
        double chemistry = distribution(genr);
        // let us even this up, a person wants what they don't have maybe, could also want some one like them.
        double want_m = wants(m, f);
        double want_f = wants(f, m);
        double mim = f->charisma + want_m;
        double fim = m->charisma + want_f;

        // cout << "wants-m: " << want_m << "- f char: " << f->charisma << endl;
        // cout << "wants-f: " << want_f << "- m char: " << m->charisma << endl;
        if (mim + chemistry > 120 && fim + chemistry > 120) {
            return true;
        }
        return false;
    }

    int reproduction(int year) {
        int children = 0;
        vector<Person*> males;
        vector<Person*> females;
        for (auto person : people) {
            if (person->alive && person->dna->gender && person->yuhnow > 20) {
                males.push_back(person);
            } else if (person->alive && !person->dna->gender && person->yuhnow > 20) {
                females.push_back(person);
            }
        }

        int num_m = males.size();
        int num_f = females.size();

        if (!num_m || !num_f) {
            return 0;
        }

        int attempts = (num_f + num_m) * 2;

        if (attempts < 2) {
            return 0;
        }
        random_device rd;
        std::mt19937 gm(rd());
        std::uniform_int_distribution<int> male(0, num_m-1);

        random_device rd2;
        std::mt19937 gf(rd2());
        std::uniform_int_distribution<int> female(0, num_f-1);

        for (int i = 0; i < attempts; i++) {
            int man = male(gm);
            int woman = female(gf);
            if (match(males[man], females[woman])) {
                if ((males[man]->yuhnow > 20) && (females[woman]->yuhnow > 20)) {
                    Person* child = new Person(males[man], females[woman], to_string(people.size()), year);
                    people.push_back(child);
                    // cout << males[man]->height<< " " << females[woman]->height << " " << "they fucked" << endl;
                    children++;
                    males[man]->yuhnow -= 20;
                    females[woman]->yuhnow -= 20;
                    // cout << males[man]->name << " and " << females[woman]->name << " new child is created " << child->name << endl;
                }
            }
        }
        return children;

    }

    int alive_pop () {
        int peeps = 0;
        for (auto elem : people) {
            if (elem->alive) {
                peeps++;
            }
        }
        return peeps;
    }

    void demographics(vector<Person*>& people, bool milit = false, bool verbose = true) {
        if (milit) {
            cout << "military stats:" << endl;
        }
        int population = 0;
        int childs = 0;
        double percent_males = 0;

        vector<double> average_age = {0,0,0};
        vector<double> average_height = {0,0,0};
        vector<double> average_strength = {0,0,0};
        vector<double> average_speed = {0,0,0};
        vector<double> average_stamina = {0,0,0};
        vector<double> average_weight = {0,0,0};
        vector<double> average_charm = {0,0,0};
        vector<double> average_willp = {0,0,0};
        vector<double> average_intel = {0,0,0};
        vector<double> average_melanin = {0,0,0};
        vector<double> average_parental = {0,0,0};
        vector<double> average_compassion = {0,0,0};
        vector<double> average_dex = {0,0,0};
        
        

        if (ruler.second != nullptr) {
            cout << "ruler: " << ruler.second->name << endl;
        } else {
            cout << "ruler: none" << endl;
        }

        for (auto elem : people) {
            if (elem->alive && elem->age>18 && elem->dna->gender) {
                population++;
                percent_males++;
                for (int i = 0; i < 2; i++) {
                    average_age[i] += elem->age;
                    average_height[i] += elem->height;
                    average_strength[i] += elem->strength;
                    average_speed[i] += elem->speed;
                    average_stamina[i] += elem->stamina;
                    average_weight[i] += elem->weight;
                    average_charm[i] += elem->charisma;
                    average_willp[i] += elem->willpower;
                    average_intel[i] += elem->intel;
                    average_melanin[i] += elem->melanin;
                    average_parental[i] += elem->parental;
                    average_compassion[i] += elem->compassion;
                    average_dex[i] += elem->dexterity;
                }

            } else if (elem->alive && elem->age>18){
                population++;
                for (int i = 0; i < 3; i = i+2) {
                    average_age[i] += elem->age;
                    average_height[i] += elem->height;
                    average_strength[i] += elem->strength;
                    average_speed[i] += elem->speed;
                    average_stamina[i] += elem->stamina;
                    average_weight[i] += elem->weight;
                    average_charm[i] += elem->charisma;
                    average_willp[i] += elem->willpower;
                    average_intel[i] += elem->intel;
                    average_melanin[i] += elem->melanin;
                    average_parental[i] += elem->parental;
                    average_compassion[i] += elem->compassion;
                    average_dex[i] += elem->dexterity;
                }
            } else if (elem->alive) {
                childs++;
            }
        }

        vector<vector<double>> storage = {average_height, average_strength, average_speed, average_stamina, average_weight, average_charm, average_willp, average_intel, average_melanin, average_parental, average_compassion, average_dex, average_age};
        for (int i = 0; i < 13; i++) {
            storage[i][0] /= population;
            storage[i][1] /= percent_males;
            storage[i][2] /= (population - percent_males);
        }

        Data* elem = new Data;

        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 3; j++) {
                elem->data[i][j] = storage[i][j];
                storage[i][j] = round(storage[i][j] * 100)/100;
                if (i == 4) {
                    storage[i][j] = round(storage[i][j] * 10)/10;
                }
            }
        }
    
        data.push_back(elem);

        if (!save_number) {
            origin = data[0];
        }
        vector<string> names = {"hgt", "str", "spe", "sta", "wgt", "cha", "wil", "int", "mel", "par", "com", "dex", "age"};



        cout << endl;
        cout << "child population: " << childs << endl;
        cout << "adult population: " << population << " - male population: " << percent_males << " - female population: " << population - percent_males << endl; 
        cout << "stats for men and women over the age of 18" << endl;

        for (int i = 0; i < 13; i++) {

            cout << "total " << names[i] << ": " << storage[i][0] << " - male " << names[i] << ": " << storage[i][1] << " - female " << names[i] << ": " << storage[i][2];   
            if (save_number > 0) {
                cout << " start-change: " << round((data[save_number]->data[i][0] - data[0]->data[i][0])/data[save_number]->data[i][0] * 10000)/100.0<< "%";
                cout << " last-change: " << round((data[save_number]->data[i][0] - data[save_number-1]->data[i][0])/data[save_number]->data[i][0] * 10000)/100.0 << "%";
            }
            cout << endl;
        }

        cout << "percent male: " << percent_males/population * 100 << "%" << endl;
        print_overall_ethnicities(people); // includes children
        print_occupation_percentages(people);
        cout << endl;
        save_number++;


    }

    void highest_in_the_room(int wanted = 5, bool aliv = true, int metric = 0, int detail = 0) {
        map <int, string> val;
        val[0] = "height";
        val[1] = "strength";
        val[2] = "speed";
        val[3] = "stamina";
        val[4] = "charisma";
        val[5] = "weight";
        val[6] = "will power";
        val[7] = "intel";
        val[8] = "melanin";
        val[9] = "parental";
        val[10] = "compassion";
        val[11] = "dexterity";
        Comparator comp = Comparator();
        comp.metric = metric;
        sort(people.begin(), people.end(), comp);

        for (auto person : people) {
            if (aliv && !person->alive) continue;
            if (wanted == 0) break;
            if (detail) {
                cout << person->name <<  " : " << *person->real[metric] << " " << val[metric] << endl;
            } else {
                person->print_compact();
            }
            
            wanted--;
        }

    }
    Person* find_person(string name) {

        for (auto& person : people) {
            if (person->first_name == name) {
                return person;
                break;
            }
        }

        return nullptr;
    }
    void family_tree(string name) {
        Person* dude = find_person(name);

        cout << "children: " << dude->children.size() << endl;
        for (auto kid : dude->children) {
            kid->print_compact();
        }
    }

    void print_parents(string name) {
        
        Person* dude = find_person(name);
        cout << "mother: " << dude->children.size() << endl;
        dude->mother->print_compact();
        cout << "father: " << dude->children.size() << endl;
        dude->father->print_compact();
    
    }

    void print_person(string name) {
        Person* dude = find_person(name);

        cout << "person:" << endl;
        dude->print_compact();
    }

    void print_overall_ethnicities(vector<Person*>& people) {
        int population = 0;
        Ethnicity* eth = new Ethnicity();
        for (auto& person : people) {
            if (!person->alive) continue;
            population++;
            for (auto& x : person->ethnic->ethnic_data) {
                eth->ethnic_data[x.first] += x.second;
            }
        }

        for(auto &value : eth->ethnic_data) {
            value.second /= population;
        }

        eth->print_ethnicity();
        delete eth;
    }

    void print_occupation_percentages(vector<Person*>& people) {
        int adults = 0;
        map<string, double> vals;

        for (auto& person : people) {
            if (!person->alive || person->age < 18) continue;
            adults++;
            vals[person->occ] += 1;
        }

        for(auto &value : vals) {
            value.second /= adults; 
            value.second *= 100;
        }

        for (const auto& item : vals) {
            cout << item.first << ": " << item.second << "%" << "  -  ";
        }

    }

    void simulate(int n, int& year, map<string, Encounter*> encounte, int supported_pop) {



        encount = encounte;
        while (n != 0) {

            fighter_c = fighter_max_ratio * alive_pop();
            academic_c = academic_ratio * alive_pop();

            int alive = alive_pop();

            select_soldiers_and_academics(true);
            year++;

            if (ruler.second == nullptr || !ruler.second->alive) {
                cout << "ruler dies" << endl;
                ruler.first = false;
                ruler.second = nullptr;
            }
            int childs = reproduction(year);

            // cout << "New Children: " << childs << endl;
            for (auto elem : people) {
                // run the enivironmenal factors here before aging, aging will weed out those who did not survive
                // for (int i = 0; i < 5; i++) {
                //     if (elem->age < 16) continue;
                //     elem->encounter(encount["food_gather"]);
                // }
                if (!elem->alive) continue;
                elem->work(encounte, ruler);


                elem->encounter(encounte["disease"]);
                elem->encounter(encounte["accident"]);

                elem->aging_process(supported_pop, alive);
            }
            // cout << "dude" << endl;
            clear_junk(military, "fighter");
            //print_military();
            if (ruler.second != nullptr && ruler.first == true) {
                cout << ruler.second->name << " consolidated power" << endl;
                ruler.first = true;
            }
            // cout << "jonny" << endl;
            n--;
        }
    }

};

