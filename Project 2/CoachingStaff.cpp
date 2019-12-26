//
//  CoachingStaff.cpp
//  CoachingStaff
//
//  Created by Jasmine Peng on 7/14/18.
//  Copyright © 2018 Jasmine Peng. All rights reserved.
//

#include "CoachingStaff.h" 
#include <iostream>

//default constructor
CoachingStaff :: CoachingStaff() : head(nullptr) {}

// copy constructor
CoachingStaff :: CoachingStaff(const CoachingStaff& rhs)
{
    Node *p = nullptr;
    Node *n = nullptr;
    
    if (rhs.head == nullptr)
        head = nullptr;
    else
    {
        head = new Node;
        
        head->value = rhs.head->value;
        head->firstName = rhs.head->lastName;
        head->lastName = rhs.head->lastName;
        
        p = head;
        n = rhs.head->next;
        
        while (n != nullptr)
        {
            p->next = new Node;
            
            p->next->value = n->value;
            p->next->firstName = n->lastName;
            p->next->lastName = n->lastName;
            p->next->next = nullptr;
            p->next->prev = p; 
            
            n = n->next;
            p = p->next;
        }
    }
}

// Destroys all the dynamically allocated memory
// in the list.
CoachingStaff :: ~CoachingStaff()
{
    if (head == nullptr);
    else if (head->next == nullptr)
        delete head;
    else
    {
        Node *temp = head->next;
        Node *remove = head;
        while (temp != nullptr)
        {
            delete remove;
            remove = temp;
            temp = temp->next;
        }
        delete remove;
    }
}

// assignment operator
const CoachingStaff& CoachingStaff::operator=(const CoachingStaff& rhs)
{
   if (this == &rhs)
       return *this;
    CoachingStaff temp = rhs;
    changeStaff(temp);
    return *this; 
}

