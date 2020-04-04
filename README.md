[result]: ./images/result.gif "Short Gif"
![result]


#  Path Planning Project
In this project I built a path planner that creates smooth and safe trajectories for a self-driving car to follow.

### Goals
The goal is to safely navigate around a virtual highway with other traffic that is driving +-10 MPH of the 50 MPH speed limit.

Here is a list of our objectives:
- The car should go as close as possible to the 50 MPH speed limit. This requires changing lanes to pass slower traffic when possible.
- Other cars will try to change lanes too. The car should avoid hitting other cars at all cost.
- The car should drive inside of the marked road lanes at all times, unless going from one lane to another.
- The car should be able to make one complete loop around the 6946m highway. This should take about 5 minutes to complete.
- The car should not experience total acceleration over 10 m/s^2 and jerk that is greater than 10 m/s^3.

### Path planner
##### Input
The planner is provided with these input data:
- the car's localization and sensor fusion data
- other cars' localization and sensor fusion data
- a sparse map list of waypoints around the highway


##### Output
The path planner at each calculation cycle outputs a list of 50 points (pairs of x and y global coordinates) that together form a trajectory.

At the beginning of the calculation cycle the planner starts the new path with whatever waypoints from the previous path that is not used by the car. Then it appends new waypoints until the new path has 50 total waypoints. This ensures that there is a smooth transition from cycle to cycle.

In `main.cpp`, `next_x_vals`, and `next_y_vals` contains the point of the trajectory that are passed to the simulator.

`previous_path_x`, and `previous_path_y` show the last points given to the simulator controller with the processed points already removed.

### Considerations
##### Safe Lane Changing
Any time the car approaches another car in front of it that is moving slower than the speed limit, it slows down and considers changing lanes.

The car only change lanes if such a change would be safe, and also if the lane change would help it move through the flow of traffic better.

Path planner uses a cost function to find the best lane to change to. This cost function considers the distance and speed of the closest car in that lane.


##### Smoothness Transition
There will be some latency between the simulator running and the path planner returning a path (maybe just 1-3 time steps). During this delay the simulator will continue using points that it was last given. Path planner should either return a path that extends this previous path or make sure to create a new path that has a smooth transition with this last path.

##### Jerk Minimization
The jerk is calculated as the average acceleration over 1 second intervals. In order for the passenger to have an enjoyable ride the total acceleration should not go over 10 m/s^2, also the jerk should not go over 50 m/s^3.

We minimize total acceleration and jerk by gradually increasing and decreasing point path spacing based on the `car_speed` variable.

### Simulator
##### Information About Cars
The `sensor_fusion` variable contains all the information about the cars on the road.

The data format for each car is: `[id, x, y, vx, vy, s, d]`. The id is a unique identifier for that car. The `x`, `y` values are in global map coordinates, and the `vx`, `vy` values are the velocity components, also in reference to the global map. Finally `s` and `d` are the Frenet coordinates for that car.

##### Highway
Inside `data/highway_map.csv` there is a list of waypoints that go all the way around the track. The track contains a total of 181 waypoints, with the last waypoint mapping back around to the first. The waypoints are in the middle of the double-yellow dividing line in the center of the highway.

The track is 6945.554 meters around (about 4.32 miles). At 50 MPH, then it takes a little more than 5 minutes for the car to go all the way around the highway.

The highway has 6 lanes total - 3 heading in each direction. Each lane is 4 meters wide and the car should only ever be in one of the 3 lanes on the right-hand side. The car should always be inside a lane unless doing a lane change.


### Result
See a video of the final result by clicking on the image below.

[image-final-result]: ./images/screen_shot.jpg "Final Video Screenshot"

[![image-final-result]](https://www.youtube.com/watch?v=BIqywLi8dC0&feature=youtu.be)


---
### Basic Build Instructions
---

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./path_planning`.

Here is the data provided from the Simulator to the C++ Program

#### Main car's localization Data (No Noise)

["x"] The car's x position in map coordinates

["y"] The car's y position in map coordinates

["s"] The car's s position in frenet coordinates

["d"] The car's d position in frenet coordinates

["yaw"] The car's yaw angle in the map

["speed"] The car's speed in MPH

#### Previous path data given to the Planner

["previous_path_x"] The previous list of x points previously given to the simulator

["previous_path_y"] The previous list of y points previously given to the simulator

Note: The above previous list are returned but with processed points removed.

#### Previous path's end s and d values

["end_path_s"] The previous list's last point's frenet s value

["end_path_d"] The previous list's last point's frenet d value

#### Sensor Fusion Data, a list of all other car's attributes on the same side of the road.

["sensor_fusion"] A 2d vector of cars and then that car's [car's unique ID, car's x position in map coordinates, car's y position in map coordinates, car's x velocity in m/s, car's y velocity in m/s, car's s position in frenet coordinates, car's d position in frenet coordinates.

Note: There is no noise in this data.

## Dependencies

* cmake >= 3.5
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `install-mac.sh` or `install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets
    cd uWebSockets
    git checkout e94b6e1
    ```

##### Interpolating Points with Spline
To estimate the location of points between the known waypoints, we "interpolate" the position of those points using [spline tool](https://kluge.in-chemnitz.de/opensource/spline/) for C++, contained in just a single header file.

### Simulator
The simulator can be downloaded [here](https://github.com/udacity/self-driving-car-sim/releases/tag/T3_v1.2).  
