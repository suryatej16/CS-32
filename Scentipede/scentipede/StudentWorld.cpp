#include "StudentWorld.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cctype>
#include <fstream>
#include <ctime>
#include <algorithm>


StudentWorld::StudentWorld()
{
    int m_counter = 0;
    m_waterDroplets;
    m_player;
    m_mushrooms;
}

StudentWorld::~StudentWorld() //come back to this at the very end
{
    return;
}


void StudentWorld::init()
{
    m_player = new PlayerShip(IID_PLAYER, this, 15, 0);
    
    int numMushrooms;
    if(testParamsProvided())
    {
        numMushrooms = getTestParam(TEST_PARAM_STARTING_MUSHROOMS);
    }
    else
        numMushrooms = 25; //default starting mushrooms
    for(int k = 0; k < numMushrooms; k++)
    {
        int x;
        int y;
        generateRandomCoordinates(x,y);
        m_mushrooms.push_back (new Mushroom(IID_MUSHROOM, this, x, y)); 
    }
}

int StudentWorld::move()
{
    m_counter++;
    
    if(m_player->isDead() == false)
    {
        m_player->doSomething();
    }
    
    
    for(int k = 0; k < m_waterDroplets.size(); k++)
    {
        if(m_waterDroplets.size() == 0)
        {
            break;
            
        }
        if(m_waterDroplets[k]->isDead() == false)
        {
            m_waterDroplets[k]->doSomething();
        }
    }
    
    removeDeadObjects();
    
    if(m_player->isDead() == true)
    {
        return GWSTATUS_PLAYER_DIED;
    }
    
    return GWSTATUS_CONTINUE_GAME; 
}

void StudentWorld::removeDeadObjects()
{
    
    for(int k = 0; k < m_mushrooms.size(); k++)
    {
        if(m_mushrooms.size() == 0)
        {
            break;
            
        }
        
        if(m_mushrooms[k] != NULL)
        {
            if(m_mushrooms[k]->isDead() == true)
            {
                delete m_mushrooms[k];
                
            }
        }
        
    }
    
    for(int k = 0; k < m_waterDroplets.size(); k++)
    {
        if(m_waterDroplets.size() == 0)
        {
            break;
            
        }
        
        if(m_waterDroplets[k] != NULL)
        {
            if(m_waterDroplets[k]->isDead() == true)
            {
                delete m_waterDroplets[k];
            }
            
        }
    }
}


void StudentWorld::cleanUp() 
{
    delete m_player;
    
    for(int k = 0; k < m_mushrooms.size(); k++)
    {
        if(m_mushrooms.size() == 0)
        {
            break;
            
        }
        if(m_mushrooms[k] != NULL)
        {
            delete m_mushrooms[k];
            
            
        }
        
    }
    
    for(int k = 0; k < m_waterDroplets.size(); k++)
    {
        if(m_waterDroplets.size() == 0)
        {
            break;
            
        }
        if(m_waterDroplets[k] != NULL)
        {
            delete m_waterDroplets[k];
            
            
        }
    }
    
}

int StudentWorld::numberofMushroomsat(int x, int y) const
{
    int count = 0;
    if(m_mushrooms.size() == 0)
    {
        return count;
    }
    for(int k = 0; k < m_mushrooms.size(); k++)
    {
        int x1, y1;
        m_mushrooms[k]->getLocation(x1, y1);
        if(x1 == x && y1 == y)
        {
            count++;
        }
    }
    return count;
}


void StudentWorld::generateRandomCoordinates(int& x, int& y) //important recursive function to implement
{
    int x1 = randInt(0, GARDEN_WIDTH-1);
    int y1 = randInt(1,18);
    if(numberofMushroomsat(x1, y1) > 0)
    {
        generateRandomCoordinates(x1, y1);
    }
    x = x1;
    y = y1;
    
}

int StudentWorld::randInt(int lowest, int highest) // make sure highest is always greater than lowest
{
    int k =  lowest + (std::rand() % (highest - lowest + 1));
    return k;
}


PlayerShip* StudentWorld::getMyPlayer()
{
    return m_player;
}


Mushroom* StudentWorld::getaMushroom(int x, int y)
{
    for(int k = 0; k < m_mushrooms.size(); k++)
    {
        int x1, y1;
        m_mushrooms[k]->getLocation(x1, y1);
        if(x1 == x && y1 == y)
        {
            return m_mushrooms[k];
        }
    }
    return NULL;
}



bool StudentWorld::isSpotOfPlayer(int x, int y)
{
    int x1, y1;
    m_player->getLocation(x1, y1);
    if(x1 == x && y1 == y)
    {
        return true;
    }
    return false;
}


bool StudentWorld::squareIsEmpty(int x, int y)
{
    int counter;
    
    for(int k = 0; k < m_mushrooms.size(); k++)
    {
        int x2, y2;
        m_mushrooms[k]->getLocation(x2, y2);
        if(x2 == x && y2 == y)
        {
            counter++;
        }
    }
    if(counter == 0)
    {
        return true;
    }
    return false;
}




void StudentWorld::addWaterDroplet(int x, int y)
{
    m_waterDroplets.push_back(new WaterDroplet(IID_WATER_DROPLET, this, x, y));
}
