//
//  main.cpp
//  anagram
//
//  Created by Jasmine Peng on 7/28/18.
//  Copyright © 2018 Jasmine Peng. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in

int dictionaryReader(istream &dictfile, string dict[]);
int recurCombos(string word, const string dict[], int size, string results[]);
void recursiveDisp(const string results[], int size);

void permutate(string word, int i, int n, string permutations[], int &element, int dictSize, const string dict[], int counter);
void readLoop(int i, int max, istream &dictfile, string dict[], int &counter);
void permuteLoop(string word, int a, int max, int holder, string permutations[], int &element, int dictSize, const string dict[], int counter);
void traverseDict(string word, int i, int dictSize, const string dict[], string permutations[], int &element, int counter);
void displayLoop(const string results[], int i, int size);


//Places each string in dictfile into the array dict.
//Returns the number of words read into dict. This number should not
//be larger than MAXDICTWORDS since that is the size of the array.
int dictionaryReader(istream &dictfile, string dict[])
{
    int counter = 0;
    readLoop(0, MAXDICTWORDS, dictfile, dict, counter);
    
    return counter - 1;
}

//Places all the combinations of word, which are found in dict into
//results. Returns the number of matched words found. This number
//should not be larger than MAXRESULTS since that is the size of the array.
//The size is the number of words inside the dict array.

//word: our target word, array dict: contains all words read from file, size: number of words from file in dict, results: all of our matched words
int recurCombos(string word, const string dict[], int size, string results[])
{
    int wordLength = word.length();
    int element = 0;
    permutate(word, 0, wordLength-1, results, element, size, dict, 0);
    
    if (element == 0)
        return 0;
    else
        return element + 1;
}
//Displays size number of strings from results. The results can be printed
//in any order.

//results array: contains all matched words, size: number of matched words
void recursiveDisp(const string results[], int size)
{
    displayLoop(results, 0, size);
}

//int i is 0, size: number of matched words, results array:
void displayLoop(const string results[], int i, int size)
{
    if(i >= size-1)
        return;
    
    cout << "Matching word " << results[i] << endl;
    
    displayLoop (results, i+1, size);
}


//int i = 0, int max is MAXDICTWORDS (20,000), dictfile: file reading from, array dict: where we are storing words read, counter: keeps track of how many words read
void readLoop(int i, int max, istream &dictfile, string dict[], int &counter)
{
    string word;
    if (i >= max)
        return;
    if(dictfile)
    {
        dictfile >> dict[i];
        
        counter += 1;
        
        readLoop(i + 1, max, dictfile, dict, counter);
    }
    else
        return;
}

void permuteLoop(string word, int a, int max, int holder, string permutations[], int &element, int dictSize, const string dict[], int counter)
{
    if (holder > max)
        return;
    swap(word[a], word[holder]);
    permutate(word, a+1, max, permutations, element, dictSize, dict, counter);
    swap(word[a], word[holder]);
    
    permuteLoop(word, a , max, holder+1, permutations, element, dictSize, dict, counter);
}


//word: the target word, int i: starting position 0, dictSize: number of words copied over from file, permutations: resulting output of matched permutations, element:
void traverseDict(string word, int i, int dictSize, const string dict[], string permutations[], int &element, int counter)
{
    if (i >= dictSize)
        return;
    
//    int mark = 0;
    if (dict[i] == word)
    {
//        if (counter < 20)
//        {
//            if (word == permutations[counter])
//                mark = 1;
//        }
//        if (element < 20 && mark == 0)
//        {
            permutations[element] = word;
            element++;
//        }
    }
    traverseDict(word, i + 1, dictSize, dict, permutations, element, counter + 1);
}

//word: our target word, int i: 0 to start loop, n: word length, element: keeps track of number of matched words, dictSize: number of words read from file, dict: contains all words read from file
void permutate(string word, int i, int n, string permutations[], int &element, int dictSize, const string dict[], int counter)
{
    if(i==n)
    {
        traverseDict(word, 0, dictSize, dict, permutations, element, counter);
    }
    else
    {
        permuteLoop (word, i, n, i, permutations, element, dictSize, dict, counter);
    }
}


int main()
{
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;
    
    dictfile.open("dictionary.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }
    
    nwords = dictionaryReader(dictfile, dict);
    cout << nwords << endl;
    
    
    cout << "Please enter a string for an anagram: ";
    cin >> word;
    
    int numMatches = recurCombos(word, dict, nwords, results);
    if (!numMatches)
        cout << "No matches found" << endl;
    else
        recursiveDisp(results, numMatches);
}

