#include "unit.h"


Unit::Unit(int h, int d, int c_d, int s): Unit_HP(h), Max_HP(h), Damage(d), Combat_Distance(c_d), Speed(s), Location(make_pair(-1,-1)){};

void Unit::go_to_square(pair<int,int> square) {
    Location.first = square.first;
    Location.second = square.second;
}


Infantryman::Infantryman(int h, int d, int s):  Unit(h, d, 1, s){}

void Infantryman::class_skill() {
    cout << "InfantrymanSkill" << endl;
}


Archer::Archer(int h, int d, int s):  Unit(h, d, 3, s){}

void Archer::class_skill() {
    cout << "ArcherSkill" << endl;
}


Knight::Knight(int h, int d, int s):  Unit(h, d, 1, s){}

void Knight::class_skill() {
    cout << "KnightSkill" << endl;
}


StandartInfantryman::StandartInfantryman(): Infantryman(12, 4, 2){}

Unit* StandartInfantryman::clone(){
    return new StandartInfantryman(*this);
}

void StandartInfantryman::special_skill() {
    cout << "StandartInfantrymanSkill" << endl;
}


StandartArcher::StandartArcher(): Archer(8, 2, 3){}

Unit* StandartArcher::clone(){
    return new StandartArcher(*this);
}

void StandartArcher::special_skill() {
    cout << "StandartArcherSkill" << endl;
}


StandartKnight::StandartKnight(): Knight(15, 6, 6){}

Unit* StandartKnight::clone(){
    return new StandartKnight(*this);
}

void StandartKnight::special_skill() {
    cout << "StandartKnightSkill" << endl;
}


EnglandArcher::EnglandArcher(): Archer(8, 3, 3){}

Unit* EnglandArcher::clone(){
    return new EnglandArcher(*this);
}

void EnglandArcher::special_skill() {
    cout << "EnglandArcherSkill" << endl;
}


FranceKnight::FranceKnight(): Knight(18, 6, 5){}

 Unit* FranceKnight::clone(){
    return new FranceKnight(*this);
}

void FranceKnight::special_skill() {
    cout << "FranceKnightSkill" << endl;
}