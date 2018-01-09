#include "robot.h"
#include <iostream>
#include <thread>
#include <chrono>

Robot::Robot(const char name):
 direction_('R')
, x(0)
, y(0)
{
    name_ = name;

    // initialize random seed
    srand (time(NULL));

}

char Robot::getName()
{
    return name_;
}

char Robot::requestMove()
{
    // random number between zero (0) and four (4)
    int rand_int = rand() % 4;

    if (rand_int == 0)
        direction_ = 'R';
    else if (rand_int == 1)
        direction_ = 'L';
    else if (rand_int == 2)
        direction_ = 'U';
    else
        direction_ = 'D';

    return direction_;
}

void Robot::run() {
    while (true) {
    	direction_ = requestMove();
        display();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void Robot::display() {
	std::cout << "robot thread id: " << std::this_thread::get_id() << std::endl;
    std::cout << "---------" << direction_ << "-----------" << std::endl;
}
