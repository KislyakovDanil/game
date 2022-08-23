#include "game.h"

Game::Game(vector<Fraction*>& Fr, Map& W_m, ArmyCreator& A_c, int c) {
    current_state = new Global_map(Fr, W_m, A_c, c);
}

void Game::set_current_state(State* s) {
    current_state = s;
}

void Game::global_map() {
    current_state->global_map(this);
}

void Game::army_management() {
    current_state->army_management(this);
}

void Game::city_management(){
    current_state->city_management(this);
}

void State::global_map(Game* g) {
    set_next_step(g);
    delete this;
}

void State::army_management(Game* g) {
    cout << "change army number (or enter 'r' go to the global map):" << endl;
    current_army_id = -1;
    while (current_army_id == -1) {
        current_army_id = 0;
        string inp;
        cin >> inp;
        if (inp[0] == 'r'){//не уверен в этом моменте
            g->set_current_state(new Global_map(Fractions, World_map, A_Creator, fraction_step_id));
            g->global_map();
            delete this;
            return;
        } else {
            for (char j: inp) {
                if (isdigit(j) && current_army_id * 10 + j - '0' >= 0 && current_army_id >= 0 && current_army_id < Fractions[fraction_step_id]->Fraction_Army.size()) {
                    current_army_id = current_army_id * 10 + j - '0';
                } else {
                    current_army_id = -1;
                    cout << "Incorrect input, please repeat" << endl;
                    break;
                }
            }
        }
    }
    set_next_step(g);
    delete this;
}

void State::city_management(Game* g) {
    set_next_step(g);
    delete this;
}

void State::exit() {
    World_map.Print_Map(Fractions);
    cout << Fractions[fraction_step_id]->name << " win" << endl;
}

void Global_map::help() {
    cout << "Choose an action:" << endl;
    cout << "To call for help enter 'h'" << endl;
    cout << "To go to the army menu enter 'a'" << endl;
    cout << "To go to the city menu enter 'c'" << endl;
    cout << "To finish a step enter 'f'" << endl;
    cout << "To print the map enter 'm'" << endl;
    cout << "To end the Game enter 'e'" << endl;
};

void Global_map::set_next_step(Game* g){
    bool flag;
    string command;
    do {
        cin >> command;
        flag = false;
        while (command == "h") {
            help();
            cin >> command;
        }
        if (command == "c") {
            g->set_current_state(new City_management(Fractions, World_map, A_Creator, fraction_step_id));
            g->city_management();
        } else if (command == "a") {
            g->set_current_state(new Army_management(Fractions, World_map, A_Creator, fraction_step_id));
            g->army_management();
        } else if (command == "f") {
            action(g);
        } else if (command == "m") {
            update(g);
        } else if (command == "e") {
            exit();
        } else {
            flag = true;
            cout << "Incorrect input, please repeat your command" << endl;
        }
    } while (flag);
}

void Global_map::action(Game* g) {
    fraction_step_id = ++fraction_step_id % Fractions.size();
    World_map.Print_Map(Fractions);
    cout << Fractions[fraction_step_id]->name << " step" << endl;
    Fractions[fraction_step_id]->active_armies.resize(0);
    Fractions[fraction_step_id]->active_armies.resize(Fractions[fraction_step_id]->Fraction_Army.size(), true);
    Fractions[fraction_step_id]->gold += Fractions[fraction_step_id]->income - Fractions[fraction_step_id]->Fraction_Army.size() * 10;
    if (Fractions[fraction_step_id]->gold < 50){
        Fractions[fraction_step_id]->gold = 50;
    }
    set_next_step(g);
}

void Global_map::update(Game *g){
    World_map.Print_Map(Fractions);
    set_next_step(g);
}

void City_management::help() {
    cout << "Choose an action:" << endl;
    cout << "To call for help enter 'h'" << endl;
    cout << "To go to the army menu enter 'a'" << endl;
    cout << "To go to the global menu enter 'g'" << endl;
    cout << "To create an army enter 'c' and proportions of infantrymen, archers and knights in the army. Like 'c 0 1 1'" << endl;
    cout << "To upgrade your city enter 'u'" << endl;
};

void City_management::set_next_step(Game* g){
    bool flag;
    string command;
    do {
        cin >> command;
        flag = false;
        while (command == "h") {
            help();
            cin >> command;
        }
        if (command == "g") {
            g->set_current_state(new Global_map(Fractions, World_map, A_Creator, fraction_step_id));
            g->global_map();
        } else if (command == "a") {
            g->set_current_state(new Army_management(Fractions, World_map, A_Creator, fraction_step_id));
            g->army_management();
        } else if (command == "u") {
            update(g);
        } else if (command == "c") {
            action(g);
        } else {
            flag = true;
            cout << "Incorrect input, please repeat your command" << endl;
        }
    } while (flag);
}

void City_management::update(Game* g) {
    Fractions[fraction_step_id]->income += Fractions[fraction_step_id]->gold / 10;
    Fractions[fraction_step_id]->gold = 0;
    set_next_step(g);
}

