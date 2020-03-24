#include "vehicle.h"
#include <map>
#include <string>
#include <vector>

using std::string;
using std::vector;

// Initializes Vehicle
Vehicle::Vehicle(){}

Vehicle::Vehicle(int lane, float s, float v, string state) {
  lane = lane;
  s = s;
  speed = speed;
  state = state;
  car_ahead = false;
  car_left_ahead = false;
  car_left_behind = false;
  car_right_ahead = false;
  car_right_behind = false;
}

Vehicle::~Vehicle() {}

int Vehicle::get_lane(float d, float lane_width) {
  // get the lane of a car from it's distance from the middle of the road
  int lane = (int)d/lane_width;
  if (lane < 0) {
      return -1;
  } else {
    return lane;
  }
}

void Vehicle::check_lanes(Vehicle car) {
  float distance = car.s - s;

  if (lane == car.lane) {
    car_ahead = distance < car.MIN_SAFE_DISTANCE;
  } else if (lane == car.lane + 1){
    car_left_ahead = (distance < car.MIN_SAFE_DISTANCE) && (distance > 0);
    car_left_ahead_speed = car.speed;
    car_left_behind = (distance > -car.MIN_SAFE_DISTANCE) && (distance < 0);
  } else if (lane == car.lane - 1) {
    car_right_ahead = (distance < car.MIN_SAFE_DISTANCE) && (distance > 0);
    car_right_ahead_speed = car.speed;
    car_right_behind = (distance > -car.MIN_SAFE_DISTANCE) && (distance < 0);
  }
}

int Vehicle::choose_next_lane() {
  double speed_diff = 0;

  if (car_ahead) {
    if ( !car_left_behind && lane > 0 ) {
      // if there is no car left and there is a left lane
      lane--; // Change lane left
    } else if (!car_right && lane != 2){
      // if there is no car right and there is a right lane
      lane++; // change lane right
    } else {
      speed_diff -= MAX_ACC;
    }
  } else {
    if (lane != 1) { // if we are not on the center lane.
      if ((lane == 0 && !car_right) || (lane == 2 && !car_left)) {
        lane = 1; // back to center
      }
    }
    if (ref_vel < MAX_SPEED) {
      speed_diff += MAX_ACC;
    }
  }

}

float cost_state(state) {
  if (state == "CLL") {
    if ((d==0) || car_left_behind || car_left_ahead) {
      return 1;
    } else {
      lane_speed =
    }
  } else if (state == "CLR") {
    if ((d==2) || car_right_behind || car_right_ahead) return 1;
  } else if (state == "KL") {
    if (car_ahead) return 1;
  } esle {
    return (2.0*MAX_SPEED - lane_speed)/MAX_SPEED;
  }


  double speed_intended = lane_speeds[intended_lane];
  double speed_final = lane_speeds[final_lane];
  double cost = (2.0*target_speed - speed_intended - speed_final)/target_speed;

  return cost;

}
