#include <iostream>
#include <vector>
using namespace std;



class Occupation {
    public:
    string name;
    Occupation(string name)  {this->name = name;};
    void set_name(string name) {this->name = name;}
    string ret_name () {return name;}

};

class Fighter : public Occupation {
    int power = 1903;
    public:
    using Occupation::Occupation;

    int ret_power() {return power;}
};

int main() {
    vector<Occupation*> peoples;
    Fighter* elem = new Fighter("bob");
    Occupation* elem2 = new Occupation("john");

    // elem->set_name("bob");
    // elem2->set_name("john");
    cout << elem->ret_name() << " " << elem2->ret_name() << endl;

    peoples.push_back(elem);
    peoples.push_back(elem2);

    cout << elem->ret_power() << endl;

    cout << !0;
}
