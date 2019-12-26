//
//  main.cpp
//  recursion
//
//  Created by Jasmine Peng on 7/25/18.
//  Copyright © 2018 Jasmine Peng. All rights reserved.
//
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

int mult(unsigned int m, unsigned int n);
int countDigit(int num, int digit);
string pairStars(string n);
string subBrackets(string str);
bool comboSum(const int a[], int size, int target);
//helper function
int sumHelper (const int a[], int size, int target, int total, int counter, int storeSize);
bool pathExists(std::string maze[], int nRows, int nCols,
                int sr, int sc, int er, int ec);

// Returns the product of two positive integers, m and n,
// using only repeated addition.
int mult(unsigned int m, unsigned int n)
{
    if (n == 1)
        return m;
    int total = mult(m, n-1);
    return total+=m;
}
// Returns the number of occurrences of digit in the decimal
// representation of num. digit is an int between 0 and 9
// inclusive.
//
// Pseudocode Example:
//    countDigit(18838, 8)  =>3
//    countDigit(55555, 3)  =>0
//    countDigit(0, 0)  => 0 or 1 (either if fine)
//
int countDigit(int num, int digit)
{
    if (num/10 == 0)
    {
        if (num%10 != digit)
            return 0;
        else
            return 1;
    }
    
    int total = countDigit (num/10, digit);
    if (num%10 == digit)
        total++;
    
    return total;
}
// Returns a string where the same characters next each other in
// string n are separated by "**"
//
// Pseudocode Example:
//    pairStars("goodbye") => "go**odbye"
//    pairStars("yyuu")    => "y**yu**u"
//    pairStars("aaaa")    => "a**a**a**a"

string pairStars(string n)
{
    if (n.length() == 1)
        return n;
        
    size_t pos = n.length()-1;
    
    string newString = n.substr(1, pos);
    string result = pairStars(newString);
    
    string firstElement = n.substr(0, 1);
    string nextElement = n.substr(1, 1);
    
    if (firstElement == nextElement)
        result = firstElement + "**" + result;
    else
        result = firstElement + result;
    
    return result;
}

// str contains a single pair of brackets, return a new string
// made of only the brackets and whatever those brackets contain
//
//  Pseudocode Example:
//     subBrackets("abc[ghj]789") => "[ghj]"
//     subBrackets("[x]7")        => "[x]"
//     subBrackets ("4agh[y]")    => "[y]"
//
string subBrackets(string str)
{
    if (str.length() == 0)
        return "";
    
    size_t pos = str.length()-1;
    
    string newString = str.substr(1, pos);
    string result = subBrackets(newString);
    
    string curr = str.substr(0, 1);
    
    if(curr == "[")
        result = curr + result;
    //string::npos = "until the end of the string", used to indicate no matches
    if (result.find("]") != string::npos)
    {
        if (result.find("[") == string::npos)
            result = curr + result;
    }
    if(curr == "]")
        result = result + curr;

    return result;
}
// Return true if the sum of any combination of elements in the
// array a equals the value of the target.
//
//  Pseudocode Example:
//     comboSum([2, 4, 8], 3, 10) => true
//     comboSum([2, 4, 8], 3, 12) => true
//     comboSum([2, 4, 8], 3, 11) => false
//     comboSum([], 0, 0)         => true
//

bool comboSum(const int a[], int size, int target)
{
    if (size == 0 && target == 0)
        return true;
    else if (size == 0)
        return false;
    
    int sum = sumHelper(a, size, target, 0, 0, size);
    
    if (sum == target)
        return true;
    else
        return comboSum(a+1, size-1, target);
}


//sumHelper is a helper function to comboSum
//adds up different combinations of numbers by going through the array list
//logic: starts from the beginning of the array and adds subsequent numbers,
//when the sum of these numbers equals target, return that sum.

//example array {2, 4, 6, 8, 10}
//how it checks:
// 2, 4, 6, 8, 10
// 2, 6, 8, 10
// 2, 8, 10
// 2, 10
//ability to skip numbers to check for every case
int sumHelper (const int a[], int size, int target, int total, int counter, int storeSize)
{
    //checks that we have gone through the entire array
    if (size == 0)
    {
        if (counter > storeSize - 2)
            return 0;
        //this portion is the same code as below except it allows for skipping numbers to check for every case
        if (total != target)
        {
            total = 0;
            
            //counter is increased, keeps track of how many numbers to skip during this run
            counter++;
            //reset the size
            size = storeSize;
            //reset the pointer to the first element
            const int *p = a-size;
            
            int start = *p;
            total = total + start;
            
            int sum = sumHelper(p+counter+1, size-counter, target, total, counter, storeSize);
            total = sum;

            return total;
        }
        else
            return total;
        
        return 0;
    }

    if (total != target)
    {
        //check for single number cases
        int start = a[0];
        if (target == start)
            return start;
        
        //add the single number to the running total if above condition not met
        total = total + start;
        //if the above sum does not satisfy target, keep calling function
        if (total != target)
        {
            int sum = sumHelper(a+1, size-1, target, total, counter, storeSize);
            total = sum;
        }
        return total;
    }
    else
        return total;
    
}

//psuedocode:
//If the start location is equal to the ending location, then
//we've solved the maze, so return true.
//Mark the start location as visted.
//For each of the four directions,
//If the location one step in that direction (from the
//                                            start location) is unvisited,
//then call pathExists starting from that location
//(and ending at the same ending location as in
// the current call).
//If that returned true,
//then return true.
//Return false.

// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
bool pathExists(std::string maze[], int nRows, int nCols,
                int sr, int sc, int er, int ec)
{
    bool result;
    
    maze[sr][sc] = '#';
    if (sr == er && sc == ec)
        return true;
    else
    {
        if(maze[sr-1][sc] == '.')
        {
            result = pathExists(maze, nRows, nCols, sr-1, sc, er, ec);
            if (result)
                return true;
        }
        if(maze[sr+1][sc] == '.')
        {
            result = pathExists(maze, nRows, nCols, sr+1, sc, er, ec);
            if (result)
                return true;
        }
        if(maze[sr][sc-1] == '.')
        {
            result = pathExists(maze, nRows, nCols, sr, sc-1, er, ec);
            if (result)
                return true;
        }
        if(maze[sr][sc+1] == '.')
        {
            result = pathExists(maze, nRows, nCols, sr, sc+1, er, ec);
            if (result)
                return true;
        }
        
        maze[sr][sc] = '.';
    }
    
    return false;
}

int main()
{
    int arr[] = {3, 6, 9};
    int size = 3;
    if (comboSum(arr, size, 15) == true)
        cout << "Correct!" << endl;
    else
        cout << "Wrong!" << endl;
    
    
    int arr1[] = {2, 4, 3};
    int size1 = 3;
    if (comboSum(arr1, size1, 5) == true)
        cout << "Correct!" << endl;
    else
        cout << "Wrong!" << endl;
    
    int arr2[] = {1, 2, 3};
    int size2 = 3;
    if (comboSum(arr2, size2, 3) == true)
        cout << "Correct!" << endl;
    else
        cout << "Wrong!" << endl;
    
    int arr3[] = {3, 6, 9};
    int size3 = 3;
    if (comboSum(arr3, size3, 6) == true)
        cout << "Correct!" << endl;
    else
        cout << "Wrong!" << endl;
    
    cout << "You should have four Correct! messages" << endl;
    
}
