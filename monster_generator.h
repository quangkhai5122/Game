#pragma once
#include "monster_skeleton.h"
#include "monster_bat.h"
#include <vector>
class MonsterGenerate
{
public:
    MonsterGenerate();
    ~MonsterGenerate();
    void AddNewSke(int x, int y);
    void AddNewBatman(int x, int y);
    void Updated();
    void Rendered();
    std::vector<MonsterSke*> skeleton_list;
    std::vector<MonsterBat*> bat_list;

private:
    const int MAX_MONSTER = 15;
    int generate_intervals;
    const char* texture;

};
extern MonsterGenerate* monster_genera;