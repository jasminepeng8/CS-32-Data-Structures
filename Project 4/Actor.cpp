#include "Actor.h"
#include "GraphObject.h"
#include "GameWorld.h"
#include "GameConstants.h"
#include "StudentWorld.h"

#include <string>
#include <cstdlib>

///////////////////////////////////////////////////////////
///////////// OBJECT
///////////////////////////////////////////////////////////

Object::Object(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth, int sound, StudentWorld* sWorld) : GraphObject(imageID, startX, startY, dir, size, depth)
{
    m_alive = true;
    m_ID = imageID;
    m_sound = sound;
    m_sWorld = sWorld;
    setVisible(true);
}
Object::~Object()
{
    setVisible(false);
}
void Object::isAnnoyed()
{
    //
}
void Object::setDead()
{
    m_alive = false;
}
bool Object::isAlive() const
{
    return m_alive;
}
void Object::playSound()
{
    getWorld()->playSound(m_sound);
}
void Object::makeVisible()
{
    setVisible(true);
}
StudentWorld* Object::getWorld()
{
    return m_sWorld;
}

///////////////////////////////////////////////////////////
///////////// ACTOR
///////////////////////////////////////////////////////////

Actor::Actor(int imageID, int startX, int startY, Direction dir, int sound, int hitPoints, StudentWorld* sWorld) : Object(imageID, startX, startY, dir, 1.0, 0, sound, sWorld)
{
    m_hitP = hitPoints;
    setVisible(true);
}
Actor::~Actor()
{
    setVisible(false);
}
void Actor::dec_hitP(int value)
{
    m_hitP = m_hitP-value;
}
int Actor::get_hitP()
{
    return m_hitP;
}
void Actor::hitByBoulder()
{
    dec_hitP(100);
    setDead();
    playSound();
}

///////////////////////////////////////////////////////////
///////////// TUNNELMAN
///////////////////////////////////////////////////////////


Tunnelman::Tunnelman(StudentWorld* sWorld) : Actor (TID_PLAYER, 29, 60, right, SOUND_PLAYER_GIVE_UP, 10, sWorld)
{
    m_squirts = 5;
    m_sonar = 1;
    m_gold = 0;
}
Tunnelman::~Tunnelman()
{
    setVisible(false);
}
void Tunnelman::doSomething()
{
    if (isAlive() == false)
        return;
    
    int value;
    if(getWorld()->getKey(value) == true)
    {
        if (value == KEY_PRESS_SPACE)
        {
            if (m_squirts > 0)
            {
                m_squirts--;
                Direction d = getDirection();
                
                if (d == left)
                    getWorld()->addObject(new Squirt(getX()-4, getY(), d, getWorld()));
                else if (d == right)
                    getWorld()->addObject(new Squirt(getX()+4, getY(), d, getWorld()));
                else if (d == down)
                    getWorld()->addObject(new Squirt(getX(), getY()-4, d, getWorld()));
                else if (d == up)
                    getWorld()->addObject(new Squirt(getX(), getY()+4, d, getWorld()));
            }
            getWorld()->playSound(SOUND_PLAYER_SQUIRT);
        }
        else if (value == KEY_PRESS_ESCAPE)
        {
            setDead();
        }
        else if (value == KEY_PRESS_TAB)
        {
            if (m_gold > 0)
            {
                m_gold--;
                getWorld()->addObject(new Gold(getX(), getY(), true, false, getWorld()));
            }
        }
        else if (value == 'Z' || value == 'z')
        {
            if (m_sonar > 0)
            {
                m_sonar--;
                getWorld()->revealGoodies(getX(), getY(), 12);
                getWorld()->playSound(SOUND_SONAR);
            }
        }
        else if (value == KEY_PRESS_LEFT || value == KEY_PRESS_RIGHT || value == KEY_PRESS_UP || value == KEY_PRESS_DOWN)
        {
            moveOrChangeDirection(value);
        }
    }
    
    getWorld()->clearEarth(getX(), getY());
}

