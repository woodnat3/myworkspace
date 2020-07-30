//
//  Game.cpp
//  helpful
//
//  Created by Nate Wood on 7/21/20.
//  Copyright © 2020 Nate Wood. All rights reserved.
//

#include "game.hpp"
#include "tools.hpp"

using namespace std;

game::game()
{
    Vector<OptTree<pair<pair<string, string>, pair<int, int>>>::Branch<pair<pair<string, string>, pair<int, int>>>*> vec(4);
    vec.fill(nullptr, 4);
    pair<pair<string, string>, pair<int, int>> str;
    str.first.first = "";
    str.first.second =  "What race do you choose?: ";
    str.second.first =  0;
    str.second.second = 0;
    tree_ = new OptTree<pair<pair<string, string>, pair<int, int>>>(4, vec, str);
    
}
void game::choose(int pos)
{
    return;
}
