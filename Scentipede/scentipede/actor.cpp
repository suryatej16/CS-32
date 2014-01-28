#include "actor.h"
#include "StudentWorld.h"
#include "GameController.h"


GameObject::GameObject(int imageID, StudentWorld* sw, int x, int y)
: GraphObject(imageID)
{
    m_world = sw;
    m_dead = false;
    m_ImageID = imageID;
    m_x = x;
    m_y = y;
    m_tickCounter = 0;
}


StudentWorld* GameObject::getmyWorld()
{
    return m_world;
}

int GameObject::getX() const
{
    return m_x;
}

int GameObject::getY() const
{
    return m_y;
}

void GameObject::updateXCoord(int newX)
{
    m_x = newX; 
}


void GameObject::updateYCoord(int newY)
{
    m_y = newY;
}

void GameObject::setLives(int lives)
{
    m_lives = lives;
}

int GameObject::livesRemaining()
{
    return m_lives;
}

void GameObject::DecreaseLives()
{
    m_lives--;
}


void GameObject::setDead()
{
    m_dead = true;
    displayMe(false);
}


bool GameObject::isDead()
{
    return m_dead;
}

void GameObject::isAttacked()
{
    setDead(); 
}

int GameObject::getTick()
{
    return m_tickCounter;
}

void GameObject::setTick()
{
    m_tickCounter = 0;
}

void GameObject::addTick()
{
    m_tickCounter++;
}


PlayerShip::PlayerShip(int imageID, StudentWorld* sw, int x, int y) //remember to pass in these arguments when constructing new players and mushrooms
: GameObject(imageID, sw, x, y)
{
    setInitialLocation(x, y);
    displayMe(true);
    m_canFire = true;
    count = 0;
    
}


void PlayerShip::doSomething()
{
    count++;
    if(count%4 == 0)
    {
        setDead();
    }
    StudentWorld* sw = getmyWorld();
    int ch;
    if(sw->getKey(ch))
    {
        switch (ch) 
        {
            case KEY_PRESS_LEFT_ARROW: // 1 is up, 2 is down, 3 is left, 4 is right; 5 is fire for now
                move(KEY_PRESS_LEFT_ARROW);
                break;
            case KEY_PRESS_RIGHT_ARROW:
                move(KEY_PRESS_RIGHT_ARROW);
                break;
            case KEY_PRESS_DOWN_ARROW:
                move(KEY_PRESS_DOWN_ARROW);
                break;
            case KEY_PRESS_UP_ARROW:
                move(KEY_PRESS_UP_ARROW);
                break;
            case KEY_PRESS_SPACE:
                move(KEY_PRESS_SPACE);
                break;
        }
    }
    
}

bool PlayerShip::move(int direction) //maybe consider changing this to void
{
    StudentWorld* sw = getmyWorld();
    int x;
    int y;
    getLocation(x, y);
    switch (direction)
    {
        case KEY_PRESS_UP_ARROW:
            m_canFire = true;
            if(y + 1 > 3 || sw->numberofMushroomsat(x, y+1) > 0)
            {
                break;
            }
            updateYCoord(y+1);
            moveTo(x, y+1);
            return true;
            break;   
        case KEY_PRESS_DOWN_ARROW:
            m_canFire = true;
            if(y - 1 < 0 || sw->numberofMushroomsat(x, y-1) > 0)
            {
                break;
            }
            updateYCoord(y-1);
            moveTo(x, y-1);
            return true;
            break;
        case KEY_PRESS_LEFT_ARROW:
            m_canFire = true;
            if(x-1 < 0 || sw->numberofMushroomsat(x-1, y) > 0)
            {
                break;
            }
            updateXCoord(x-1);
            moveTo(x-1, y);
            return true;
            break;
        case KEY_PRESS_RIGHT_ARROW:
            m_canFire = true;
            if(x+1 >= GARDEN_WIDTH || sw->numberofMushroomsat(x+1, y) > 0)
            {
                break;
            }
            updateXCoord(x+1);
            moveTo(x+1, y);
            return true;
            break;
        case KEY_PRESS_SPACE:
            if(m_canFire == true)
            {
                int dropletX = x;
                int dropletY = y+1;
                while(dropletX >= 0 && dropletX < GARDEN_WIDTH && dropletY >= 0 && dropletY < GARDEN_HEIGHT)
                {
                    if(sw->squareIsEmpty(dropletX, dropletY))
                    {
                        sw->addWaterDroplet(dropletX, dropletY);
                    }
                    if(sw->numberofMushroomsat(dropletX, dropletY) > 0)
                    {
                        Mushroom* mush = sw->getaMushroom(dropletX, dropletY);
                        if(mush != NULL)
                        {
                            mush->isAttacked();
                            return true;
                        }
                        break;
                    }
                    dropletY++; //not sure if this is correct
                }
            }
            break;
        default:
            m_canFire = true;
            return true;
            
    }
    
    return false;
}

Mushroom::Mushroom(int imageID, StudentWorld* sw, int x, int y)
: GameObject(imageID, sw, x, y)
{
    setInitialLocation(x, y);
    displayMe(true);
    setLives(4);
}

void Mushroom::isAttacked()
{
    DecreaseLives();
    StudentWorld* sw = getmyWorld();
    sw->increaseScore(1);
    if(livesRemaining() == 0)
    {
        setDead();
    }
    if(livesRemaining() == 3)
    {
        setBrightness(.75);
    }
    if(livesRemaining() == 2)
    {
        setBrightness(.5);
    }
    if(livesRemaining() == 1)
    {
        setBrightness(.25);
    }
}

PoisonMushroom::PoisonMushroom(int imageID, StudentWorld* sw, int x, int y) 
: Mushroom(imageID, sw, x, y)
{
    setInitialLocation(x, y);
    displayMe(true);
    setLives(4); 
    
}

WaterDroplet::WaterDroplet(int imageID, StudentWorld* sw, int x, int y)
: PlayerShip(imageID, sw, x, y)
{
    setInitialLocation(x, y);
    displayMe(true);
    setLives(2);
    
}

void WaterDroplet::doSomething()
{
    if(isDead() == true)
    {
        return;
    }
    DecreaseLives();
    if(livesRemaining() == 0)
    {
        setDead();
        
    }
}
