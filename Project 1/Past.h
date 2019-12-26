//
//  Past.h
//  zion_solution
//
//  Created by Jasmine Peng on 6/28/18.
//  Copyright © 2018 Jasmine Peng. All rights reserved.
//

#ifndef Past_h
#define Past_h


#include "globals.h"

class Past
{
    public:
    Past(int nRows, int nCols);
    bool markIt(int r, int c);
    void printThePast() const;
    
    private:
    int     m_rows;
    int     m_cols;
    char grid[MAXROWS][MAXCOLS];
};

#endif /* Past_h */