void City_management::action(Game* g) {
    vector<int> units(3, -1);
    for (int i = 0; i < 3; ++i) {
        while (units[i] == -1) {
            units[i] = 0;
            string inp;
            cin >> inp;
            for (char j: inp) {
                if (isdigit(j) && units[i] * 10 + j - '0' >= 0) {
                    units[i] = units[i] * 10 + j - '0';
                } else {
                    units[i] = -1;
                    cout << "Incorrect input, please repeat number of unit " << i+1 <<  " type" << endl;
                    break;
                }
            }
        }
    }
    int inf_proport, arch_proport, knig_proport;
    int sum = units[0] + units[1] + units[2];
    inf_proport = units[0] * Fractions[fraction_step_id]->gold / sum;
    arch_proport = units[1] * Fractions[fraction_step_id]->gold / sum;
    knig_proport = units[2] * Fractions[fraction_step_id]->gold / sum;
    Fractions[fraction_step_id]->gold = 0;
    Fractions[fraction_step_id]->Fraction_Army.push_back(A_Creator.CreateArmy(Fractions[fraction_step_id]->Fraction_unit_creator, inf_proport, arch_proport, knig_proport, Fractions[fraction_step_id]->fraction_id, Fractions[fraction_step_id]->Fraction_Army.size(), make_pair(Fractions[fraction_step_id]->capital_coord.first,Fractions[fraction_step_id]->capital_coord.second)));
    World_map.battlefield[Fractions[fraction_step_id]->capital_coord.first][Fractions[fraction_step_id]->capital_coord.second]->subscribe(Fractions[fraction_step_id]->Fraction_Army.back());
    Fractions[fraction_step_id]->active_armies.push_back(false);
    set_next_step(g);
}

void Army_management::help() {
    cout << "Choose an action:" << endl;
    cout << "To call for help enter 'h'" << endl;
    cout << "To go to the city menu enter 'c'" << endl;
    cout << "To go to the global menu enter 'g'" << endl;
    cout << "To upgrade your army enter 'u' and  number 0 to 5" << endl;
    cout << "To move the army enter 'm' and string from one to three route from (U, D, R, L). Like 'm LDD'" << endl;
};

void Army_management::set_next_step(Game* g){
    bool flag;
    string command;
    do {
        cin >> command;
        flag = false;
        while (command == "h") {
            help();
            cin >> command;
        }
        if (command == "g") {
            g->set_current_state(new Global_map(Fractions, World_map, A_Creator, fraction_step_id));
            g->global_map();
        } else if (command == "c") {
            g->set_current_state(new City_management(Fractions, World_map, A_Creator, fraction_step_id));
            g->city_management();
        } else if (command == "u") {
            update(g);
        } else if (command == "m") {
            action(g);
        } else {
            flag = true;
            cout << "Incorrect input, please repeat your command" << endl;
        }
    } while (flag);
}

void Army_management::update(Game* g) {
    CommanderLevelUpper* CLU;
    int level_up_id = -1;
    while (level_up_id == -1) {
        level_up_id = 0;
        string inp;
        cin >> inp;
        for (char j: inp) {
            if (isdigit(j) && level_up_id * 10 + j - '0' >= 0) {
                level_up_id = level_up_id * 10 + j - '0';
            } else {
                level_up_id = -1;
                cout << "Incorrect input, please repeat number 0 to 5" << endl;
                break;
            }
        }
    }
    CLU->CommanderLevelUp(Fractions[fraction_step_id]->Fraction_Army[current_army_id], level_up_id);
    set_next_step(g);
}

void Army_management::action(Game* g) {
    if (Fractions[fraction_step_id]->active_armies[current_army_id]){
        Fractions[fraction_step_id]->active_armies[current_army_id] = false;
        bool destroyed = false;
        crusade(destroyed, current_army_id);
        bool victory = false;
        if (!destroyed) {
            for (Fraction *f: Fractions) {
                if (Fractions[fraction_step_id]->Fraction_Army[current_army_id]->get_location().first == f->capital_coord.first && Fractions[fraction_step_id]->Fraction_Army[current_army_id]->get_location().second == f->capital_coord.second && f->fraction_id != Fractions[fraction_step_id]->fraction_id) {
                    victory = true;
                }
            }
        }
        if (victory) {
            exit();
        } else {
            set_next_step(g);
        }
    } else {
        cout << "This army was already moving" << endl;
        set_next_step(g);
    }
}

