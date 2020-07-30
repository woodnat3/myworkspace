//
//  character.cpp
//  helpful
//
//  Created by Nate Wood on 7/21/20.
//  Copyright © 2020 Nate Wood. All rights reserved.
//

#include <iostream>
#include "character.hpp"

using namespace std;

void character::addStat(pair<int, int> stat)
{
    switch(stat.first)
    {
        case 0:
            return;
        case 1:
            attack += stat.second;
        case 2:
            defense += stat.second;
        case 3:
            speed += stat.second;
        case 4:
            speech += stat.second;
        case 5:
            magic += stat.second;
        case 6:
            attack += stat.second;
            defense+= stat.second;
        case 7:
            attack += stat.second;
            magic += stat.second;
        case 8:
            speed += stat.second;
            speech += stat.second;
        case 9:
            defense += stat.second;
            magic  += stat.second;
        /* att+def att+spd att+mag spd+spe def+mag? ADD WHAT YOU SEE FIT LATER BASED ON THE STORY */
    }
}

void character::stats()
{
    cout << "----Stats----" << endl;
}
