#pragma once
#include "unit.h"

// Абстрактная фабрика для производства воинов
struct UnitFactory {
    virtual Unit* CreateInfantryman();
    virtual Unit* CreateArcher();
    virtual Unit* CreateKnight();
    virtual ~UnitFactory();
};

// Фабрика для создания воинов Английской армии
struct EnglandUnitFactory: public UnitFactory {
    Unit* CreateArcher();
};

// Фабрика для создания воинов Французской армии
struct FranceUnitFactory: public UnitFactory {
    Unit* CreateKnight();
};

struct UnitCreator {
    UnitFactory* CreateUnitFactory(int fraction_id);
};
