
#ifndef _ACTOR_H_

#define _ACTOR_H_

#include "GraphObj.h"
#include "GameConstants.h"
#include "GameWorld.h"
#include <string>

class StudentWorld;

class GameObject : public GraphObject //need destructors for all objects
{
public:
    GameObject(int imageID, StudentWorld* sw, int x, int y);
    virtual ~GameObject(){}
    StudentWorld* getmyWorld();
    virtual void doSomething() = 0;
    virtual void isAttacked();
    int getX() const;
    int getY() const;
    void updateXCoord(int newX);
    void updateYCoord(int newY);
    void setLives(int lives); 
    int livesRemaining();
    void DecreaseLives();
    void setDead(); 
    bool isDead();
    void setTick();
    int getTick();
    void addTick();
    
private:
    int m_ImageID;
    StudentWorld* m_world;
    bool m_dead;
    int m_x;
    int m_y;
    int m_lives;
    int m_tickCounter;
};


class PlayerShip : public GameObject
{
public:
    PlayerShip(int imageID, StudentWorld* sw, int x, int y);
    ~PlayerShip() {}
    virtual void doSomething ();
    bool move(int direction);
private:
    bool m_canFire;
    int count;
};

class Mushroom: public GameObject
{
public:
    Mushroom(int imageID, StudentWorld* sw, int x, int y);
    ~Mushroom() {}
    virtual void doSomething () {}
    virtual void isAttacked();
};

class PoisonMushroom : public Mushroom
{
public:
    PoisonMushroom(int imageID, StudentWorld* sw, int x, int y); 
    
};

class WaterDroplet: public PlayerShip
{
public:
    WaterDroplet(int imageID, StudentWorld* sw, int x, int y);  
    ~WaterDroplet() {}
    virtual void doSomething();
    
    
};



#endif // #ifndef _ACTOR_H_