bool CoachingStaff :: noCoaches() const
{
    Node *p;
    p = head;
    if (p == nullptr)
        return true;
    else
        return false;
}
int CoachingStaff :: numberOfCoaches() const
{
    Node *p;
    p = head;
    
    int counter = 0;
    
    while (p != nullptr)
    {
        p = p->next;
        counter++;
    }
    return counter;
}
bool CoachingStaff :: hireCoach(const std::string& firstName, const std::string& lastName, const IType& value)
{
    Node *p;
    p = head;
    
    if (p == nullptr)
    {
        Node *newCoach = new Node;
        newCoach->firstName = firstName;
        newCoach->lastName = lastName;
        newCoach->value = value;
        
        p = newCoach;
        p->next = nullptr;
        p->prev = nullptr;
        
        head = p;
        
        return true;
    }
    
    while (p != nullptr)
    {
        //last name and first name matches, coach already exists
        if (p->lastName == lastName && p->firstName == firstName)
        {
            return false;
        }
        else if (p->prev == nullptr && p->next == nullptr)
        {
            //coach doesn't exist, create new node
            Node *newCoach = new Node;
            newCoach->firstName = firstName;
            newCoach->lastName = lastName;
            newCoach->value = value;
            
            //compare last names
            if (p->lastName > newCoach->lastName)
            {
                p->prev = newCoach;
                newCoach->next = p;
                newCoach->prev = nullptr;
                p->next = nullptr;
                
                head = newCoach;
                return true;
                
            }
            else if (p->lastName < newCoach->lastName)
            {
                p->next = newCoach;
                newCoach->prev = p;
                newCoach->next = nullptr;
                p->prev = nullptr;
                return true;
            }
            //if last name matches, check first name
            else if (p->lastName == newCoach->lastName)
            {
                if (p->firstName > newCoach->firstName)
                {
                    p->prev = newCoach;
                    newCoach->next = p;
                    newCoach->prev = nullptr;
                    p->next = nullptr;
                    
                    head = newCoach; 
                    return true;
                }
                else if (p->firstName < newCoach->firstName)
                {
                    p->next = newCoach;
                    newCoach->prev = p;
                    newCoach->next = nullptr;
                    p->prev = nullptr;
                    return true;
                }
            }
            delete newCoach;
            newCoach = nullptr;
        }
        else if ((p->prev == nullptr) && (p->next != nullptr))
        {
            //coach doesn't exist, create new node
            Node *newCoach = new Node;
            newCoach->firstName = firstName;
            newCoach->lastName = lastName;
            newCoach->value = value;
            
            //compare last names
            if (p->lastName > newCoach->lastName)
            {
                p->prev = newCoach;
                newCoach->next = p;
                newCoach->prev = nullptr;
                
                head = newCoach;
                return true;
                
            }
            else if ((p->lastName < newCoach->lastName) && (p->next->lastName > newCoach->lastName))
            {
                newCoach->next = p->next;
                p->next->prev = newCoach;
                p->next = newCoach;
                newCoach->prev = p;
                return true;
            }
            //if last name matches, check first name
            else if (p->lastName == newCoach->lastName)
            {
                if (p->firstName > newCoach->firstName)
                {
                    p->prev = newCoach;
                    newCoach->next = p;
                    newCoach->prev = nullptr;
                    
                    head = newCoach; 
                    return true;
                }
                else if ((p->firstName < newCoach->firstName) && (p->next->firstName > newCoach->firstName))
                {
                    newCoach->next = p->next;
                    p->next->prev = newCoach;
                    p->next = newCoach;
                    newCoach->prev = p;
                    return true;
                }
            }
            delete newCoach;
            newCoach = nullptr;
        }
        else if ((p->next == nullptr) && (p->prev != nullptr))
        {
            //coach doesn't exist, create new node
            Node *newCoach = new Node;
            newCoach->firstName = firstName;
            newCoach->lastName = lastName;
            newCoach->value = value;
            
            //compare last names
            if ((p->lastName > newCoach->lastName) && (p->prev->lastName < newCoach->lastName))
            {
                newCoach->prev = p->prev;
                p->prev->next = newCoach;
                p->prev = newCoach;
                newCoach->next = p;
                return true;
                
            }
            else if (p->lastName < newCoach->lastName)
            {
                p->next = newCoach;
                newCoach->prev = p;
                newCoach->next = nullptr;
                return true;
            }
            //if last name matches, check first name
            else if (p->lastName == newCoach->lastName)
            {
                if ((p->firstName > newCoach->firstName) && (p->prev->firstName < newCoach->firstName))
                {
                    newCoach->prev = p->prev;
                    p->prev->next = newCoach;
                    p->prev = newCoach;
                    newCoach->next = p;
                    return true;
                }
                else if (p->firstName < newCoach->firstName)
                {
                    p->next = newCoach;
                    newCoach->prev = p;
                    newCoach->next = nullptr;
                    return true;
                }
            }
            delete newCoach;
            newCoach = nullptr;
        }
        else if ((p->next != nullptr) && (p->prev != nullptr))
        {
            //coach doesn't exist, create new node
            Node *newCoach = new Node;
            newCoach->firstName = firstName;
            newCoach->lastName = lastName;
            newCoach->value = value;
            
            //compare last names
            if ((p->lastName > newCoach->lastName) && (p->prev->lastName < newCoach->lastName))
            {
                newCoach->prev = p->prev;
                p->prev->next = newCoach;
                p->prev = newCoach;
                newCoach->next = p;
                return true;
                
            }
            else if ((p->lastName < newCoach->lastName) && (p->next->lastName > newCoach->lastName))
            {
                newCoach->next = p->next;
                p->next->prev = newCoach;
                p->next = newCoach;
                newCoach->prev = p;
                return true;
            }
            //if last name matches, check first name
            else if (p->lastName == newCoach->lastName)
            {
                if ((p->firstName > newCoach->firstName) && (p->prev->firstName < newCoach->firstName))
                {
                    newCoach->prev = p->prev;
                    p->prev->next = newCoach;
                    p->prev = newCoach;
                    newCoach->next = p;
                    return true;
                }
                else if ((p->firstName < newCoach->firstName) && (p->next->firstName > newCoach->firstName))
                {
                    newCoach->next = p->next;
                    p->next->prev = newCoach;
                    p->next = newCoach;
                    newCoach->prev = p;
                    return true;
                }
            }
            delete newCoach;
            newCoach = nullptr;
        }
        p = p->next;
        
    }
    
    return false;
    
}

bool CoachingStaff :: renameCoach(const std::string& firstName, const std::string& lastName, const IType& value)
{
    Node *p;
    p = head;
    if (p == nullptr)
        return false;
    
    int counter = 1;
    
    while (p != nullptr)
    {
        if (p->lastName == lastName && p->firstName == firstName)
        {
            p->value = value;
            counter = 0;
        }
        p = p->next;
    }
    
    if (counter == 0)
        return true;
    else
        return false;
}

bool CoachingStaff :: hireOrRename(const std::string& firstName, const std::string& lastName, const IType& value)
{
    if (hireCoach(firstName, lastName, value))
    {
        hireCoach(firstName, lastName, value);
        return true;
    }
    else
    {
        renameCoach(firstName, lastName, value);
        return true;
    }
}

bool CoachingStaff :: fireCoach(const std::string& firstName, const std::string& lastName)
{
    Node *p;
    p = head;
    if (p == nullptr)
        return false;
    
    while (p != nullptr)
    {
        if (p->lastName == lastName && p->firstName == firstName)
        {
            
            if (p->prev == nullptr && p->next == nullptr)
            {
                delete p;
                p = nullptr;
                return true;
            }
            else if (p->prev == nullptr)
            {
                p->next->prev = nullptr;
                delete p;
                return true;
            }
            else if(p->next == nullptr)
            {
                p->prev->next = nullptr;
                delete p;
                return true;
            }
            else
            {
                p->prev->next = p->next;
                p->next->prev = p->prev;
                delete p;
                p = nullptr;
                return true;
            }
        }
        p = p->next;
    }
    return false;
}
    
