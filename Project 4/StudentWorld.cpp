#include "StudentWorld.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <math.h>
#include <vector>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

StudentWorld::StudentWorld(std::string assetDir)
: GameWorld(assetDir)
{
    m_man = nullptr;
    m_ticks = 0;
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    m_man = new Tunnelman(this);
    
    //creating the oil field
    for (int r = 0; r < 60; r++)
    {
        for (int c = 0; c < 60; c++)
        {
            m_earth[r][c] = new Earth(c, r, this);
        }
    }
    
    
    //creating the tunnel in the center of the oil field
    for (int r = 3; r < 60; r++)
    {
        for (int c = 29; c < 33; c++)
        {
            delete m_earth[r][c];
            m_earth[r][c] = nullptr;
        }
    }
    
    int x, y, val;
    
    //adding boulders
    val = getLevel() / 2 + 2;
    int B = min(val, 9);
    
    for (int i = 0; i < B; i++)
    {
        srand(time(NULL));
        x = rand() % 60;
        y = rand() % 37 + 20;
        
        //no boulders in the tunnel
        while(x > 24 && x < 33 && y > 0)
            x = rand() % 56;
        
        //check for objects within a radius of 6 squares
        while(isObjNear(x, y, 6) == true)
        {
            x = rand() % 56;
            y = rand() % 37 + 20;
            
            while(x > 24 && x < 33 && y > 0)
                x = rand() % 56;
        }
        Object* objB = new Boulder(x, y, this);
        m_obj.push_back(objB);
        
        clearEarth(x, y);
    }
    
    //adding barrels of oil
    val = 2 + getLevel();
    int L = min(val, 21);
    
    for (int i = 0; i < L; i++)
    {
        srand(time(NULL));
        x = rand() % 56;
        y = rand() % 57;
        
        //no barrels in the tunnel
        while(x > 24 && x < 33 && y > 0)
            x = rand() % 56;
        
        //check for objects within a radius of 6 squares
        while(isObjNear(x, y, 6) == true)
        {
            x = rand() % 56;
            y = rand() % 37 + 20;
            
            while(x > 24 && x < 33 && y > 0)
                x = rand() % 56;
        }
        Object* objB = new Barrel(x, y, this);
        m_obj.push_back(objB);
    }
    
    //adding gold nuggets
    val = 5 - getLevel() / 2;
    int G = min(val, 2);
    
    for (int i = 0; i < G; i++)
    {
        srand(time(NULL));
        x = rand() % 56;
        y = rand() % 57;
        
        while(x > 24 && x < 33 && y > 0)
            x = rand() % 56;
        
        //check for objects within a radius of 6 squares
        while(isObjNear(x, y, 6) == true)
        {
            x = rand() % 56;
            y = rand() % 37 + 20;
            
            while(x > 24 && x < 33 && y > 0)
                x = rand() % 56;
        }
        Object* objG = new Gold(x, y, false, true, this);
        m_obj.push_back(objG);
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    setDisplayText();
    
    m_man->doSomething();
    
    if (m_man->isAlive())
    {
        m_man->doSomething();
    }
    else
    {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    
    objectDoSomething();
    
    if (getBarrelsLeft() == 0)
    {
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
    
    //adding new objects
    int xPos, yPos;
    int gProb = 1;
    int G = getLevel() * 25 + 300;
    if (rand() % G == gProb)
    {
        if (rand() % 5 == 1)
        {
            int val = 300 - 10 * getLevel();
            int T = max(100, val);
            Object *obj = new Sonar(0, 60, T, this);
            addObject(obj);
        }
        else
        {
            xPos = rand() % 56;
            yPos = rand() % 56;
            while (isThereEarthGrid(xPos, yPos) == true)
            {
                xPos = rand() % 56;
                yPos = rand() % 56;
            }
            int val = 300 - 10 * getLevel();
            int T = max(100, val);
            Object *obj = new Water(xPos, yPos, T, this);
            addObject(obj);
        }
    }
    
    int tVal = 200 - getLevel();
    int T = max(25, tVal);	//ticks between adding protesters
    
    int pVal = 2 + getLevel() * 1.5;
    int P = min(15, pVal);	//target number of protesters
    
    int probVal = getLevel() * 10 + 30;
    int probHardcore = min(90, probVal); //probability of hardcore protester
    
    int pNum = getProtestersLeft();	//number of protesters currently
    
    if (pNum < P && m_ticks > T)
    {
        //choose between hard core or regular
        if ((rand() % 100) < probHardcore)
        {
            addObject(new HardCoreProtester(this));
        }
        else
            addObject(new RegProtester(this));
        m_ticks = 0;
    }
    else
        m_ticks++;
    
    
    //getting rid of "dead" objects
    removeDead();
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for (int r = 0; r < 60; r++)
    {
        for (int c = 0; c < 64; c++)
        {
            if (m_earth[r][c] != nullptr)
                delete m_earth[r][c];
        }
    }
    
    vector<Object*>::iterator it;
    it = m_obj.begin();
    while (it != m_obj.end())
    {
        if ((*it) != nullptr)
        {
            delete *it;
            it = m_obj.erase(it);
        }
    }
    
    if (m_man != nullptr)
        delete m_man;
}


double StudentWorld::calcDistance(int x1, int y1, int x2, int y2)
{
    // d = sqrt(x^2+y^2)
    int lenX = x2 - x1;
    int lenY = y2 - y1;
    
    double d = sqrt((lenX*lenX)+(lenY*lenY));
    
    return d;
}

bool StudentWorld::isThereEarthGrid(int x, int y)
{
    for (int c = x; c < x+4; c++)
    {
        for (int r = y; r < y+4; r++)
        {
            if (m_earth[r][c] != nullptr)
                return true;
        }
    }
    return false;
}

bool StudentWorld::isThereEarthX(int x, int y)
{
    int countEarth = 0;
    for (int i = x; i < x+4; i++)
    {
        if (m_earth[i][y] == nullptr)
            countEarth++;
    }
    if (countEarth == 4)
        return false;
    else
        return true;
}

bool StudentWorld::isThereBoulder(int x, int y)
{
    vector<Object*>::iterator it;
    it = m_obj.begin();
    while (it != m_obj.end())
    {
        if( (*it)->getID() == TID_BOULDER )
        {
            int xObj = (*it)->getX();
            int yObj = (*it)->getY();
            if (xObj == x && yObj == y)
                return true;
            else
                return false;
        }
        it++;
    }
    return false;
}

bool StudentWorld::clearEarth(int x, int y)
{
    for (int c = x; c < x+4; c++)
    {
        for (int r = y; r < y+4; r++)
        {
            if (m_earth[r][c] != nullptr && r < 60 && c < 60)
            {
                playSound(SOUND_DIG);
                delete m_earth[r][c];
                m_earth[r][c] = nullptr;
            }
        }
    }
    return true; 
}

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

void StudentWorld::addObject(Object* obj)
{
    m_obj.push_back(obj);
}

void StudentWorld::revealGoodies(int x, int y, int rad)
{
    int xObj, yObj;
    vector<Object*>::iterator it;
    it = m_obj.begin();
    while (it != m_obj.end())
    {
        if ((*it)->getID() == TID_BARREL || (*it)->getID() == TID_GOLD)
        {
            xObj = (*it)->getX();
            yObj = (*it)->getY();
            if (calcDistance(x, y, xObj, yObj) <= rad)
                (*it)->makeVisible();
        }
        it++;
    }
}


void StudentWorld::objectDoSomething()
{
    vector<Object*>::iterator it;
    it = m_obj.begin();
    while (it != m_obj.end())
    {
        if((*it)->isAlive() && (*it) != nullptr)
            (*it)->doSomething();
        it++;
    }
}

void StudentWorld::removeDead()
{
    vector<Object*>::iterator it;
    it = m_obj.begin();
    while (it != m_obj.end())
    {
        if ((*it)->isAlive() == false && (*it) != nullptr)
        {
            delete *it;
            it = m_obj.erase(it);
        }
        else
            it++;
    }
}


bool StudentWorld::isObjNear(int x, int y, int rad)
{
    int xObj, yObj;
    vector<Object*>::iterator it;
    it = m_obj.begin();
    while (it != m_obj.end())
    {
        xObj = (*it)->getX();
        yObj = (*it)->getY();
        double d = calcDistance(x, y, xObj, yObj);
        
        if (d <= rad)
            return true;
        
        it++;
    }
    return false;
}

bool StudentWorld::isManNear(int x, int y, int rad)
{
    int xMan, yMan;
    
    xMan = m_man->getX();
    yMan = m_man->getY();
    
    double d = calcDistance(x, y, xMan, yMan);
    
    if (d <= rad)
        return true;
    
    return false;
}

bool StudentWorld::isProtesterNear(int x, int y, int rad)
{
    int xPro, yPro;
    
    vector<Object*>::iterator it;
    it = m_obj.begin();
    while (it != m_obj.end())
    {
        if( (*it)->getID() == TID_PROTESTER || (*it)->getID() == TID_HARD_CORE_PROTESTER )
        {
            xPro = (*it)->getX();
            yPro = (*it)->getY();
            
            double d = calcDistance(x, y, xPro, yPro);
            
            if (d <= rad)
                return true;
        }
        it++;
    }
    return false;
}

Object* StudentWorld::getProtester(Object *obj, int rad)
{
    int x = obj->getX();
    int y = obj->getY();
    int xPro, yPro;
    
    vector<Object*>::iterator it;
    it = m_obj.begin();
    while (it != m_obj.end())
    {
        if( (*it)->getID() == TID_PROTESTER || (*it)->getID() == TID_HARD_CORE_PROTESTER )
        {
            xPro = (*it)->getX();
            yPro = (*it)->getY();
            
            double d = calcDistance(x, y, xPro, yPro);
            
            if (d <= rad)
                return *it;
        }
        it++;
    }
    return nullptr;
}

Tunnelman* StudentWorld::getMan()
{
    return m_man;
}
void StudentWorld::annoyMan()
{
    m_man->isAnnoyed();
}

int StudentWorld::annoyProtester(Object *obj, int rad)
{
    int count = 0;
    
    int xObj = obj->getX();
    int yObj = obj->getY();
    
    vector<Object*>::iterator it;
    it = m_obj.begin();
    while (it != m_obj.end())
    {
        if((*it)->getID() == TID_PROTESTER || (*it)->getID() == TID_HARD_CORE_PROTESTER)
        {
            int xPro = (*it)->getX();
            int yPro = (*it)->getY();
            double d = calcDistance(xObj, yObj, xPro, yPro);
            if (d <= rad)
            {
                (*it)->isAnnoyed();
                count++;
            }
        }
        it++;
    }
    return count;
}
int StudentWorld::getProtestersLeft()
{
    int count = 0;
    vector<Object*>::iterator it;
    it = m_obj.begin();
    while (it != m_obj.end())
    {
        if ((*it)->getID() == TID_PROTESTER)
            count++;
        it++;
    }
    return count;
}
int StudentWorld::getBarrelsLeft()
{
    int count = 0;
    vector<Object*>::iterator it;
    it = m_obj.begin();
    while (it != m_obj.end())
    {
        if ((*it)->getID() == TID_BARREL)
            count++;
        it++;
    }
    return count;
}

void StudentWorld::setDisplayText()
{
    int level = getLevel(); 
    int lives = getLives();
    int health = m_man->get_hitP();
    int squirts = m_man->getSquirts();
    int gold = m_man->getGold();
    int barrelsLeft = getBarrelsLeft();
    int sonar = m_man->getSonar();
    int score = getScore();
    
    string gameStats = formatDisplay(level, lives, health, squirts, gold, barrelsLeft, sonar, score);
    
    setGameStatText(gameStats);
}

string StudentWorld::formatDisplay(int level, int lives, int health, int squirts, int gold, int barrelsLeft, int sonar, int score)
{
    ostringstream oss;
    
    oss <<  "Lvl: " << setw(2) << level << "  ";
    
    oss <<  "Lives: " << setw(1) << lives << "  ";
    
    oss <<  "Hlth: " << setw(3) << health*10 << "%" << "  ";
    
    oss <<  "Wtr: " << setw(2) << squirts << "  ";
    
    oss <<  "Gld: " << setw(2) << gold << "  ";
    
    oss << "Oil Left: " << setw(2) << barrelsLeft << "  ";
    
    oss <<  "Sonar: " << setw(2) << sonar << "  ";
    
    oss.fill('0');
    
    oss <<  "Scr: " << setw(6) << score << "  ";
    
    string gameStats = oss.str();
    
    return gameStats;
}
