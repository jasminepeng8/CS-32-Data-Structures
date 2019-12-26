//
//  linkedlist.cpp
//  LinkedList
//
//  Created by Jasmine Peng on 7/11/18.
//  Copyright © 2018 Jasmine Peng. All rights reserved.
//

#include "linkedlist.h"

// copy constructor
LinkedList :: LinkedList(const LinkedList& rhs)
{
    Node *p = nullptr;
    Node *n = nullptr;
    
    if (rhs.head == nullptr)
        head = nullptr;
    else
    {
        head = new Node;
        head->value = rhs.head->value;
        
        p = head;
        n = rhs.head->next;
    }
    
    while (n != nullptr)
    {
        p->next = new Node;
        p = p->next;
        p->value = n->value;
        
        n = n->next;
    }
    p->next = nullptr;
}

// Destroys all the dynamically allocated memory
// in the list.
LinkedList:: ~LinkedList()
{
    Node *p = head;
    while (p != nullptr)
    {
        Node *n = p->next;
        delete p;
        p = n;
    }
    head = nullptr;
}

// assignment operator
const LinkedList& LinkedList :: operator=(const LinkedList& rhs)
{
    Node *curr, *next;
    curr = head;
    next = nullptr;
    
    while (curr != nullptr)
    {
        next = curr->next;
        delete curr;
        curr = next;
    }
    
    Node *ptr = new Node;
    ptr = rhs.head;
    ptr->next = nullptr;
    
    Node *temp = rhs.head->next;
    
    while(temp != nullptr)
    {
        ptr->next = new Node;
        ptr->next = temp;
        ptr = ptr->next;
        ptr->next = nullptr;
        
        temp = rhs.head->next;
    }
    
    return *this;
}


    // Inserts val at the front of the list
    void LinkedList :: insertToFront(const ItemType &val)
    {
        Node *p;
        p = new Node;
        p->value = val;
        p->next = head;
        head = p;
    }

    // Prints the LinkedList
    void LinkedList :: printList() const
    {
        Node *p;
        p = head;
        while (p != nullptr)
        {
            cout << p->value << " ";
            p = p->next; 
        }
        cout << endl;
    }
    
    // Sets item to the value at position i in this
    // LinkedList and return true, returns false if
    // there is no element i
    bool LinkedList :: get(int i, ItemType& item) const
    {
        Node *p;
        p = head;
       
        int counter = 0;
        while (p != nullptr)
        {
            if (counter == i)
            {
                item = p->value;
                return true;
            }
            counter++;
            p = p->next;
        }
        return false;
    }
    
    // Reverses the LinkedList
    void LinkedList :: reverseList()
    {
        if(head == nullptr)
            return;
        Node *current = head;
        Node *prev = nullptr;
        Node *next = nullptr;
        while (current != nullptr)
        {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }
    
    // Prints the LinkedList in reverse order
    void LinkedList :: printReverse() const
    {
        if(head == nullptr)
            return;
        Node *current = head;
        Node *prev = nullptr;
        Node *next = nullptr;
        while (current != nullptr)
        {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        while (prev != nullptr)
        {
            cout << prev->value << " ";
            prev = prev->next;
        }
        cout << endl;
    }
    
    // Appends the values of other onto the end of this
    // LinkedList.
    void LinkedList :: append(const LinkedList &other)
    {
        Node *ptr;
        ptr = other.head;
        Node *store_vals = new Node;
        store_vals->value = ptr->value;
        
        Node *store_head = nullptr;
        store_head = store_vals;
        
        while (ptr->next != nullptr)
        {
            ptr = ptr->next;
            store_vals->next = new Node;
            store_vals = store_vals->next;
            store_vals->value = ptr->value;
        }
        
        Node *p;
        p = head;
        while (p->next != nullptr)
        {
            p = p->next;
        }
        p->next = store_head;
    }
    
    // Exchange the contents of this LinkedList with the other
    // one.
    void LinkedList :: swap(LinkedList &other)
    {
        Node *p;
        p = head;
        head = other.head;
        other.head = p;
        return;
    }
    
    // Returns the number of items in the Linked List.
    int LinkedList :: size() const
    {
        int counter = 0;
        Node *p;
        p = head;
        while (p != nullptr)
        {
            counter++;
            p = p->next;
        }
        return counter;
    }

