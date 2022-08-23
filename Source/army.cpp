#include "army.h"

void RealArmy::add_unit(Unit* u) {
    Units.push_back(u);
}

RealArmy::~RealArmy() {
    for (vector<Unit*>::iterator it = Units.begin() ; it != Units.end(); ++it) {
        delete (*it);
    }
}

void RealArmy::attack_commander_skill() {
    cout << "Kill";
}

void RealArmy::defense_commander_skill() {
    cout << "Defense";
}

void RealArmy::move_commander_skill() {
    cout << "Run";
}


void RealArmy::go_to_square(pair<int,int> l){
    location.first = l.first;
    location.second = l.second;
}

int RealArmy::get_units_size(){
    return Units.size();
}

Unit* RealArmy::extract_last_unit(){
    Unit* warrior = Units.back();
    Units.pop_back();
    return  warrior;
}

vector<Unit*> RealArmy::get_units(){
    return Units;
}

int RealArmy::get_fraction_id(){
    return fraction_id;
}

int RealArmy::get_army_id(){
    return army_id;
}

void RealArmy::set_army_id(int n){
    army_id = n;
}

pair<int,int> RealArmy::get_location(){
    return location;
}

Army* ArmyCreator::CreateArmy(UnitFactory* unit_creator,int inf_num, int arch_num, int knig_num, int f_id, int a_id, pair<int, int> location){
    RealArmy* army = new RealArmy(f_id, a_id);
    for (int i = 0; i < inf_num; ++i) {
        army->add_unit(unit_creator->CreateInfantryman());
    }
    for (int i = 0; i < arch_num; ++i) {
        army->add_unit(unit_creator->CreateArcher());
    }
    for (int i = 0; i < knig_num; ++i) {
        army->add_unit(unit_creator->CreateKnight());
    }
    army->go_to_square(location);//переписать на подписку на соответствующий квадрат
    return army;
}

void ArmyCreator::MergeArmy(Army* first, Army* second){
    while(second->get_units_size() != 0){
        first->add_unit(second->extract_last_unit());
    }
    delete second;
}

Commander::Commander(Army* a) {
    army = a;
}

void Commander::attack_commander_skill() {
    army->attack_commander_skill();
}

void Commander::defense_commander_skill() {
    army->defense_commander_skill();
}

void Commander::move_commander_skill() {
    army->move_commander_skill();
}

void Commander::go_to_square(pair<int,int> l){
    army->go_to_square(l);
}

void Commander::add_unit(Unit* u) {
    army->add_unit(u);
}

int Commander::get_units_size(){
    return army->get_units_size();
}

Unit* Commander::extract_last_unit(){
    return army->extract_last_unit();
}

vector<Unit*> Commander::get_units(){
    return army->get_units();
}

int Commander::get_fraction_id(){
    return army->get_fraction_id();
}

int Commander::get_army_id(){
    return army->get_army_id();
}

void Commander::set_army_id(int n){
    army->set_army_id(n);
}

pair<int,int> Commander::get_location(){
    return army->get_location();
}

CommanderAttackArea::CommanderAttackArea(Army* a): Commander(a){}

void  CommanderAttackArea::attack_commander_skill() {
    Commander::attack_commander_skill();
    cout << "Them";
}

CommanderAttackStrong::CommanderAttackStrong(Army* a): Commander(a){}

void  CommanderAttackStrong::attack_commander_skill() {
    Commander::attack_commander_skill();
    cout << "All";
}

CommanderDefenseArea::CommanderDefenseArea(Army* a): Commander(a){}

void  CommanderDefenseArea::defense_commander_skill() {
    Commander::defense_commander_skill();
    cout << "Area";
}

CommanderDefenseStrong::CommanderDefenseStrong(Army* a): Commander(a){}

void  CommanderDefenseStrong::defense_commander_skill() {
    Commander::defense_commander_skill();
    cout << "Fully";
}

CommanderMoveDistance::CommanderMoveDistance(Army* a): Commander(a){}

void  CommanderMoveDistance::move_commander_skill() {
    Commander::move_commander_skill();
    cout << "Away";
}

CommanderMoveNavigation::CommanderMoveNavigation(Army* a): Commander(a){}

void  CommanderMoveNavigation::move_commander_skill() {
    Commander::move_commander_skill();
    cout << "OnWater";
}

Army* CommanderLevelUpper::CommanderLevelUp(Army* army, int level_up_id) {
    switch (level_up_id) {
        case 0:
            return new CommanderAttackArea(army);
        case 1:
            return new CommanderAttackStrong(army);
        case 2:
            return new CommanderDefenseArea(army);
        case 3:
            return new CommanderDefenseStrong(army);
        case 4:
            return new CommanderMoveDistance(army);
        case 5:
            return new CommanderMoveNavigation(army);
    }
};