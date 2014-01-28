Scentipede Project Outline and Implementation:

1.
class GameObject : public GraphObject 
{
public:
    GameObject(int imageID, StudentWorld* sw, int x, int y): This is the constructor for GameObject, which is the class that the rest of the objects in the game are derived from. Its parameters include an image ID of each object, a pointer to the Student World class and the starting coordinates of each object.
    virtual ~GameObject(){} : The destructor for this class does nothing.
    StudentWorld* getmyWorld() : This function returns the pointer to the Student World class stored as a private member function 
    virtual void doSomething() = 0; : The do Something function is listed as pure virtual because every object has a different implementation of what they should be doing during each tick
    virtual void isAttacked(): This is listed as a virtual function because every object can be attacked(with the exception of water droplet); however player has a very simple isAttacked function, which is defined in the base class. Hence, this function is not pure virtual.
    void updateXCoord(int newX): This updates the x coordinate of all objects when they move 
    void updateYCoord(int newY) : This updates the y coordinate of all objects when they move
    void setLives(int lives) : This function is used by the mushroom, poison mushroom, and water droplet class to set the number of lives that each object starts out with. Hence, it is defined in the base class.
    int livesRemaining() : Returns the number of lives that an object with lives has remaining
    void DecreaseLives() : decrements the number of lives of the appropriate object
    void setDead() : marks an object as dead and uses the displayme(false) function to no longer show the object on the screen.
    bool isDead() : returns true if the object has no lives remaining(mushrooms, water droplet) or if it has been attacked(insects, player) and it returns false otherwise
int getX() : returns the objects current x coordinate
int getY(): returns the objects current y coordinate 
}

class PlayerShip : public GameObject
{
public:
    PlayerShip(int imageID, StudentWorld* sw, int x, int y): constructor of the PlayerShip object, a derived class of GameObject; it sets the player’s initial coordinates to (15,0), sets m_canFire to true, meaning the player is allowed to fire water droplets, and passes the necessary parameters to GameObject
    ~PlayerShip() {} : the destructor does nothing
    virtual void doSomething () : this function gets the key from the user and uses a switch statement to pass the argument on to the move function, which then determines what the player’s move is. 
    bool move(int direction): uses a switch statement to determine which key was pressed. If there is an insect in the direction the user entered, then the player dies. If there is a mushroom or if the boundary of the player’s movement is reached, then the player stays where he is. If the player wants to fire a water droplet, a while loop is used to determine how many water droplets are needed based on the objects in the squares above the player. If an object(such as mushrooms or insects) is hit, then that object’s attack function is called. The m_canFire member is set to false, and can only be reversed to true after the user hits another key, or does nothing, ensuring he can only fire every other tick.
}

class Mushroom: public GameObject
{
public:
    Mushroom(int imageID, StudentWorld* sw, int x, int y) : passes the required parameters onto GameObject and sets the number of lives to 4
    ~Mushroom() {}
    virtual void doSomething () {} : does nothing 
    virtual void isAttacked() : give the player a point for successfully attacking the mushroom. Depending on the number of lives left, it sets the mushroom’s brightness to the appropriate luminosity. If there are no lives remaining, it sets the object as dead.  
};

class PoisonMushroom : public Mushroom
{
public:
    PoisonMushroom(int imageID, StudentWorld* sw, int x, int y) : same constructor as mushroom with a different imageID
    ~PoisonMushroom() {} : does nothing 

};

class WaterDroplet: public PlayerShip
{
public:
    WaterDroplet(int imageID, StudentWorld* sw, int x, int y) : the water droplet is derived from the player class. The constructor sets the initial location of the water droplet and sets the number of live equal to 2
    ~WaterDroplet() {} : does nothing
    virtual void doSomething() : decrements the number of lives of the water droplet by one.


};