void  Army_management::crusade(bool& destroyed, int arm_num){
    string route;
    cin >> route;
    int x_coord = Fractions[fraction_step_id]->Fraction_Army[current_army_id]->get_location().first;
    int y_coord = Fractions[fraction_step_id]->Fraction_Army[current_army_id]->get_location().second;
    int s = 3;
    if (route.size() < 3){
        s = route.size();
    }
    for (int i = 0; i < s; ++i){
        World_map.battlefield[x_coord][y_coord]->unsubscribe(Fractions[fraction_step_id]->Fraction_Army[arm_num]->get_army_id(), Fractions[fraction_step_id]->Fraction_Army[arm_num]->get_fraction_id());
        if (route[i] == 'L' || route[i] == 'l') {
            if (y_coord > 0) {
                --y_coord;
            }
        } else if (route[i] == 'R' || route[i] == 'r') {
            if (y_coord < World_map.battlefield.size()-1){
                ++y_coord;
            }
        } else if (route[i] == 'U' || route[i] == 'u') {
            if (x_coord > 0){
                --x_coord;
            }
        } else if (route[i] == 'D' || route[i] == 'd') {
            if (x_coord < World_map.battlefield.size()-1){
                ++x_coord;
            }
        } else {
            cout << "Incorrect" << i+1 << "route, the army remains in place" << endl;
            continue;
        }
        int enemy_fraction_id = -1;
        if (!World_map.battlefield[x_coord][y_coord]->Armies.empty() && World_map.battlefield[x_coord][y_coord]->Armies[0]->get_fraction_id() != fraction_step_id){
            enemy_fraction_id = World_map.battlefield[x_coord][y_coord]->Armies[0]->get_fraction_id();
            for (int j = 0; j < World_map.battlefield[x_coord][y_coord]->Armies.size(); ++j) {
                Battle* B;
                B->battle(Fractions[fraction_step_id]->Fraction_Army[arm_num], World_map.battlefield[x_coord][y_coord]->Armies[j]);
                if (Fractions[fraction_step_id]->Fraction_Army[arm_num]->get_units_size() == 0) {
                    World_map.battlefield[x_coord][y_coord]->unsubscribe(Fractions[fraction_step_id]->Fraction_Army[arm_num]->get_army_id(), Fractions[fraction_step_id]->Fraction_Army[arm_num]->get_fraction_id());
                    Fractions[fraction_step_id]->Fraction_Army.erase(Fractions[fraction_step_id]->Fraction_Army.begin() + arm_num);
                    for (int k = 0; k < Fractions[fraction_step_id]->Fraction_Army.size(); ++k){
                        Fractions[fraction_step_id]->Fraction_Army[k]->set_army_id(k);
                        if (k >= arm_num) {
                            Fractions[fraction_step_id]->active_armies[k] = Fractions[fraction_step_id]->active_armies[k+1];
                        }
                    }
                    destroyed = true;
                    return;
                }
                if (World_map.battlefield[x_coord][y_coord]->Armies[j]->get_units_size() == 0) {
                    int arm_id = World_map.battlefield[x_coord][y_coord]->Armies[j]->get_army_id();
                    World_map.battlefield[x_coord][y_coord]->unsubscribe(World_map.battlefield[x_coord][y_coord]->Armies[j]->get_army_id(), World_map.battlefield[x_coord][y_coord]->Armies[j]->get_fraction_id());
                    Fractions[enemy_fraction_id]->Fraction_Army.erase(Fractions[enemy_fraction_id]->Fraction_Army.begin() + arm_id);
                    for (int k = 0; k < Fractions[enemy_fraction_id]->Fraction_Army.size(); ++k){
                        Fractions[enemy_fraction_id]->Fraction_Army[k]->set_army_id(k);
                    }
                    --j;
                }
            }
        }
        World_map.battlefield[x_coord][y_coord]->subscribe(Fractions[fraction_step_id]->Fraction_Army[arm_num]);
        Fractions[fraction_step_id]->Fraction_Army[arm_num]->go_to_square(make_pair(x_coord,y_coord));
    }
}

void Battle::battle(Army* first, Army* second) {
    //здесь скилы командиров
    Unit *first_army_unit = first->extract_last_unit();
    Unit *second_army_unit = second->extract_last_unit();
    while (first->get_units_size() != 0 && second->get_units_size() != 0) {
        //здесь скилы юнитов
        if (first_army_unit->Combat_Distance > 1) {
            second_army_unit->Unit_HP -=
                    first_army_unit->Damage * (first_army_unit->Combat_Distance) * 2 / (second_army_unit->Speed);
        }
        if (second_army_unit->Combat_Distance > 1) {
            first_army_unit->Unit_HP -=
                    second_army_unit->Damage * (second_army_unit->Combat_Distance) * 2 / (first_army_unit->Speed);
        }
        while (first_army_unit->Unit_HP > 0 && second_army_unit->Unit_HP > 0) {
            //здесь тоже скилы юнитов
            second_army_unit->Unit_HP = second_army_unit->Unit_HP - first_army_unit->Damage;
            first_army_unit->Unit_HP = first_army_unit->Unit_HP - second_army_unit->Damage;
        }
        if (first_army_unit->Unit_HP <= 0) {
            first_army_unit = first->extract_last_unit();
        }
        if (second_army_unit->Unit_HP <= 0) {
            second_army_unit = second->extract_last_unit();
        }
    }
}