void Tunnelman::isAnnoyed()
{
    if (get_hitP() > 0)
        dec_hitP(2);
    else if (get_hitP() <= 0)
    {
        setDead();
        getWorld()->playSound(SOUND_PLAYER_ANNOYED);
    }
}

void Tunnelman::hitByBoulder()
{
    //
}

bool Tunnelman::canMove(int x, int y)
{
    if (x >= 0 && x < 60)
    {
        if (y >= 0 && y < 61)
        {
            if (getWorld()->isThereBoulder(x, y) == false)
                return true;
        }
    }
    return false;
}

bool Tunnelman::canMoveInDir(Direction d)
{
    if (d == left)
    {
        if (canMove(getX() - 1, getY()))
            return true;
    }
    else if (d == right)
    {
        if (canMove(getX() + 1, getY()))
            return true;
    }
    else if (d == up)
    {
        if (canMove(getX(), getY()+1))
            return true;
    }
    else if (d == down)
    {
        if (canMove(getX(), getY()-1))
            return true;
    }
    return false;
}

void Tunnelman::moveOrChangeDirection(int value)
{
    if (value == KEY_PRESS_LEFT)
    {
        if (canMoveInDir(left) == true)
        {
            if (getDirection() == left)
                moveTo(getX()-1, getY());
            else
                setDirection(left);
        }
    }
    else if (value == KEY_PRESS_RIGHT)
    {
        if (canMoveInDir(right) == true)
        {
            if (getDirection() == right)
                moveTo(getX()+1, getY());
            else
                setDirection(right);
        }
    }
    else if (value == KEY_PRESS_UP)
    {
        if (canMoveInDir(up) == true)
        {
            if (getDirection() == up)
                moveTo(getX(), getY()+1);
            else
                setDirection(up);
        }
    }
    else if (value == KEY_PRESS_DOWN)
    {
        if (canMoveInDir(down) == true)
        {
            if (getDirection() == down)
                moveTo(getX(), getY()-1);
            else
                setDirection(down);
        }
    }
}

int Tunnelman::getSquirts()
{
    return m_squirts;
}

int Tunnelman::getSonar()
{
    return m_sonar;
}

int Tunnelman::getGold()
{
    return m_gold;
}
void Tunnelman::addInventory(int ID)
{
    if (ID == TID_WATER_POOL)
        m_squirts+=5;
    if (ID == TID_SONAR)
        m_sonar++;
    if (ID == TID_GOLD)
        m_gold++;
}
///////////////////////////////////////////////////////////
///////////// EARTH
///////////////////////////////////////////////////////////

Earth::Earth(int startX, int startY, StudentWorld* sWorld) : Object (TID_EARTH, startX, startY, right, 0.25, 3, SOUND_NONE, sWorld)
{
    setVisible(true); 
}
Earth::~Earth()
{
    setVisible(false);
}
void Earth::doSomething()
{
    //
}

///////////////////////////////////////////////////////////
///////////// BOULDER
///////////////////////////////////////////////////////////

Boulder::Boulder(int startX, int startY, StudentWorld* sWorld) : Object (TID_BOULDER, startX, startY, down, 1.0, 1, SOUND_FALLING_ROCK, sWorld)
{
    m_ticks = 0;
    m_stable = true;
    m_falling = false;
    setVisible(true);
}
Boulder::~Boulder()
{
    setVisible(false);
}
void Boulder::doSomething()
{
    if (isAlive() == false)
        return;
   
    //check if the boulder is stable or is falling
    isStable();
    isFalling();
    
    if(m_stable == false)
        m_ticks++;
    
    if (m_ticks == 31)
        playSound();
    
    if(m_falling == true)
        moveTo(getX(), getY()-1);
    
    if(m_ticks > 30 && m_falling == false)
        setDead();
}
void Boulder::isStable()
{
    if(getWorld()->isThereEarthX(getX(), getY()-1) == false)
        m_stable = false;
}
void Boulder::isFalling()
{
    if (m_ticks > 30)
        m_falling = true;
    
    //stop falling
    if (getY() < 0)
        m_falling = false;
    else if(getWorld()->isThereEarthX(getX(), getY())-1)
        m_falling = false;
    else if(getWorld()->isThereBoulder(getX(), getY()))
        m_falling = false;
}
///////////////////////////////////////////////////////////
///////////// GOODIE
///////////////////////////////////////////////////////////
Goodie::Goodie(int imageID, int startX, int startY, int sound, StudentWorld* sWorld) : Object (imageID, startX, startY, right, 1.0, 2, sound, sWorld)
{
    //
}
Goodie::~Goodie()
{
    setVisible(false);
}
void Goodie::doSomething()
{
    //
}


