//
//  Past.cpp
//  zion_solution
//
//  Created by Jasmine Peng on 6/28/18.
//  Copyright © 2018 Jasmine Peng. All rights reserved.
//

#include "Past.h"
#include "Arena.h"
#include "globals.h"

#include <iostream>
using namespace std;


Past::Past(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            grid[r][c] = '0';
}

char grid[MAXROWS][MAXCOLS];

bool Past::markIt(int r, int c)
{
    if(r > m_rows || c > m_cols)
    {
        return false;
    }
    else
    {
        grid[r-1][c-1]++;
        return true;
    }
}

void Past::printThePast() const
{
    // Position (row,col) in the arena coordinate system is represented in
    // the array element grid[row-1][col-1]
    int r, c;
    
    char gridChar[MAXROWS][MAXCOLS];
    
    // Fill the grid with dots
    for (r = 0; r < m_rows; r++)
        for (c = 0; c < m_cols; c++)
            gridChar[r][c] = '.';
    
    for (r = 0; r < m_rows; r++)
        for (c = 0; c < m_cols; c++)
        {
            switch(grid[r][c])
            {
                case '0': gridChar[r][c] = '.';
                    break;
                case '1': gridChar[r][c] = 'A';
                    break;
                case '2': gridChar[r][c] = 'B';
                    break;
                case '3': gridChar[r][c] = 'C';
                    break;
                case '4': gridChar[r][c] = 'D';
                    break;
                case '5': gridChar[r][c] = 'E';
                    break;
                case '6': gridChar[r][c] = 'F';
                    break;
                case '7': gridChar[r][c] = 'G';
                    break;
                case '8': gridChar[r][c] = 'H';
                    break;
                case '9': gridChar[r][c] = 'I';
                    break;
                case ':': gridChar[r][c] = 'J';
                    break;
                case ';': gridChar[r][c] = 'K';
                    break;
                case '<': gridChar[r][c] = 'L';
                    break;
                case '=': gridChar[r][c] = 'M';
                    break;
                case '>': gridChar[r][c] = 'N';
                    break;
                case '?': gridChar[r][c] = 'O';
                    break;
                case '@': gridChar[r][c] = 'P';
                    break;
                case 'A': gridChar[r][c] = 'Q';
                    break;
                case 'B': gridChar[r][c] = 'R';
                    break;
                case 'C': gridChar[r][c] = 'S';
                    break;
                case 'D': gridChar[r][c] = 'T';
                    break;
                case 'E': gridChar[r][c] = 'U';
                    break;
                case 'F': gridChar[r][c] = 'V';
                    break;
                case 'G': gridChar[r][c] = 'W';
                    break;
                case 'H': gridChar[r][c] = 'X';
                    break;
                case 'I': gridChar[r][c] = 'Y';
                    break;
                case 'J':
                default:
                    gridChar[r][c] = 'Z';
            }
        }
    // Draw the grid
    clearScreen();
    for (r = 0; r < m_rows; r++)
    {
        for (c = 0; c < m_cols; c++)
            cout << gridChar[r][c];
        cout << endl;
    }
    cout << endl;
}
