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
#include "Object.h"
// #include "Tool.h"
using namespace std;


class Occupation {
    // fighter, academic, ruler, useless, engineer, builder, athlete, scientist, mathematician
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

struct Sec {
    double temperature = 75;
    double sunlight = 50;
    double soil_quality = 20;
    Food* gatherFood;
    Food* preyFood;
    Food* predatorFood;
    
    Sec() {
        gatherFood = new Food("berries", .89, false);
        preyFood = new Food("deer", .7, true);
        predatorFood = new Food("strong deer", .2, true);
    };
    Sec(double temp, double sun, double soil) : temperature(temp), sunlight(sun), soil_quality(soil) {
        gatherFood = new Food("berries", .89, false);
        preyFood = new Food("deer", .7, true);
        predatorFood = new Food("strong deer", .2, true);
    };

    ~Sec() {
        delete gatherFood;
        delete preyFood;
        delete predatorFood;
    }
};

class Person {
    public:

    int birth_year = -20;
    int age = 0;

    Person* father = nullptr;
    Person* mother = nullptr;
    vector<Person*> children;
    vector<Person*> friends = {};

    vector<Object*> inventory;
    
    Dna* dna;
    vector<Dna*> reprod;



    bool alive = true;
    string death_cause = "alive";
    // actual metrics
    // environmental factors

    string name = "0";
    string first_name = "0";
    int id = stoi(first_name);
    string family_name = "0";
    double food_intake, nutrition, upbringing, care, historical_food_data = 1;

    double social_status = 0.0;
    

    string occ = "useless";
    double salary = 0;
    map<string, double> proficiency; // proficiency in tools and skills (where relevant)


    // risks
    double disease;
    double accidental;


    // genetics based
    // etnicity data
    Ethnicity* ethnic = nullptr;
    string sector_name = "base";


    double height, strength, speed, stamina, weight, charisma, willpower, intel, melanin, parental, compassion, dexterity, weapon_prof;

    vector<double*> real = {&height, &strength, &speed, &stamina, &charisma, &weight, &willpower, &intel, &melanin, &parental, &compassion, &dexterity};

    double fit_interest, str_interest, spe_interest, char_interest, intel_interest, dex_interest;

    // variable metrics

    double wealth, food, hunger, child_hunger, yuhnow = 0.0;

    // job suitibility
    double hunter, farmer, fighter, academic, ruler, engineer, builder, athlete, scientist, merchant;

    double years_service = 0; //military 


    double fire, water, earth, air, martial = 0;

    void fillInterests();

    Person(Person* father, Person* mother, string name, int year = 0);
    Person(Dna* dna, string name, int age, vector<Dna*> rep, string race = "basic", string occupation = "useless");
    ~Person() {delete ethnic;}

    double differential(vector<double> diffs, vector<double> diffImp) {
        double sum = 0;
        for (int i = 0; i < 12; ++i) {
            sum += (*real[i] - diffs[i]) * diffImp[i];
        }

        return sum;
    }

    void risks();
    string save_person();
    void work(pair<bool, Person*>& ruler);
    void occupation_impact() {};
    void find_job();
    void aging_process(Sec* sec, pair<bool, Person*>& ruler);

    void fight(Food* animal);
    void fight(Person* person);

    /**
     * Takes in the chance of disease as a double
     * @return Runs the chance that the person dies from disease
     */
    void disease_chance(Sec* sec);

    /**
     * @return Checks if the person has fulfilled food requirements, if they havent affect their speed, strength, weight accordingly
     */ 
    void check_hunger();

    void set_hunger();

  /**
     * Gathering food items, 20 iterations of searching for food, search can result in Objects which are added to the persons inventory
     * Considers environmental factors effecting gathering and abundence of gatherable food, in dangerous terrain, action requires stamina
     
     * @return Double
     */
    double gather(Sec* sec);

