#include "Source\game.h"

int main() {
    ArmyCreator A_Creator;
    UnitCreator U_Creator;
    CommanderLevelUpper ComLevUpper;
    vector<Fraction*> Fractions(0, nullptr);
    cout << "Choose map size (recommend from 3 to 6):";
    int map_size = 0;
    while (map_size == 0) {
        string inp;
        cin >> inp;
        for (char i: inp) {
            if (isdigit(i) && map_size * 10 + i - '0' > 1) {
                map_size = map_size * 10 + i - '0';
            } else {
                map_size = 0;
                cout << "Incorrect input, repeat please" << endl;
                break;
            }
        }
    }
    Map World_map(map_size);
    for (int i = 0; i < World_map.battlefield.size(); ++i){
        for (int j = 0; j < World_map.battlefield.size(); ++j){
            World_map.battlefield[i][j] = new Location();
        }
    }
    Fractions.push_back(new Fraction(U_Creator, "England", 0, 0, 0));
    Fractions.push_back(new Fraction(U_Creator, "France", map_size-1, map_size-1, 1));
    cout << "Choose first country:" << endl;
    for (Fraction* f: Fractions){
        cout << f->name << "-" << f->fraction_id  << endl;
    }
    int fraction_id = 0;
    bool flag;
    do {
        flag = false;
        string inp;
        cin >> inp;
        for (char i: inp) {
            if (isdigit(i) && fraction_id * 10 + i - '0' >= 0 && fraction_id * 10 + i - '0' < Fractions.size()) {
                fraction_id = fraction_id * 10 + i - '0';
            } else {
                flag = true;
                fraction_id = 0;
                cout << "Incorrect input, repeat please" << endl;
                break;
            }
        }
    } while (flag);
    cout << "To call for help enter 'h'" << endl;
    Game game(Fractions, World_map, A_Creator, fraction_id);
    game.global_map();
    return 0;
}