#pragma once
#include "map.h"
struct State;

struct Game {
    Game(vector<Fraction*>& Fr, Map& W_m, ArmyCreator& A_c, int c);
    State* current_state;
    void set_current_state(State* s);
    void global_map();
    void army_management();
    void city_management();
};

struct State {
    State(vector<Fraction*>& Fr, Map& W_m, ArmyCreator& A_c, int c):Fractions(Fr), World_map(W_m), A_Creator(A_c), fraction_step_id(c), current_army_id(0){}
    vector<Fraction*>& Fractions;
    Map World_map;
    ArmyCreator A_Creator;
    int fraction_step_id;
    int current_army_id;
    virtual void set_next_step(Game* g) = 0;
    virtual void global_map(Game* g);
    virtual void army_management(Game* g);
    virtual void city_management(Game* g);
    virtual void action(Game* g){};
    virtual void update(Game* g){};
    virtual void exit();
    virtual void help() = 0;
};

struct Global_map: public State {
    Global_map(vector<Fraction*>& Fr, Map& W_m, ArmyCreator& A_c, int c):State(Fr, W_m, A_c, c){};
    void set_next_step(Game* g);
    void action(Game* g);
    void update(Game* g);
    void help();
};

struct Army_management: public State {
    Army_management(vector<Fraction*>& Fr, Map& W_m, ArmyCreator& A_c, int c):State(Fr, W_m, A_c, c){};
    void set_next_step(Game* g);
    void action(Game* g);
    void update(Game* g);
    void help();
    void crusade(bool& destroyed, int arm_num);
};

struct City_management: public State {
    City_management(vector<Fraction*>& Fr, Map& W_m, ArmyCreator& A_c, int c):State(Fr, W_m, A_c, c){};
    void set_next_step(Game* g);
    void action(Game* g);
    void update(Game* g);
    void help();
};

struct  Battle {
    void battle(Army* first, Army* second);
};