    /**
     * Gathering food items, 20 iterations of searching for food and trying to hunt it down, dying is possible but food quantities and
     * the nutrition of the resulting food is higher. 
     
     * @return Double
     */
    double hunt(Sec* sec);

    /**
     * Consume the most nutritious food objects in inventory until hunger is quenched
     
     * @return Double
     */
    double eat(bool commit);

    /**
     * Cook cookable foods into their cookable variants
     
     * @return Double
     */
    double cook(bool commit);

    /**
     * Turn wealth into food up to 95% of wealth is used or until hunger is quenched.
     * @return Double
     */
    double buy_food(bool commit) {
        double max_to_spend = wealth*.95;
        if (max_to_spend - hunger - child_hunger > 0) {
            wealth -= hunger;
            food += hunger + child_hunger;
        }
        return 0.0;
    };

    // human experience related activities

    /**
     * Examine the sectors nearby the persons sector
     * @return Double
     */
    double explore(bool commit);

    /**
     * Provide attention to children, helps increase their development.
     * @return Double
     */
    double spendTimeWithChild(bool commit);
    
    // intelligence related activities

    /**
     * Performed at the start of a person's turn. Calculates the exprected gain with weights for activities, and selects the k activities that
     * are most beneficial to the person, there is a degree of uncertainity which is higher when intelligence is lower, this can cause
     * people to make unoptimal decisions if they are not smart, or if they are overally ambitious, compassionate, parental, etc
     * @return Double
     */
    vector<string> analyze();


    /**
     * Think of the future and what could be, chance to make a major change
     * @return Double
     */
    double ponder(bool commit);

    /**
     * Come up with a theory of explanation for a processes, if correct, unlock a discovery in field of study
     * @return Double
     */
    double hypothesize(bool commit);

    /**
     * Create an object and add it to inventory
     * @return Double
     */
    double create(Object* obj = nullptr);

    /**
     * Perform occupational duties and recienve salary to wealth
     * @return Double
     */
    double work();

    void speedTraining(double focus) {};
    void strengthTraining(double focus) {};
    void fitnessTraining(double focus){};
    void charismaTraining(double focus){};
    void dexterityTraining(double focus){};

    // Various printing methods for a person and their stats
    void print_base();
    void print_compact();
    void print_actual();

};
class Peoples {
    public:
    string label = "name,age,birth year,first_name,family_name,father name,mother name,alive,death_cause,occ,height,strength,speed,stamina,weight,charisma,willpower,intel,melanin,parental,compassion,dexterity,weapon_prof,wealth,academic,farmer,fighter,hunter,merchant,ruler,years_service"; 

    vector<Person*> military; // capped role
    vector<Person*> academics; // capped role
    pair<bool, Person*> ruler = pair(false, nullptr);
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

    void populate_data(string filename) {
        cout << "here" << endl;
        ofstream file;
        file.open("simulation_runs/" + filename);
        file << label << "\n";
        for (auto person : people) {
            cout << "we wrote " << person->name << "'s data to the file" << endl;
            file << person->save_person() << '\n';
        }

        file.close();
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
                if (elem->age > 16 && elem->occ != opp && elem->occ != self) {
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
                if (elem->age > 16 && elem->occ != opp && elem->occ != self) {
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

    void simulate(int n, int& year, Sec* sec) {
        // cout << "Peoples simulate call" << endl;
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

            // cout << "reprods" << endl;
            int childs = reproduction(year);


            cout << "New Children: " << childs << endl;
            for (auto elem : people) {
                if (!elem->alive) continue;
                elem->aging_process(sec, ruler); // will perform all of a persons yearly activities
            }
            // cout << "dude" << endl;
            clear_junk(military, "fighter");
            print_military();
            if (ruler.second != nullptr && ruler.first == true) {
                cout << ruler.second->name << " consolidated power" << endl;
                ruler.first = true;
            }
            // cout << "jonny" << endl;
            n--;
        }
    }

};

