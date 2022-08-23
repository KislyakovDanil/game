#include "fraction.h"

Fraction::Fraction(UnitCreator U_Creator, string n, int first_cap_c, int second_cap_c, int id): Fraction_Army(0, nullptr), name(n), capital_coord(make_pair(first_cap_c,second_cap_c)), fraction_id(id), gold(100), income(100),active_armies(0, true){
    Fraction_unit_creator = U_Creator.CreateUnitFactory(id);
}