class Insect : public GameObject
{
public:
    Insect(int imageID, int x, int y, StudentWorld* sw, std::string stateHorizontal, std::string stateVertical) : serves as the base class for all insect objects and is derived from GameObject. It passes the appropriate parameters along to the GameObject constructor and stores the insects initial vertical and horizontal movement
    ~Insect() {}
    virtual void doSomething() = 0 : this function is pure virtual because each insect has its own movement, thus each requires its own implementation of doSomething.
    virtual void isAttacked() : this function is virtual because each insect gives different points to the player when it is attacked. 
    std::string getVerticalState() : returns the current vertical orientation of an insect
    std::string getHorizontalState() : returns the current horizontal orientation of each insect
    void setStateVertical(std::string state) : changes the vertical state of the insect to that passed in by the code
    void setStateHorizontal(std::string state) : changes the horizontal state of the insect to that passed in by the code
};


class Scentipede : public Insect
{
public:
    Scentipede(int imageID, int x, int y, StudentWorld* sw, std::string stateHorizontal, std::string stateVertical) : passes in an image ID, a location, a pointer to student World, and starting horizontal and vertical directions to the base insect class. Also sets m_poisonedState to false because each scentipede segment begins in a normal state
    ~Scentipede() {} : does nothing
    virtual void doSomething() : 
    virtual void isAttacked() : sets the scentipede dead, gives the player 10 points, and there is a 33% chance that it will drop a mushroom
};


class Flea : public Insect
{
public:
    Flea(int imageID, int x, int y, StudentWorld* sw, std::string stateHorizontal, std::string stateVertical);
    ~Flea() {}
    virtual void doSomething();
    virtual void isAttacked() : gives the player 50 points and sets the flea as dead, and tells the program to no longer display it
};


class Spider : public Insect
{
public:
    Spider(int imageID, int x, int y, StudentWorld* sw, std::string stateHorizontal, std::string stateVertical) : passes the necessary parameters to the insect base class and sets the current tick count to 0, and the vertical distance to a random value between 1 and 4
    ~Spider() {} : does nothing
    virtual void doSomething(): if the tick counter is greater than 1, then the spider does nothing and returns. If the spider can move, it must determine its current vertical distance. If the distance is 0, the spider flips its vertical orientation and picks another random value for its new vertical distance; if the distance is greater than 0, the spider decrements it. The spider then determines its new location by moving diagonally from its present location; where it moves depends on its current horizontal and vertical orientations. If the new location occupies the same square as the player, the player dies. If it contains a mushroom, the mushroom dies, and if the location is out of the garden bounds, then the spider dies. 
    virtual void isAttacked() : sets the spider dead and gives the player 20 points 
    void setTick() : resets the tick count back to 0
    int getTick() : returns the current tick count
    void addTick() : increments the tick count by one
};



