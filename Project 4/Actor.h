#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameWorld.h"

class StudentWorld;

class Object: public GraphObject
{
    public:
    Object(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth, int sound, StudentWorld* sWorld);
    virtual ~Object();
    
    virtual void doSomething() = 0;
    virtual void isAnnoyed();
    void setDead();
    bool isAlive() const;
    void playSound();
    void makeVisible();
    StudentWorld* getWorld();
    
    private:
    bool m_alive;
    int m_ID;
    int m_sound;
    StudentWorld* m_sWorld;
};

class Actor : public Object
{
    public:
    Actor(int imageID, int startX, int startY, Direction dir, int sound, int hitPoints, StudentWorld* sWorld);
    virtual ~Actor();
    
    virtual void doSomething() = 0;
    virtual void isAnnoyed() = 0;
    
    void dec_hitP(int value);
    int get_hitP();
    void hitByBoulder();
    
    private:
    int m_hitP;
};

class Tunnelman : public Actor
{
public:
    Tunnelman(StudentWorld* sWorld);
    virtual ~Tunnelman();
    virtual void doSomething();
    virtual void isAnnoyed();
    virtual void hitByBoulder();
    
    bool canMove(int x, int y);
    bool canMoveInDir(Direction d);
    
    void moveOrChangeDirection(int value);
    int getSquirts();
    int getSonar();
    int getGold();
    void addInventory(int ID);

private:
    int m_squirts;
    int m_sonar;
    int m_gold;
};


class Earth : public Object
{
public:
    Earth(int startX, int startY, StudentWorld* sWorld);
    virtual ~Earth();
    virtual void doSomething();
private:

};

class Boulder : public Object
{
public:
    Boulder(int startX, int startY, StudentWorld* sWorld);
    virtual ~Boulder();
    
    void isStable();
    void isFalling();
    
    virtual void doSomething();
private:
    int m_ticks;
    
    bool m_stable;
    bool m_falling;
};

class Goodie : public Object
{
public:
    Goodie(int imageID, int startX, int startY, int sound, StudentWorld* sWorld);
    virtual ~Goodie();
    
    virtual void doSomething() = 0;
    
private:
    
    
};

class Barrel : public Goodie
{
public:
    Barrel(int startX, int startY, StudentWorld* sWorld);
    virtual ~Barrel();
    virtual void doSomething();
private:
    
};

class Gold : public Goodie
{
public:
    Gold(int startX, int startY, bool temp, bool forMan, StudentWorld* sWorld);
    virtual ~Gold();
    virtual void doSomething();
private:
    bool m_temp; //temporary or permanent state
    bool m_forMan;
    int m_ticks;
};

class Sonar : public Goodie
{
public:
    Sonar(int startX, int startY, int tickLife, StudentWorld* sWorld);
    virtual ~Sonar();
    virtual void doSomething();
private:
    int m_ticks;
};

class Water : public Goodie
{
public:
    Water(int startX, int startY, int tickLife, StudentWorld* sWorld);
    virtual ~Water();
    virtual void doSomething();
private:
    int m_ticks;
};

class Protester : public Actor
{
public:
    Protester(int imageID, int sound, int hitPoints, StudentWorld* sWorld);
    virtual ~Protester();
    
    virtual void doSomething() = 0;
    virtual void isAnnoyed() = 0;
    virtual void addGold() = 0;
    
    bool lineOfSight();
    bool facingMan();
    void protestorMoveTo(int x, int y);
    bool canMove(int x, int y);
    bool canMoveInDir(Direction d);
    void moveInDir(Direction d);
    bool atIntersection(Direction d);
    
    void setRandomSquares();
    void setSquaresToMove(int num);
    void setRestTicks(int num);
    void setShoutTicks(int num);
    void setTurnTicks(int num);
    void setLeave();
    
    int getSquaresToMove();
    int getRestTicks();
    int getShoutTicks();
    int getTurnTicks();
    bool getLeave();
    
    Direction newDirection();
private:
    int m_squaresToMove;
    int m_restTicks;
    int m_shoutTicks;
    int m_turnTicks;
    bool m_leaveField;
};

class RegProtester : public Protester
{
public:
    RegProtester(StudentWorld* sWorld);
    virtual ~RegProtester();
    
    virtual void doSomething();
    virtual void isAnnoyed();
    virtual void addGold();
    
private:
    //
};

class HardCoreProtester : public Protester
{
public:
    HardCoreProtester(StudentWorld* world);
    virtual ~HardCoreProtester();
    
    virtual void doSomething();
    virtual void isAnnoyed();
    virtual void addGold();
private:
    //
};

class Squirt : public Object
{
public:
    Squirt(int x, int y, Direction dir, StudentWorld* world);
    virtual ~Squirt();
    virtual void doSomething();
    
    bool canMove(int x, int y);
    bool canMoveInDir(Direction d);
    void moveInDir(Direction d);
private:
    int m_travelDistance;
};



#endif // ACTOR_H_