///////////////////////////////////////////////////////////
///////////// BARREL
///////////////////////////////////////////////////////////
Barrel::Barrel(int startX, int startY, StudentWorld* sWorld) : Goodie (TID_BARREL, startX, startY, SOUND_FOUND_OIL, sWorld)
{
    setVisible(false);
}
Barrel::~Barrel()
{
    setVisible(false);
}
void Barrel::doSomething()
{
    if (isAlive() == false)
        return;

    if (getWorld()->isManNear(getX(), getY(), 4) == true)
        setVisible(true);
    
    if (getWorld()->isManNear(getX(), getY(), 3) == true)
    {
        setDead();
        playSound();
        getWorld()->increaseScore(1000);
    }
}

///////////////////////////////////////////////////////////
///////////// GOLD
///////////////////////////////////////////////////////////
Gold::Gold(int startX, int startY, bool temp, bool forMan, StudentWorld* sWorld) : Goodie (TID_GOLD, startX, startY, SOUND_GOT_GOODIE, sWorld)
{
    m_temp = temp;
    m_forMan = forMan;
    m_ticks = 0;
    // temporary = visible and permanent = not visible
//    if (temp == true)
//        setVisible(true);
//    else
//        setVisible(false);
    setVisible(false);
}
Gold::~Gold()
{
    setVisible(false);
}
void Gold::doSomething()
{
    if (isAlive() == false)
        return;
    
    if (m_forMan == true)
    {
        if (getWorld()->isManNear(getX(), getY(), 4) == true)
            setVisible(true);
        
        if (getWorld()->isManNear(getX(), getY(), 3) == true)
        {
            setDead();
            playSound();
            getWorld()->increaseScore(10);
            getWorld()->getMan()->addInventory(TID_GOLD);
        }
    }
    else if (m_forMan == false)
    {
        if (getWorld()->isProtesterNear(getX(), getY(), 3) == true)
        {
            setDead();
            getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
            Protester *p = dynamic_cast<Protester*>(getWorld()->getProtester(this, 3));
            p->addGold();
        }
    }
    
    if (m_temp == true)
    {
        //
        m_ticks++;
        if (m_ticks == 100)
            setDead();
    }
    
}

///////////////////////////////////////////////////////////
///////////// SONAR
///////////////////////////////////////////////////////////
Sonar::Sonar(int startX, int startY, int ticks, StudentWorld* sWorld) : Goodie (TID_SONAR, startX, startY, SOUND_GOT_GOODIE, sWorld)
{
    m_ticks = ticks;
    setVisible(true);
}
Sonar::~Sonar()
{
    setVisible(false);
}
void Sonar::doSomething()
{
    if (isAlive() == false)
        return;
    
    if (getWorld()->isManNear(getX(), getY(), 3) == true)
    {
        setDead();
        playSound();
        getWorld()->increaseScore(75);
        getWorld()->getMan()->addInventory(TID_SONAR);
    }
    
    m_ticks--;
    
    if(m_ticks == 0)
        setDead();
}

