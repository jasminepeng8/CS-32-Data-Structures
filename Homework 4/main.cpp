//
//  main.cpp
//  WordTree
//
//  Created by Jasmine Peng on 8/20/18.
//  Copyright © 2018 Jasmine Peng. All rights reserved.
//

#include <iostream>
#include <cassert>
#include "tree.h"

using namespace std; 

int main()
{
    WordTree k;
    k.add("Kim");
    k.add("Kanye");
    k.add("Kanye");
    k.add("Kanye");
    assert(k.distinctWords() == 2);
    assert(k.totalWords() == 4);
    cout << k; 
    
    WordTree w;
    w.add("Harry");
    w.add("Niall");
    w.add("Niall");
    w.add("Liam");
    w.add("Louis");
    w.add("Harry");
    w.add("Niall");
    w.add("Zayn");
    cout << w;
}
