# robo agents


build status: 
[![Build Status](https://travis-ci.org/keivanzavari/roboagents.svg?branch=master)](https://travis-ci.org/keivanzavari/roboagents.svg?branch=master)

## idea
There are two separate classes Robot and World. 

### The World class
* The World class encapsulates a simple 2D world. The world map is represented by a 2D data structure with each coordinate either blocked or unobstructed. The map is a rectangle of arbitrary size that is blocked around the entire border and has arbitrary internal coordinates blocked. Map configuration edge cases are not handled.
* World provides a way to place robots, and keeps track of the location of them. Each robot exists in a single coordinate space. There can be up to a few robots on the map at a time.
* World provides a movement API for the Robot class.
  * A robot can try to move a single space in any direction (holonomic), but if that space is blocked the robot does not move. Robot receives whether the move was successful or not
* World continuously displays the world (obstacles plus robots) to the terminal using ASCII. Below is example output with two robots A and B

1111111
1**A**00001
100**B**001
1001101
1001101
1000001
1111111

### The Robot class
The Robot class defines a simple autonomous robot.
* The robot should move based on some simple behavior (such as move one space a second in one direction until blocked, then move in another direction). This behavior is random for each instance of Robot.
* Robot does not interact with or have knowledge about the world beyond the move API
* Each Robot instance runs independently and not depend on a global "tick" (ie, each has a different thread).

## doxygen documentation
- run `doxygen doxyfile` and look into *doc/html/index.html* 

## how to run
This project has a stub that builds with CMake and Make by running the following command from the project directory: 

- `mkdir build && cd build && cmake .. && make`
- run *build/roboagents*

