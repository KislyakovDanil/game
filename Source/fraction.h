#pragma once
#include "army.h"

struct Fraction {
    Fraction(UnitCreator U_Creator, string n, int first_cap_c, int second_cap_c, int id);
    int fraction_id;
    int income;
    int gold;
    string name;
    pair<int,int> capital_coord;
    vector<Army*> Fraction_Army;
    vector<bool> active_armies;
    UnitFactory* Fraction_unit_creator;
};