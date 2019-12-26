//
//  main.cpp
//  CoachingStaff
//
//  Created by Jasmine Peng on 7/14/18.
//  Copyright © 2018 Jasmine Peng. All rights reserved.
//

#include "CoachingStaff.h"
#include <type_traits>
#include <iostream>
#include <cassert>
#include <string>

#define CHECKTYPE(f, t) { auto p = (t)(f); (void)p; }
static_assert(std::is_default_constructible<CoachingStaff>::value,"Map must be default-constructible.");
static_assert(std::is_copy_constructible<CoachingStaff>::value,"Map must be copy-constructible.");
void ThisFunctionWillNeverBeCalled()
{
    CHECKTYPE(&CoachingStaff::operator=, CoachingStaff&
              (CoachingStaff::*)(const CoachingStaff&));
    CHECKTYPE(&CoachingStaff::noCoaches, bool
              (CoachingStaff::*)() const);
    CHECKTYPE(&CoachingStaff::numberOfCoaches, int
              (CoachingStaff::*)() const);
    CHECKTYPE(&CoachingStaff::hireCoach, bool (CoachingStaff::*)
              (const std::string&, const std::string&, const IType&));
    CHECKTYPE(&CoachingStaff::renameCoach, bool
              (CoachingStaff::*)(const std::string&, const std::string&,
                                 const IType&));
    CHECKTYPE(&CoachingStaff::hireOrRename, bool
              (CoachingStaff::*)(const std::string&, const std::string&,
                                 const IType&));
    CHECKTYPE(&CoachingStaff::fireCoach, bool (CoachingStaff::*)
              (const std::string&, const std::string&));
    CHECKTYPE(&CoachingStaff::coachOnStaff, bool
              (CoachingStaff::*)(const std::string&, const std::string&)
              const);
    CHECKTYPE(&CoachingStaff::findCoach, bool (CoachingStaff::*)
              (const std::string&, const std::string&, IType&) const);
    CHECKTYPE(&CoachingStaff::whichCoach, bool (CoachingStaff::*)
              (int, const std::string&, const std::string&, IType&)
              const);
    CHECKTYPE(&CoachingStaff::changeStaff, void
              (CoachingStaff::*)(CoachingStaff&));
    CHECKTYPE(mergeStaffs,  bool (*)(const CoachingStaff&, const
                                     CoachingStaff&, CoachingStaff&));
    CHECKTYPE(searchStaff, void (*)(const std::string&,
                                    const std::string&, const CoachingStaff&, CoachingStaff&));
}
//
//int main() {
//    CoachingStaff o;
//    o.hireCoach ("Chip", "Kelly", 54); o.hireCoach ("Dana", "Bible", 64); o.hireCoach ("Jimmie", "Dougherty", 39); o.hireCoach ("DeShaun", "Foster", 38); o.hireCoach ("Derek", "Sage", 40); o.hireCoach ("Justin", "Frye", 34);
//    for (int n = 0; n < o.numberOfCoaches(); n++)
//    {
//        std::string first;
//        std::string last;
//        int val;
//        o.whichCoach (n, first, last, val);
//        std::cout << first << " " << last << " " << val << std::endl;
//    }
//
//    CoachingStaff fortyTimes;
//    fortyTimes.hireCoach("Jerry", "Azzinaro", 6.99);
//    assert(!fortyTimes.coachOnStaff ("",""));
//    fortyTimes.hireCoach("Vince", "Oghobaase", 5.19);
//    fortyTimes.hireCoach("", "", 4.00);
//    fortyTimes.hireCoach("Roy", "Manning", 4.7);
//    assert(fortyTimes.coachOnStaff ("", ""));
//    fortyTimes.fireCoach("Vince", "Oghobaase");
//    assert(fortyTimes.numberOfCoaches() == 3
//           && fortyTimes.coachOnStaff("Jerry", "Azzinaro")
//           && fortyTimes.coachOnStaff ("Roy", "Manning")
//           && fortyTimes.coachOnStaff ("", ""));
//    
//    std::cout << "All tests passed." << std::endl;
//    
//    return 0;
//}

//int main()
//{
//    CoachingStaff o;
//    assert(o.noCoaches());
//    assert(o.numberOfCoaches() == 0);
//    o.hireCoach("Jeremy", "Allen", 5);
//    assert(!o.noCoaches());
//    o.hireCoach("Adam", "Smith", 6);
//    o.hireCoach("John", "Boden", 2);
//    assert(o.numberOfCoaches() == 3);
//    o.hireCoach("Jake", "Paul", 6);
//    assert(!o.noCoaches());
//    o.renameCoach("Adam", "Smith", 4);
//    o.renameCoach("Jeremy", "Allen", 1);
//    o.renameCoach("John", "Boden", 2);
//    o.renameCoach("Jake", "Paul", 3);
////    CoachingStaff p;
////    p.changeStaff(o);
////    
////    p.dump();
//
//    std::cout << std::endl;
//    
//    assert(o.coachOnStaff("John", "Boden"));
//    o.fireCoach("John", "Boden");
//    o.dump();
//    
//    std::cout << std::endl;
//    
//    assert(o.coachOnStaff("John", "Boden") == false);
//    
//    IType valueOne;
//    assert(o.findCoach("Jeremy", "Allen", valueOne));
//    assert(valueOne == 1);
//    
//    std::string first, last;
//    IType valueTwo;
//    int number = 1;
//    o.whichCoach(number, first, last, valueTwo);
//    assert(first == "Jake" && last == "Paul" && valueTwo == 3);
//    
//    //testing the mergeStaffs function
//    CoachingStaff sourceOne;
//    CoachingStaff sourceTwo;
//    CoachingStaff merged;
//    
//    sourceOne.hireCoach("Joe", "Smith", 6);
//    sourceOne.hireCoach("John", "Doe", 7);
//    sourceOne.hireCoach("Brian", "Cole", 1);
//    sourceOne.hireCoach("Brandon", "Warren", 8);
//    
//    sourceTwo.hireCoach("Bradley", "Andersen", 2);
//    sourceTwo.hireCoach("Dave", "Alvarez", 3);
//    sourceTwo.hireCoach("John", "Doe", 7);
//    
//    assert(mergeStaffs(sourceOne, sourceTwo, merged) == true);
//    merged.dump();
//    
//    //tesing the searchStaff function
//    CoachingStaff source;
//    CoachingStaff result;
//    std::string string1, string2;
//    
//    source.hireCoach("Joe", "Smith", 6);
//    source.hireCoach("John", "Doe", 7);
//    source.hireCoach("Brian", "Cole", 1);
//    source.hireCoach("Brandon", "Warren", 8);
//    source.hireCoach("George", "Warren", 6);
//    source.hireCoach("John", "Cena", 7);
//    source.hireCoach("Dave", "Warren", 8);
//    
//    string1 = "John";
//    string2 = "Cena";
//    
//    searchStaff(string1, string2, source, result);
//    result.dump();
//    
//    
//    
//    std::cout << "All tests passed." << std::endl;
//
//}
