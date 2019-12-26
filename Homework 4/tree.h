//
//  tree.hpp
//  WordTree
//
//  Created by Jasmine Peng on 8/20/18.
//  Copyright © 2018 Jasmine Peng. All rights reserved.
//

#ifndef tree_hpp
#define tree_hpp

#include <iostream>
#include <string>
using namespace std;
typedef string IType;
struct WordNode {
    IType m_data;
    int m_counter; 
    WordNode *m_left;
    WordNode *m_right;
    
    WordNode(IType data, int counter)
    {
        m_left = nullptr;
        m_right = nullptr; 
        m_data = data;
        m_counter = counter; 
    }
    ~WordNode();
    // You may add additional data members and member functions
    // in WordNode
};
class WordTree {
private:
    WordNode *root;
    void traverseTree(WordNode *cur, int &counter, int flag) const; // 0 = total words, 1 = distinct words
    void copyTree(WordNode *&copy, WordNode *&ref);
    ostream& printTree(ostream &out, WordNode *cur);
public:
    // default constructor
    WordTree();
    // copy constructor
    WordTree(const WordTree& rhs);
    // assignment operator
    const WordTree& operator=(const WordTree& rhs);
    // Inserts v into the WordTree
    void add(IType v);
    // Returns the number of distinct words / nodes
    int distinctWords() const;
    // Returns the total number of words inserted, including
    // duplicate values
    int totalWords() const;
    // Prints the LinkedList
    friend ostream& operator<<(ostream &out, const WordTree&
                               rhs);
    // Destroys all the dynamically allocated memory in the
    // tree
    ~WordTree();
};

#endif /* tree_hpp */
