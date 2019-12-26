#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <vector>
#include <string>

using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(string assetDir);
    ~StudentWorld();
 
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    double calcDistance(int x1, int y1, int x2, int y2);
    bool isThereEarthGrid(int x, int y);
    bool isThereEarthX(int x, int y);
    bool isThereBoulder(int x, int y);
    bool clearEarth(int x, int y);
    
    bool pathExists();
    
    void addObject(Object *obj);
    void revealGoodies(int x, int y, int rad); //oil and gold
    void removeDead();
    void objectDoSomething();
    
    bool isObjNear(int x, int y, int rad);
    bool isManNear(int x, int y, int rad);
    bool isProtesterNear(int x, int y, int rad);
    
    Object* getProtester(Object* obj, int rad);
    Tunnelman* getMan();
    void annoyMan();
    int annoyProtester(Object *obj, int rad);
    
    int getProtestersLeft();
    int getBarrelsLeft();
    
    void setDisplayText();
    string formatDisplay(int level, int lives, int health, int squirts, int gold, int barrelsLeft, int sonar, int score);
    
private:
    Earth* m_earth[60][60];
    Tunnelman* m_man;
    vector <Object*> m_obj;
    
    int m_ticks; //to manage frequency at which protesters are added
};

#endif // STUDENTWORLD_H_
