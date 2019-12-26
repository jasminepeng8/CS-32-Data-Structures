//
//  main.cpp
//  LinkedList
//
//  Created by Jasmine Peng on 7/11/18.
//  Copyright © 2018 Jasmine Peng. All rights reserved.
//

#include <iostream>
#include <string> 
#include "linkedlist.h"
#include <assert.h>
using namespace std; 

int main()
{
//    LinkedList e1;
//    e1.insertToFront("Sam");
//    e1.insertToFront("Carla");
//    e1.insertToFront("Cliff");
//    e1.insertToFront("Norm");
//    e1.reverseList();  // reverses the contents of e1
//    string s;
//    assert(e1.size() == 4  &&  e1.get(0, s)  &&  s == "Sam");
    
    LinkedList e1;
    e1.insertToFront("A");
    e1.insertToFront("B");
    e1.insertToFront("C");
    e1.insertToFront("D");
    LinkedList e2;
    e2.insertToFront("X");
    e2.insertToFront("Y");
    e2.insertToFront("Z");
    e1.swap(e2);  // exchange contents of e1 and e2
    string s;
    assert(e1.size() == 3  &&  e1.get(0, s)  &&  s == "Z");
    assert(e2.size() == 4  &&  e2.get(2, s)  &&  s == "B");
    
    LinkedList e3;
    assert(e3.get(9, s) == false);
    
//    LinkedList e1;
//    e1.insertToFront("bell");
//    e1.insertToFront("biv");
//    e1.insertToFront("devoe");
//    LinkedList e2;
//    e2.insertToFront("Andre");
//    e2.insertToFront("Big Boi");
//    e1.append(e2);  // adds contents of e2 to the end of e1
//    e1.printList();

}
