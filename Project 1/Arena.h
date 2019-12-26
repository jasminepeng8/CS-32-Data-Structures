//
//  Arena.h
//  zion_solution
//
//  Created by Jasmine Peng on 6/28/18.
//  Copyright © 2018 Jasmine Peng. All rights reserved.
//

#ifndef Arena_h
#define Arena_h

#include "Past.h"
#include "globals.h"
#include <string>

using namespace std; 

class Player;
class Robot;

class Arena
{
public:
    // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    Past& thePast();
    int     robotCount() const;
    int     nRobotsAt(int r, int c) const;
    void    display(string msg) const;
    
    // Mutators
    bool   addRobot(int r, int c);
    bool   addPlayer(int r, int c);
    void   damageRobotAt(int r, int c);
    bool   moveRobots();
    
private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Robot*  m_robots[MAXROBOTS];
    Past    m_past;
    int     m_nRobots;
};

#endif /* Arena_h */