bool CoachingStaff :: coachOnStaff(const std::string& firstName, const std::string& lastName) const
{
    Node *p;
    p = head;
    
    if (p == nullptr)
        return false;
    
    int counter = 1;
    
    while (p != nullptr)
    {
        if (p->lastName == lastName && p->firstName == firstName)
        {
            counter = 0;
        }
        p = p->next;
    }
    
    if (counter == 0)
        return true;
    else
        return false;
}
bool CoachingStaff :: findCoach(const std::string& firstName, const std::string& lastName, IType& value) const
{
    Node *p;
    p = head;
    
    if (p == nullptr)
        return false;
    
    int counter = 1;
    
    while (p != nullptr)
    {
        if (p->lastName == lastName && p->firstName == firstName)
        {
            value = p->value;
            counter = 0;
        }
        p = p->next;
    }
    
    if (counter == 0)
        return true;
    else
        return false;
}
bool CoachingStaff :: whichCoach(int i, std::string& firstName, std::string& lastName, IType& value) const
{
    Node *p;
    p = head;
    
    if (p == nullptr)
        return false;
    
    int counter = 0;
    
    int marker = 1;
    
    while (p != nullptr)
    {
        if (counter == i)
        {
            firstName = p->firstName;
            lastName = p->lastName;
            value = p->value;
            marker = 0;
        }
        counter++;
        p = p->next;
    }
    
    if (marker == 0)
        return true;
    else
        return false;
}
void CoachingStaff :: changeStaff(CoachingStaff& other)
{
    Node* temp = other.head;
    other.head = head;
    head = temp;
    
    return;
}
void CoachingStaff :: dump() const
{
    Node *p;
    p = head;
    while (p != nullptr)
    {
        std::cerr << p->firstName << " " << p->lastName << " " << p->value << std::endl;
        p = p->next;
    }
    return;
}


//non member functions
bool mergeStaffs(const CoachingStaff & csOne,
                 const CoachingStaff & csTwo,
                 CoachingStaff & csMerged)
{
    int counter = 0;
    
    if (csMerged.noCoaches() == false)
    {
        int max = csMerged.numberOfCoaches();
        for (int i = 0; i < max; i++)
        {
            std::string firstName, lastName;
            IType value;
            csMerged.whichCoach(i, firstName, lastName, value);
            csMerged.fireCoach(firstName, lastName);
        }
    }
    
    int numberOne = csOne.numberOfCoaches();

    for (int i = 0; i < numberOne; i++)
    {
        std::string firstName, lastName;
        IType value;
        csOne.whichCoach(i, firstName, lastName, value);
        if (csMerged.coachOnStaff(firstName, lastName))
        {
            IType checkVal;
            csMerged.findCoach(firstName, lastName, checkVal);
            if (value != checkVal)
            {
                csMerged.fireCoach(firstName, lastName);
                counter = 1;
            }
            else if (value == checkVal)
            {
                counter = 0;
            }
        }
        else
            csMerged.hireCoach(firstName, lastName, value);
    }
    
    int numberTwo = csTwo.numberOfCoaches();
    
    for (int i = 0; i < numberTwo; i++)
    {
        std::string firstName, lastName;
        IType value;
        csTwo.whichCoach(i, firstName, lastName, value);
        
        if (csMerged.coachOnStaff(firstName, lastName))
        {
            IType checkVal;
            csMerged.findCoach(firstName, lastName, checkVal);
            if (value != checkVal)
            {
                csMerged.fireCoach(firstName, lastName);
                counter = 1;
            }
            else if (value == checkVal)
            {
                counter = 0;
            }
        }
        else
            csMerged.hireCoach(firstName, lastName, value);
    }
    
    if (counter == 0)
        return true;
    else
        return false;
}

void searchStaff (const std::string& fsearch,
                  const std::string& lsearch,
                  const CoachingStaff& csOne,
                  CoachingStaff& csResult)
{
    if (!(csResult.noCoaches()))
    {
        int max = csResult.numberOfCoaches();
        for (int i = 0; i < max; i++)
        {
            std::string firstName, lastName;
            IType value;
            csResult.whichCoach(i, firstName, lastName, value);
            csResult.fireCoach(firstName, lastName);
        }
    }
    int max = csOne.numberOfCoaches();
    for (int i = 0; i < max; i++)
    {
        std::string firstName, lastName;
        IType value;
        
        if (fsearch == "*" && lsearch == "*")
        {
            csOne.whichCoach(i, firstName, lastName, value);
            csResult.hireCoach(firstName, lastName, value);
        }
        if (fsearch == "*")
        {
            csOne.whichCoach(i, firstName, lastName, value);
            if (lsearch == lastName)
            {
                csResult.hireCoach(firstName, lastName, value);
            }
        }
        else if (lsearch == "*")
        {
            csOne.whichCoach(i, firstName, lastName, value);
            if (fsearch == firstName)
            {
                csResult.hireCoach(firstName, lastName, value);
            }
        }
        else
        {
            csOne.whichCoach(i, firstName, lastName, value);
            if (fsearch == firstName && lsearch == lastName)
            {
                csResult.hireCoach(firstName, lastName, value);
            }
        }
    }
    return;
}