///////////////////////////////////////////////////////////
///////////// WATER
///////////////////////////////////////////////////////////
Water::Water(int startX, int startY, int ticks, StudentWorld* sWorld) : Goodie (TID_WATER_POOL, startX, startY, SOUND_GOT_GOODIE, sWorld)
{
    m_ticks = ticks;
    setVisible(true);
}
Water::~Water()
{
    setVisible(false);
}
void Water::doSomething()
{
    if (isAlive() == false)
        return;
    
    if (getWorld()->isManNear(getX(), getY(), 3) == true)
    {
        setDead();
        playSound();
        getWorld()->increaseScore(100);
        getWorld()->getMan()->addInventory(TID_WATER_POOL);
    }
    
    m_ticks--;
    
    if(m_ticks == 0)
        setDead();
}

///////////////////////////////////////////////////////////
///////////// PROTESTOR
///////////////////////////////////////////////////////////


Protester::Protester(int imageID, int sound, int hitPoints, StudentWorld* sWorld) : Actor (imageID, 60, 60, left, sound, hitPoints, sWorld)
{
    m_squaresToMove = 0;
    m_restTicks = 0;
    m_shoutTicks = 0;
    m_turnTicks = 0;
    m_leaveField = false;
    setVisible(true);
}

Protester::~Protester()
{
    setVisible(false);
}

bool Protester::lineOfSight()
{
    int xPro = getX(), yPro = getY();
    int xMan = getWorld()->getMan()->getX();
    int yMan = getWorld()->getMan()->getY();
    if (xPro == xMan)
    {
        if (yPro < yMan)
        {
            for (int i = yPro; i < yMan; i++)
            {
                if (getWorld()->isThereBoulder(xPro, i) == true)
                {
                    return false;
                }
                
            }
        }
        else if (yMan < yPro)
        {
            for (int i = yMan; i < yPro; i++)
            {
                if (getWorld()->isThereBoulder(xPro, i) == true)
                {
                    return false;
                }
                
            }
        }
        else
            return true;
    }
    if (yPro == yMan)
    {
        if (xPro < xMan)
        {
            for (int i = xPro; i < xMan; i++)
            {
                if (getWorld()->isThereBoulder(i, yPro) == true)
                {
                    return false;
                }
                
            }
        }
        else if (xMan < xPro)
        {
            for (int i = xMan; i < xPro; i++)
            {
                if (getWorld()->isThereBoulder(i, yPro) == true)
                {
                    return false;
                }
                
            }
        }
        else
            return true;
    }
    
    return false;
}

bool Protester::facingMan()
{
    Direction d = getDirection();
    
    int xPro = getX(), yPro = getY();
    int xMan = getWorld()->getMan()->getX();
    int yMan = getWorld()->getMan()->getY();
    
    if (d == left)
    {
        if (xMan < xPro)
            return true;
    }
    if (d == right)
    {
        if (xMan > xPro)
            return true;
    }
    if (d == up)
    {
        if (yMan > yPro)
            return true;
    }
    if (d == down)
    {
        if (yMan < yPro)
            return true;
    }
    return false;
}

void Protester::protestorMoveTo(int x, int y)
{
    if (getWorld()->isThereBoulder(x, y) == false)
    {
        if (getWorld()->isThereEarthGrid(x, y) == false)
            moveTo(x, y);
    }
}

bool Protester::canMove(int x, int y)
{
    if (x >= 0 && x < 60)
    {
        if (y >= 0 && y < 61)
        {
            if (getWorld()->isThereBoulder(x, y) == false)
            {
                if (getWorld()->isThereEarthGrid(x, y) == false)
                    return true;
            }
        }
    }
    return false;
}

bool Protester::canMoveInDir(Direction d)
{
    if (d == left)
    {
        if (canMove(getX()-1, getY()) && (getX()-1) >= 0)
            return true;
    }
    else if (d == right)
    {
        if (canMove(getX()+1, getY()) && (getX()+1) < 61)
            return true;
    }
    else if (d == up)
    {
        if (canMove(getX(), getY()+1) && (getY()+1) < 60)
            return true;
    }
    else if (d == down)
    {
        if (canMove(getX(), getY()-1) && (getY()-1) >= 0)
            return true;
    }
    return false;
}

