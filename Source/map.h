#pragma once
#include "fraction.h"

struct Location {
    Location(string l = "field"):land(l), Armies(0){};
    void subscribe(Army* a){
        Armies.push_back(a);
    }
    void unsubscribe(int n, int f){
        for (int i = 0; i < Armies.size(); ++i){
            if (Armies[i]->get_army_id() == n && Armies[i]->get_fraction_id() == f){
                Armies.erase(Armies.begin() + i);
            }
        }
    }
    vector<Army*> Armies;
    string land;
};

struct Map {
    Map(int n):battlefield(n, vector<Location*>(n, nullptr)){};
    void Print_Map(const vector<Fraction*>& Fractions);
    vector<vector<Location*>> battlefield;
};