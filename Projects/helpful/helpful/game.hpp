//
//  Game.hpp
//  helpful
//
//  Created by Nate Wood on 7/21/20.
//  Copyright © 2020 Nate Wood. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <string>
#include <utility>
#include "tools.hpp"
#include "character.hpp"

class game
{
public:
    game();
    void choose(int pos);
    
private:
    int numPicks = 0;
    LinkedList<OptTree<pair<pair<string, string>, pair<int, int>>>::Branch<pair<pair<string, string>, pair<int, int>>>> history_;
    OptTree<pair<pair<string, string>, pair<int, int>>>* tree_;
    character* player = nullptr;
    OptTree<pair<pair<string, string>, pair<int, int>>>::Branch<pair<pair<string, string>, pair<int, int>>>* current_;
};

#endif /* Game_hpp */