void Protester::moveInDir(Direction d)
{
    if (d == left)
    {
        protestorMoveTo(getX() - 1, getY());
    }
    if (d == right)
    {
        protestorMoveTo(getX() + 1, getY());
    }
    if (d == up)
    {
        protestorMoveTo(getX(), getY() + 1);
    }
    if (d == down)
    {
        protestorMoveTo(getX(), getY() - 1);
    }
}

bool Protester::atIntersection(Direction d)
{
    if (d == left || d == right)
    {
        if (canMoveInDir(up))
        {
            moveInDir(up);
            return true;
        }
        else if (canMoveInDir(down))
        {
            moveInDir(down);
            return true;
        }
    }
    else if (d == up || d == down)
    {
        if (canMoveInDir(left))
        {
            moveInDir(left);
            return true;
        }
        else if (canMoveInDir(right))
        {
            moveInDir(right);
            return true;
        }
    }
    return false;
}

void Protester::setRandomSquares()
{
    m_squaresToMove = rand() % 60 + 8;
}
void Protester::setSquaresToMove(int num)
{
    m_squaresToMove = num;
}
void Protester::setRestTicks(int num)
{
    m_restTicks = num;
}
void Protester::setShoutTicks(int num)
{
    m_shoutTicks = num;
}
void Protester::setTurnTicks(int num)
{
    m_turnTicks = num;
}
void Protester::setLeave()
{
    m_leaveField = true;
}

int Protester::getSquaresToMove()
{
    return m_squaresToMove;
}
int Protester::getRestTicks()
{
    return m_restTicks;
}
int Protester::getShoutTicks()
{
    return m_shoutTicks;
}
int Protester::getTurnTicks()
{
    return m_turnTicks;
}
bool Protester::getLeave()
{
    return m_leaveField;
}


GraphObject::Direction Protester::newDirection()
{
    int d = rand() * 4;
    switch (d)
    {
        case 0:
            return left;
            break;
        case 1:
            return right;
            break;
        case 2:
            return up;
            break;
        case 3:
            return down;
            break;
        default:
            return left;
    }
}

///////////////////////////////////////////////////////////
///////////// REGPROTESTER
///////////////////////////////////////////////////////////
RegProtester::RegProtester(StudentWorld* sWorld) : Protester(TID_PROTESTER, SOUND_PROTESTER_GIVE_UP, 5, sWorld)
{
    setVisible(true);
}
RegProtester::~RegProtester()
{
    setVisible(false);
}

