#pragma once
#include <iostream>
using namespace std;

struct Unit{
    int Unit_HP; // хп конкретного юнита
    const int Max_HP; // максимальны хп данного вида юнитов
    const int Damage; // атака данного вида юнитов
    const int Combat_Distance; // максимальное расстояние атаки данного вида юнитов
    const int Speed; // скорость данного вида юнитов
    pair<int,int> Location; // местонахождение конкретного юнита
    Unit(int h, int d, int c_d, int s);
    virtual void class_skill() = 0;
    virtual void special_skill() = 0;
    virtual Unit* clone() = 0;
    void go_to_square(pair<int,int> square);
    virtual ~Unit() {};
};

// Базовые классы всех возможных видов юнитов
struct Infantryman: public Unit {
    Infantryman(int h, int d, int s);
    virtual void special_skill() = 0;
    virtual Unit* clone() = 0;
    void class_skill();
    virtual ~Infantryman() {};
};

struct Archer: public Unit {
    Archer(int h, int d, int s);
    virtual void special_skill() = 0;
    virtual Unit* clone() = 0;
    void class_skill();
    virtual ~Archer() {};
};

struct Knight: public Unit {
    Knight(int h, int d, int s);
    virtual void special_skill() = 0;
    virtual Unit* clone() = 0;
    void class_skill();
    virtual ~Knight() {};
};

// Конкретные классы стандартных юнитов
struct StandartInfantryman: public Infantryman {
    StandartInfantryman();
    virtual Unit* clone();
    void special_skill();
    virtual ~StandartInfantryman(){};
};

struct StandartArcher: public Archer {
    StandartArcher();
    virtual Unit* clone();
    void special_skill();
    virtual ~StandartArcher(){};
};

struct StandartKnight: public Knight {
    StandartKnight();
    virtual Unit* clone();
    void special_skill();
    virtual ~StandartKnight(){};
};

// Конкретные классы уникальных юнитов
struct EnglandArcher: public Archer {
    EnglandArcher();
    virtual Unit* clone();
    void special_skill();
    virtual ~EnglandArcher(){};
};

struct FranceKnight: public Knight {
    FranceKnight();
    virtual Unit* clone();
    void special_skill();
    virtual ~FranceKnight(){};
};
