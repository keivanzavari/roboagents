#include <iostream>
#include <thread>
#include <chrono>
#include "world.h"
#include "colors.h"

World::World(int map_size, int num_blocked)
{

    // ---------------------------------
    // construst a squared world map with blocked edges
    // ---------------------------------
    
    if (num_blocked >= (map_size-1)*(map_size-1)/2) {
        // check if the given number of blocked coordinates is 
        // not filling the map too much
        // map_size-1 because the edge is already going to be blocked
        // divided by 2 to make sure half of the coordinates are unobstructed
        num_blocked = (map_size-1)*(map_size-1)/2;

        std::cerr << "maximum number of blocked coordinates is " 
                  << num_blocked << std::endl;
    }

    map_.resize(map_size);
    for (int i=0; i<map_size; i++) {
        map_[i].resize(map_size);
        for (int j=0; j<map_size; j++) {
            // block the edges, first and last row and column
            if (i==0 || j==0 || i==map_size-1 || j==map_size-1) {
                map_[i][j] = '1';
            }
            else
            {
                map_[i][j] = '0';
            }
        }
    }

    // max number of row and col in the range [0,map_size-1]
    // for a 10x10 map size the index goes from 0 to 9
    row_max_ = col_max_ = map_size-1;

    // ---------------------------------
    // customize the map with random ones
    // ---------------------------------

    // initialize random seed
    srand (time(NULL));

    int rand_row, rand_col;
    int num_rand_generated = 1;

    while (num_rand_generated <= num_blocked) {
        // generate random number between 1 and map_size-1 
        rand_row = rand() % (row_max_ - 1) + 1;
        rand_col = rand() % (col_max_ - 1) + 1;

        if (map_[rand_row][rand_col] != '1') {

            map_[rand_row][rand_col] = '1';

            num_rand_generated++;
        }

    }

    robot_name_.clear();
    robot_xy_.clear();
    // robots_.clear();

}

World::World(const std::vector< std::vector<char> > & map) {
    // register the world size from the given map 
    row_max_ = map.size()-1;
    if (row_max_!=0)
        col_max_ = map[0].size();
    else
        std::cerr << "map cannot be empty!" << std::endl;

    // make a copy of the given map
    map_ = map;

    // initialize random seed
    srand (time(NULL));

    robot_name_.clear();
    robot_xy_.clear();
    // robots_.clear();
}


bool World::addRobot(int row, int col, char name) {

    // look for robots with the same name
    std::vector<char>::iterator it = std::find (robot_name_.begin(), 
                                           robot_name_.end(), name);

    // if a robot with the same name is found, do not add the robot, return false
    if (it == robot_name_.end() && !robot_name_.empty() && *it != '\0')
    {
        std::cout << "addRobot..." << std::endl;
        std::cout << KGRN << "\nrobot_name_.size..." << robot_name_.size() 
        << "\n" << RST << std::endl;

        std::cout <<  KGRN << "it..." << *it << RST << std::endl;
        std::cout <<  KGRN << "robot_name_.back..." << robot_name_.back() 
        << RST << std::endl;
        std::cout <<  KGRN << name << RST << std::endl;

        std::cerr <<  KRED <<"robot name already exists" << RST << std::endl;
        return false;
    }

    if (('a' < name < 'z') || ('A' < name < 'Z') ) {

        // if the requested location is occupied i.e. either blocked
        // or another robot is risiding at it
        if (map_[row][col] != '0') {
            // choose a new location for the new robot and come back here.
            // this new location cannot be edge cases, therefore the generated
            // number exculudes 0 and row_max 
            int rand_row = rand() % (row_max_-1) + 1;
            int rand_col = rand() % (col_max_-1) + 1;

            // std::cout << "given location of " << row << "," << col 
            // << " didn't work, trying new location " << rand_row << "," <<
            // rand_col << std::endl;
            addRobot(rand_row,rand_col,name);
            return true;
        }


        RobotXY new_robot_xy;
        new_robot_xy.row = row;
        new_robot_xy.col = col;

        robot_xy_.push_back(new_robot_xy);
        robot_name_.push_back(name);

        map_[row][col] = name;
    } else {

        std::cerr << "robot name can only be letters!" << std::endl;

        return false;
    }

    // std::cout << "robot " << name << " added to (" << row << "," << col << ")"
    // << std::endl; 
    return true;
}



bool World::moveRobot(char direction, char robot_name) {
    // This is the trick to find which robot needs to move
    // We find the index of the robot with the given name
    // As there are only a few robots present, we won't get into the question of 
    // the efficiency of find algorithms
    // We could also directly work with an index.
    std::vector<char>::iterator it = std::find (robot_name_.begin(), 
                                           robot_name_.end(), robot_name);

    int idx = it - robot_name_.begin();
    if (robot_name_[idx] != robot_name)
    {
        std::cerr << "name doesn't match the found name..." << std::endl;
        std::cout << "given name: " << robot_name << " found name: " 
        << robot_name_[idx] << std::endl;

        return false;
    }

    switch (direction)
    {
        // right, left, up, down
        case 'r':
        case 'R':
            if (map_[robot_xy_[idx].row][robot_xy_[idx].col+1] != '0')
                return false;

            map_[robot_xy_[idx].row][robot_xy_[idx].col] = '0';
            robot_xy_[idx].row;
            robot_xy_[idx].col++;

            break;
        case 'l':
        case 'L':
            if (map_[robot_xy_[idx].row][robot_xy_[idx].col-1] != '0')
                return false;

            map_[robot_xy_[idx].row][robot_xy_[idx].col] = '0';
            robot_xy_[idx].row;
            robot_xy_[idx].col--;
            break;
        case 'u':
        case 'U':
            if (map_[robot_xy_[idx].row-1][robot_xy_[idx].col] != '0')
                return false;
            map_[robot_xy_[idx].row][robot_xy_[idx].col] = '0';
            robot_xy_[idx].row--;
            robot_xy_[idx].col;

            break;
        case 'd':
        case 'D':
            if (map_[robot_xy_[idx].row+1][robot_xy_[idx].col] != '0')
                return false;

            map_[robot_xy_[idx].row][robot_xy_[idx].col] = '0';
            robot_xy_[idx].row++;
            robot_xy_[idx].col;
            break;
        default:
            std::cerr << "allowed directions are R, L, U, D." << std::endl;
            return false;
            break;
    }

    map_[robot_xy_[idx].row][robot_xy_[idx].col] = robot_name;
    return true;
}




void World::run() {
    while (true) {
        display();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}



void World::display() {
    // "Clear" screen
    for (int i = 0; i < 20; i++)
        std::cout << std::endl;

    // std::cout << "world thread id: " << std::this_thread::get_id() 
    // << std::endl;

    for (int i = 0; i <= row_max_; i++) {
        for (int j = 0; j <= col_max_; j++) {
            // if we have a robot at this location, print it in color
            if (map_[i][j] != '0' && map_[i][j] != '1')
                std::cout << KGRN << "\x1B[1m" << map_[i][j] << RST;
            else
                std::cout << map_[i][j];
        }
        std::cout << std::endl;
    }
}
