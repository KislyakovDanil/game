#include "map.h"

void Map::Print_Map(const vector<Fraction*>& Fractions){
    for (int j = 0; j < Fractions.size(); ++j) {
        cout << Fractions[j]->name << " gold = " << Fractions[j]->gold << endl;
    }
    for (int i = 0; i < battlefield.size(); ++i){
        for (int j = 0; j < battlefield.size(); ++j){
            if (battlefield[i][j]->Armies.empty()){
                bool flag = true;
                for (int k = 0; k < Fractions.size(); ++k){
                    if (Fractions[k]->capital_coord.first == i && Fractions[k]->capital_coord.second == j){
                        flag = false;
                        cout << Fractions[k]->name[0] << "C ";
                    }
                }
                if(flag){
                    cout << "__" << " ";
                }
            } else {
                cout << Fractions[battlefield[i][j]->Armies.back()->get_fraction_id()]->name[0] << battlefield[i][j]->Armies.back()->get_army_id() << " ";
            }
        }
        cout << endl;
    }
}
