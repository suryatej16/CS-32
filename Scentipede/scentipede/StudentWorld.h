#ifndef _StudentWorld_H_
#define _StudentWorld_H_

// students - add your code here!

#include "actor.h" //this might not be necessary
#include <vector>

class StudentWorld: public GameWorld
{
public:
    StudentWorld();
    
    ~StudentWorld();
	
    virtual void init();
	
    virtual int move();
	
    virtual void cleanUp();
    
    int numberofMushroomsat(int x, int y) const;
    
    void generateRandomCoordinates(int& x, int& y);
    
    int randInt(int lowest, int highest);
    
    PlayerShip* getMyPlayer();
    
    Mushroom* getaMushroom(int x, int y);
    
    bool isSpotOfPlayer(int x, int y);
    
    bool squareIsEmpty(int x, int y);
    
    void addWaterDroplet(int x, int y);
    
    void removeDeadObjects();
    
private:
    
    std::vector<Mushroom*> m_mushrooms; //figure out how to differentiate between different objects
    
    PlayerShip* m_player;
    
    int m_counter;
    
    std::vector<WaterDroplet*> m_waterDroplets;
};

#endif // #ifndef _StudentWorld_H_