void RegProtester::doSomething()
{
    if (isAlive() == false)
        return;
    if (getRestTicks() > 0)
    {
        setRestTicks(getRestTicks()-1);
        return;
    }
    // non-resting tick
    else if (getRestTicks() == 0)
    {
        int val = 3 - getWorld()->getLevel() / 4;
        int newTicks = max(0, val);
        setRestTicks(newTicks);
        setShoutTicks(getShoutTicks() + 1);
        setTurnTicks(getTurnTicks() + 1);
    }
    
    
    if (getLeave() == true)
    {
        if (getX() == 60 && getY() == 60)
            setDead();
        else
        {
            //maze searching algorithm
        }
        
    }
    
    
    if (getWorld()->isManNear(getX(), getY(), 4) == true && facingMan() == true && getShoutTicks() > 50)
    {
        getWorld()->playSound(SOUND_PROTESTER_YELL);
        getWorld()->annoyMan();
        setShoutTicks(0);
        return;
    }
    else if (lineOfSight() == true && getWorld()->isManNear(getX(), getY(), 4) != true)
    {
        int xPro = getX(), yPro = getY();
        int xMan = getWorld()->getMan()->getX();
        int yMan = getWorld()->getMan()->getY();
        
        if (xPro == xMan)
        {
            if (xPro < xMan)
            {
                setDirection(right);
                protestorMoveTo(getX()+1, getY());
            }
            if (xPro > xMan)
            {
                setDirection(left);
                protestorMoveTo(getX()-1, getY());
            }
        }
        else if (yPro == yMan)
        {
            if (yPro < yMan)
            {
                setDirection(up);
                protestorMoveTo(getX(), getY()+1);
            }
            if (yPro > yMan)
            {
                setDirection(down);
                protestorMoveTo(getX(), getY()-1);
            }
        }
        
        setSquaresToMove(0);
        return;
    }
    else if (atIntersection(getDirection()) == true && getTurnTicks() > 200)
    {
        setTurnTicks(0);
        setRandomSquares();
        atIntersection(getDirection()); //moves in selected direction
        setSquaresToMove(getSquaresToMove() - 1);
    }
 

    if (getSquaresToMove() == 0)
    {
        Direction d = newDirection();
        while(canMoveInDir(d) == false)
        {
            d = newDirection();
        }
        
        setRandomSquares();
        
        moveInDir(d);
    }
    
    if (canMoveInDir(getDirection()))
    {
        setSquaresToMove(getSquaresToMove() - 1);
        moveInDir(getDirection());
    }
    else
    {
        setSquaresToMove(0);
        Direction d = newDirection();
        while(canMoveInDir(d) == false)
        {
            d = newDirection();
        }
        return;
    }
}

void RegProtester::isAnnoyed()
{
    if (getLeave() == true)
        return;
    
    //specifically from squirts
    if (get_hitP() > 0)
    {
        dec_hitP(2);
        getWorld()->playSound(SOUND_PROTESTER_ANNOYED);
        int val = 100 - getWorld()->getLevel() * 10;
        int newTicks = max(50, val);
        setRestTicks(newTicks);
    }
    else if (get_hitP() <= 0)
    {
        setLeave();
        getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
        setRestTicks(0);
        getWorld()->increaseScore(100);
    }
}

void RegProtester::addGold()
{
    getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
    getWorld()->increaseScore(25);
    setLeave();
}

///////////////////////////////////////////////////////////
///////////// HARDCOREPROTESTER
///////////////////////////////////////////////////////////
HardCoreProtester::HardCoreProtester(StudentWorld* sWorld) : Protester(TID_HARD_CORE_PROTESTER, SOUND_PROTESTER_GIVE_UP, 20, sWorld)
{
    setVisible(true);
}
HardCoreProtester::~HardCoreProtester()
{
    setVisible(false);
}

void HardCoreProtester::doSomething()
{
    if (isAlive() == false)
        return;
    if (getRestTicks() > 0)
    {
        setRestTicks(getRestTicks()-1);
        return;
    }
    // non-resting tick
    else if (getRestTicks() == 0)
    {
        int val = 3 - getWorld()->getLevel() / 4;
        int newTicks = max(0, val);
        setRestTicks(newTicks);
        setShoutTicks(getShoutTicks() + 1);
        setTurnTicks(getTurnTicks() + 1);
    }
    
    
    if (getLeave() == true)
    {
        if (getX() == 60 && getY() == 60)
            setDead();
        else
        {
            //maze searching algorithm
        }
        
    }
    
    
    if (getWorld()->isManNear(getX(), getY(), 4) == true && facingMan() == true && getShoutTicks() > 50)
    {
        getWorld()->playSound(SOUND_PROTESTER_YELL);
        getWorld()->annoyMan();
        setShoutTicks(0);
        return;
    }
    else if (lineOfSight() == true && getWorld()->isManNear(getX(), getY(), 4) != true)
    {
        int xPro = getX(), yPro = getY();
        int xMan = getWorld()->getMan()->getX();
        int yMan = getWorld()->getMan()->getY();
        
        if (xPro == xMan)
        {
            if (xPro < xMan)
            {
                setDirection(right);
                protestorMoveTo(getX()+1, getY());
            }
            if (xPro > xMan)
            {
                setDirection(left);
                protestorMoveTo(getX()-1, getY());
            }
        }
        else if (yPro == yMan)
        {
            if (yPro < yMan)
            {
                setDirection(up);
                protestorMoveTo(getX(), getY()+1);
            }
            if (yPro > yMan)
            {
                setDirection(down);
                protestorMoveTo(getX(), getY()-1);
            }
        }
        
        setSquaresToMove(0);
        return;
    }
    else if (atIntersection(getDirection()) == true && getTurnTicks() > 200)
    {
        setTurnTicks(0);
        setRandomSquares();
        atIntersection(getDirection()); //moves in selected direction
        setSquaresToMove(getSquaresToMove() - 1);
    }
    else
    {
        setSquaresToMove(getSquaresToMove() - 1);
        if (getSquaresToMove() == 0)
        {
            Direction d = newDirection();
            while(canMoveInDir(d) == false)
            {
                d = newDirection();
            }
            
            setRandomSquares();
            
            moveInDir(d);
        }
        
        if (canMoveInDir(getDirection()))
            moveInDir(getDirection());
        else
        {
            setSquaresToMove(0);
            return;
        }
        
    }
}

