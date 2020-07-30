//
//  character.hpp
//  helpful
//
//  Created by Nate Wood on 7/21/20.
//  Copyright © 2020 Nate Wood. All rights reserved.
//

#ifndef character_hpp
#define character_hpp

#include <stdio.h>
#include <string>

class game;

class character
{
public:
    character(game* game) : game_( game ){};
    void firstPick(std::string race, std::pair<int, int> stat) { race_ = race; firstPick_ = true; };
    void addStat(std::pair<int, int>);
    void stats();
    
private:
    int attack = 0;
    int defense = 0;
    int speed = 0;
    int speech = 0;
    int magic = 0;
    bool firstPick_ = false;
    //
    std::string race_;
    //swordsman, traveler, mage, paladin
    std::string class_;
    game* game_;
};

#endif /* character_hpp */
/*
 
Add test class that tests if a certain stat is higher than the  number given (requires something that keeps track of requirements like BranchReq class or something, or add something to Branch
Add more cases to addStat() when necessary but make sure that everything is labeled and kept track of
Make some Branches so that we can  test the game and make a game display for when playing in the shell for the time being
Of course finish initializer for game so testing is possible, maybe look into xml on xcode again to see whats possible
Think of races and what stats might be added to each one
Make a second pick function so that the class can be set and so necessary stats can be added
 
 */
