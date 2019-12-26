//
//  tree.cpp
//  WordTree
//
//  Created by Jasmine Peng on 8/20/18.
//  Copyright © 2018 Jasmine Peng. All rights reserved.
//

#include "tree.h"
#include <iostream>
#include <algorithm>

// default constructor
WordTree::WordTree() : root(nullptr) {}
// copy constructor
WordTree::WordTree(const WordTree& rhs)
{
    if (rhs.root == nullptr)
        root = nullptr;
    else
    {
        WordNode *q = root;
        WordNode *p = rhs.root;
        
        copyTree(q, p);
    }
}

void WordTree::copyTree(WordNode *&copy, WordNode *&ref)
{
    if (ref == nullptr)
        return;
    
    copyTree(copy->m_left, ref->m_left);
    
    copyTree(copy->m_right, ref->m_right);
    
    copy = new WordNode(ref->m_data, ref->m_counter);
}
// assignment operator
const WordTree& WordTree::operator=(const WordTree& rhs)
{
    if (this == &rhs)
        return *this;
    WordTree temp = rhs;
    swap(temp, *this);
    return *this;
    
}
// Inserts v into the WordTree
void WordTree::add(IType v)
{
    if (root == nullptr)
    {
        root = new WordNode(v, 1);
        return;
    }
    
    WordNode *cur = root;
    for(;;)
    {
        if (v == cur->m_data)
        {
            cur->m_counter = cur->m_counter + 1;
            return;
        }
        if (v < cur->m_data)
        {
            if(cur->m_left != nullptr)
                cur = cur->m_left;
            else
            {
                cur->m_left = new WordNode(v, 1);
                return;
            }
        }
        else if (v > cur->m_data)
            
        {
            if (cur->m_right != nullptr)
                cur = cur->m_right;
            else
            {
                cur->m_right = new WordNode(v, 1); 
                return;
            }
        }
    }
    
}


// Returns the number of distinct words / nodes
int WordTree::distinctWords() const
{
    int counter = 0;
    WordNode *p = root;
    int flag = 1;
    
    traverseTree(p, counter, flag);
    
    return counter;
}
// Returns the total number of words inserted, including
// duplicate values
int WordTree::totalWords() const
{
    int counter = 0;
    WordNode *p = root;
    int flag = 0;
    
    traverseTree(p, counter, flag);
    
    return counter;
}
// Prints the LinkedList
ostream& operator<<(ostream &out, const WordTree&
                           rhs)
{
    WordTree temp;
    WordNode *p = rhs.root;
    temp.printTree(out, p);
    
    return out; 
}

ostream& WordTree::printTree(ostream &out, WordNode *cur)
{
    if (cur != nullptr)
    {
        printTree(out, cur->m_left);
        
        out << cur->m_data << " " << cur->m_counter << endl;
        
        printTree(out, cur->m_right);
    }
    return out;
}
void WordTree::traverseTree(WordNode *cur, int &counter, int flag) const
{
    if (cur == nullptr)
        return;
    
    traverseTree(cur->m_left, counter, flag);
    
    traverseTree(cur->m_right, counter, flag);
    
    if (flag == 0)
    {
        counter = counter + cur->m_counter;
    }
    else if (flag == 1)
    {
        counter++;
    }
    
}

WordNode::~WordNode()
{
    delete m_left;
    delete m_right;
}

// Destroys all the dynamically allocated memory in the
// tree
WordTree::~WordTree()
{
    delete root;
    root = nullptr;
}
