#ifndef ROBOT_H_
#define ROBOT_H_

#include "world.h"

// Forward declaration
class World;

/**
* Robot provides the necessary structure for a robot with its location in 
* 2D world & some methods
*
*/
class Robot {
    public:
        /**
        * Constructor with a name
        *
        */
        Robot(const char name);

        /**
        * robot location x, y
        */
        int x;
        int y;

        /*
        * random selection of adirection to move
        *
        * @return char direction : 
        * - Left : 'l' or 'L' 
        * - Right: 'r' or 'R' 
        * - Up   : 'u' or 'U' 
        * - Down : 'd' or 'D' 
        *
        */
        char requestMove();

        /*
        * @return char name :
        * Name of the robot, preferably only a letter i.e. a-z or A-Z
        *
        */
        char getName();

        /**
        * @brief Similar to World::run
        *
        * runs an infinite loop on the current thread with an update rate of 1[Hz].
        * It updates the requested direction of motion & displays/updates 
        * the direction on every iteration
        */
        void run();

        /**
        * contains print statements to show the thread id & direction
        * gets called by Robot::run
        */
        void display();

    private:
        /** @brief the last requested direction of motion
        */
        char direction_;

        /** @brief the name of the robot
        */
        char name_;
};

#endif