class Scorpion : public Insect
{
public:
    Scorpion(int imageID, int x, int y, StudentWorld* sw, std::string stateHorizontal, std::string stateVertical) : passes the required parameters to the insect base class parameter and sets initial location 
    ~Scorpion() {} : does nothing
    virtual void doSomething(): if the scorpion is currently on top of a regular mushroom, it uses the setID() function to change it to a poison mushroom. It then moves across the screen from right to left until it hits the right wall, and then it dies. If it lands on the same square as a player, the player dies. 
    virtual void isAttacked() : sets the scorpion dead and increases the player’s score by 25 points
    
};
	class StudentWorld: public GameWorld
{
public:
	StudentWorld(): sets the insect counter to 0
    ~StudentWorld(): does nothing
    virtual void init() : creates a new player; if a test parameter is given for the mushrooms, it allocates said number of mushrooms to a vector of pointers to mushroom objects. Otherwise, it allocates 25
    virtual int move() : creates insect objects and increments the insect count. It also goes through each vector(the mushroom, the insect, and the water droplet) and if the object is alive, then the objects doSomething() function is called. At the end, all of the dead mushrooms, insects and water droplets are deleted from the game play. If the player is still alive, the game continues, it the player is dead, then the game stops and the clean up function is called
    virtual void cleanUp() : deletes all objects from the garden
    void addInsects() : if there are given parameters, then insects are added based on the given chances. Otherwise, the odds of an insect being added is determined by the current score of the player. The higher the score, the more likely that new insects will be added. If there are no scentipedes, then a random number of scentipede segments ranging from 6 to 12 will be added. If there aren’t too many fleas, spiders, and scorpions, then one of the three types will be added to the game. 
    int numberofMushroomsat(int x, int y) const : returns the number of mushrooms in a square
    void generateRandomCoordinates(int& x, int& y);
    int randInt(int lowest, int highest);
    PlayerShip* getMyPlayer() : returns a pointer to the player object
    Mushroom* getaMushroom(int x, int y) : returns a pointer to a mushroom object in the specified coordinates
    Insect* getaInsect(int x, int y) : returns a pointer to an insect in a certain square
    void addMushroom(int x, int y) : adds a mushroom to the garden using the coordinates given and adds it to the mushroom vector
    bool isSpotOfPlayer(int x, int y) : returns true if the coordinates given match that of the player, false otherwise 
    bool isSpotOfScentipede(int x, int y) : returns true if there is a scentipede segment in a certain square, false otherwise
    int numberOfFleas() const : returns the number of fleas in the insect object vector
    int numberOfSpiders() const : returns the number of spiders in the insect object vector
    int numberOfScentipedes() const : returns the number of scentipedes in the insect object vector
    int numberOfScorpions() const : returns the number of scorpions in the insect object vector
    int numberOfInsectsAt(int x, int y) const : returns the number of insects at a certain square
    bool squareIsEmpty(int x, int y) : returns true if there are no objects in a specific square, false otherwise
    void addWaterDroplet(int x, int y) : adds a new water droplet in the specified square and adds it to the water droplet vector
    int numberOfScentipedsInRow(int y) : goes through each square in the row and counts up the number of scentipede segments
    void removeDeadObjects() : deallocates all of the objects that have died during the current tick of the game 
}

One functionality I wasn’t sure if I covered was the player’s restriction to performing only one activity per tick. I think this was covered by the switch statement, but I was unsure. 
When the water droplet hit both an insect and a mushroom, I decided that the player would be awarded points for killing only the insect.

Class StudentWorld: I ran the game with testParamsProvided set to true and false. I executed the game testing after each stage and used breakpoints to see that the proper objects had been added and deleted.

Class Mushroom: I checked if, when attacked, the Mushrooms had their brightness decrease four times. I mades sure multiple mushrooms did not occupy the same spot during debugging, and counted whether the number added was accurate.

Class playerShip: I checked wether it could only move within the specification's constraints. I checked wether it could fire drops till the end of the screen. I checked if it could fire drops ending at an object. I checked if it would die if it walked into an insect. I checked if it would die if an insect walked into it.

Class Droplet: I tested to see is the water droplet would last 2 ticks, and only be fired on every other tick. I also checked to see if it set the insects dead when it occupied the same square as them.

Class Scentipede: I checked the frequency at which they were added, to make sure they were added in the right circumstances
I checked wether they moved in a desired manner when unpoisoned
I checked wether they moved in a desired manner when poisoned
I checked wether it turn at the corners, and if it struck a mushroom. I tested it response to a droplet. I tested whether it would kill another scentipede object if it moved onto the same square as it

Class Flea: I checked if it killed a player when it occupied the same square. I checked if it dropped Mushrooms at the required probability. I checked whether they died when they moved out of the screen's range

Class Spider: I checked if it moved in a zig-zag manner and I checked if they chose a new travel plan once they had spent the vertical distance. I checked whether they died when they moved out of the screen's range

Class Scorpion: I checked wether it poisoned a mushroom by occupying the same square as it. I checked whether they died when they moved out of the screen's range