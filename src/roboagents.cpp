#include "world.h"
#include "robot.h"

#include <iostream>
#include <pthread.h>
#include <thread>
#include <memory>
#include <chrono>
#include <mutex>

// number of robots
const int NUM_ROBOTS = 2;


// give an arbitrary size of the world map and number of blocked locations
int map_size = 10;
int num_blocked = 10;
// world map gets randomly initialized
World world(map_size, num_blocked);

// default location for the initial location of a robot in the world
volatile int x_init = 1;
volatile int y_init = 1;

// for mutual exclusion, helpful if you have more than one robot, they will not 
// be placed at init_x & y at the same time
std::mutex mu;

/** 
* thread function for robots
*/
extern "C" void* thread_robot_func( void * arg )
{

    // We don't need dynamic cast here
    Robot *rob = static_cast<Robot*>(arg);


    // locak the access to make sure only one thread is adding a robot in a 
    // certain location
    mu.lock();
    bool res = world.addRobot(x_init, y_init, rob->getName());    
    mu.unlock();

    bool result;
    char direction;
    while (true) {
        direction = rob->requestMove();
        
        // result of the move request from the world, not used anywhere yet
        result = world.moveRobot(direction, rob->getName());

        /*
        // if the move was successful, update the new location of the robot
        if (result)
        {
            // rob->x = ...
            // rob->y = ...
        }
        */

        // sleep for 1 sec
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    pthread_exit(NULL);

    return 0;
}

/** 
* thread function for world
*/
extern "C" void* thread_world_func( void * arg )
{
    world.run();
    pthread_exit(NULL);

    return 0;
}


int main(int argc, char** argv) {

    // define the necessary threads, one for the world + threads for robots
    pthread_t threads[NUM_ROBOTS+1];
    int rc[NUM_ROBOTS+1];
    
    int i =0;
    // pthread_create function starts a new thread in the calling process.
    // On success, it returns 0 & on error an error number
    rc[i] = pthread_create(&threads[i], 0, thread_world_func, 0);
    if (rc[i]) {
        std::cout << "Error:unable to create thread," << rc << std::endl;
        exit(-1);
    }

    // define a robot
    i++;    
    Robot * robot_a = new Robot('A');
    rc[i] = pthread_create(&threads[i], 0, thread_robot_func, robot_a);
    
    // define a robot
    i++;
    Robot * robot_b = new Robot('C');
    rc[i] = pthread_create(&threads[i], 0, thread_robot_func, robot_b);

    pthread_exit(NULL);
    
}
