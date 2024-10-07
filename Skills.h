#ifndef SKILLS_H
#define SKILLS_H

#include <map>
#include <string>
#include "People.h"
#include "Object.h"

class Skills {
    static std::map<std::string, function<double>(Person*)> skillset;

    // Basic activities

    // food related activities

    /**
     * Gathering food items, 20 iterations of searching for food, search can result in Objects which are added to the persons inventory
     * Considers environmental factors effecting gathering and abundence of gatherable food, in dangerous terrain, action requires stamina
     
     * @return Double
     */
    double gather(Person* person);

    /**
     * Gathering food items, 20 iterations of searching for food and trying to hunt it down, dying is possible but food quantities and
     * the nutrition of the resulting food is higher. 
     
     * @return Double
     */
    double hunt(Person* person);

    /**
     * Consume the most nutritious food objects in inventory until hunger is quenched
     
     * @return Double
     */
    double eat(Person* person);

    /**
     * Cook cookable foods into their cookable variants
     
     * @return Double
     */
    double cook(Person* person);

    /**
     * Turn wealth into food up to 75% of wealth is used or until hunger is quenched.
     * @return Double
     */
    double buy_food(Person* person);

    // human experience related activities

    /**
     * Examine the sectors nearby the persons sector
     * @return Double
     */
    double explore(Person* person);

    /**
     * Provide attention to children, helps increase their development.
     * @return Double
     */
    double spendTimeWithChild(Person* person);
    
    // intelligence related activities

    /**
     * Performed at the start of a person's turn. Calculates the exprected gain with weights for activities, and selects the k activities that
     * are most beneficial to the person, there is a degree of uncertainity which is higher when intelligence is lower, this can cause
     * people to make unoptimal decisions if they are not smart, or if they are overally ambitious, compassionate, parental, etc
     * @return Double
     */
    double analyze(Person* person);


    /**
     * Think of the future and what could be, chance to make a major change
     * @return Double
     */
    double ponder(Person* person);

    /**
     * Come up with a theory of explanation for a processes, if correct, unlock a discovery in field of study
     * @return Double
     */
    double hypothesize(Person* person);

    /**
     * Create an object and add it to inventory
     * @return Double
     */
    double create(Person* person, Object* obj = nullptr);

    /**
     * Perform occupational duties and recienve salary to wealth
     * @return Double
     */
    double work(Person* person);

    Skills() {

    }
};

#endif