void HardCoreProtester::isAnnoyed()
{
    if (getLeave() == true)
        return;
    
    //specifically from squirts
    if (get_hitP() > 0)
    {
        dec_hitP(2);
        getWorld()->playSound(SOUND_PROTESTER_ANNOYED);
        int val = 100 - getWorld()->getLevel() * 10;
        int newTicks = max(50, val);
        setRestTicks(newTicks);
    }
    else if (get_hitP() <= 0)
    {
        setLeave();
        getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
        setRestTicks(0);
        getWorld()->increaseScore(250);
    }
}

void HardCoreProtester::addGold()
{
    getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
    getWorld()->increaseScore(50);
    int val = 100 - getWorld()->getLevel() * 10;
    int newTicks = max(50, val);
    setRestTicks(newTicks);
}

///////////////////////////////////////////////////////////
///////////// SQUIRT
///////////////////////////////////////////////////////////

Squirt::Squirt(int startX, int startY, Direction dir, StudentWorld* sWorld)
:Object(TID_WATER_SPURT, startX, startY, dir, 1.0, 1, SOUND_PLAYER_SQUIRT, sWorld)
{
    m_travelDistance = 4;
}

Squirt::~Squirt()
{
    setVisible(false);
}

void Squirt::doSomething()
{
    if (getWorld()->annoyProtester(this, 3) > 0)
        setDead();
    if (m_travelDistance <= 0)
        setDead();
    else
    {
        m_travelDistance--;
        Direction d = getDirection();

        if(canMoveInDir(d) == true)
        {
            moveInDir(d);
            return;
        }
        else
            setDead();
    }
}
bool Squirt::canMove(int x, int y)
{
    if (getWorld()->isThereBoulder(x, y) == false)
    {
        if (getWorld()->isThereEarthGrid(x, y) == false)
            return true;
    }
    return false;
}

bool Squirt::canMoveInDir(Direction d)
{
    if (d == left)
    {
        if (canMove(getX() - 1, getY()))
            return true;
    }
    else if (d == right)
    {
        if (canMove(getX() + 1, getY()))
            return true;
    }
    else if (d == up)
    {
        if (canMove(getX(), getY()+1))
            return true;
    }
    else if (d == down)
    {
        if (canMove(getX(), getY()-1))
            return true;
    }
    return false;
}

void Squirt::moveInDir(Direction d)
{
    if (d == left)
    {
        moveTo(getX() - 1, getY());
    }
    if (d == right)
    {
        moveTo(getX() + 1, getY());
    }
    if (d == up)
    {
        moveTo(getX(), getY() + 1);
    }
    if (d == down)
    {
        moveTo(getX(), getY() - 1);
    }
}




