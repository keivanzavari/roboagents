#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include <algorithm>    // std::find
#include "robot.h"

// Forward declaration
class Robot;

/**
* @brief container for the location of a robot in 2D world
*/
struct RobotXY {
    int row, col;
    
    /**
    * @brief row and col contain the index in the world map & they are 
    * zero based index. Constructor initializes them to zero.
    */
    RobotXY(){row = col = 0;}
};

/**
* @brief World is the required class for the construction of a 2D world with
* an arbitrary size.
*
* **STANDARD:** The world should be made out of only the following characters:
* - **0** : empty or onbstructed locations
* - **1** : blocked locations
* - letters **a-z** or **A-Z** for the robots which means up to 64 robots are 
* allowed 
*
* You can add robots to the world (World::addRobot) and simply call 
* World::run method. 
*
*/
class World {
 public:

    /**
    * Two types of constructor are available.
    * A Square of size map_size x map_size which will be
    * randomly initialized. The number of blocked locations is given 
    * by num_blocked
    *
    * @param: int map_size size of the world map
    * @param: int num_blocked number of blocked locations
    */
    World(int map_size, int num_blocked);

    /**
    * Two types of constructor are available.
    * An arbitrary size given map.
    *
    * **WARNING** There is no check for the edges of the world map, they 
    * have to be 1
    */
    World(const std::vector< std::vector<char> > & map);

    /**
    * Add a robot at (row, col) location. Each robot is identified by
    * its unique name.
    * If the location is obstructed i.e. blocked or another robot is present 
    * there, the method will try to find a new random location for the robot
    *
    * @param int row : X location of the robot
    * @param int col : Y location of the robot
    * @param char name Name of the robot, can only be a letter 
    *    i.e. in range [a,z] or [A,Z]
    *
    * @return bool :
    *    - true if the robot is successfully added to the world map
    *    - false if the name is not a letter
    */
    bool addRobot(int row, int col, char robot_name);

    /**
    * Move the robot in a given direction.
    * The method looks for the index of the robot with the given name to
    * access its location. 
    * To find out which robot needs to move, a simple find algorithm is used.
    * As there are only a few robots present, we won't get into the question of 
    * the efficiency of find algorithms.
    *
    * This method can also be implemented to directly work with an index. It 
    * just requires a different API.
    *
    * @param char direction : 
    * - Left : 'l' or 'L' 
    * - Right: 'r' or 'R' 
    * - Up   : 'u' or 'U' 
    * - Down : 'd' or 'D' 
    *
    * @param char robot_name
    *
    * @return true if the the operation was successfull
    */
    bool moveRobot(char direction, char robot_name);

    /**
    * runs an infinite loop on the current thread with an update rate of 1[Hz].
    * It displays/updates the world on every iteration
    */
    void run();

    /**
    * contains print statements to show the world, gets called by World::run
    */
    void display();

 private:
    /*
    * Dynamic container for the world map
    */
    std::vector< std::vector<char> > map_;

    /**
    * @brief maximum number of rows in the range [0,map_size-1]. 
    *
    * For a 10x10 map size this index goes from 0 to 9. 
    * The same applies for World::col_max_
    */
    int row_max_, col_max_;


    /**
    * @brief container for robot location
    */
    std::vector<RobotXY> robot_xy_;
    
    /**  @brief container for robot names
    */
    std::vector<char> robot_name_;


    /// You can also add robot objects as members of thisclass. They were
    /// not necessary in this project
    // std::vector<Robot *> robots_;
    // std::vector<Robot> robots_;

};

#endif
