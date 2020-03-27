#include "vehicle.h"
#include <map>
#include <string>
#include <vector>

using std::string;
using std::vector;

// Initializes Vehicle
Vehicle::Vehicle(){}

Vehicle::Vehicle(int lane, float s, float v, string state) {
  this->lane = lane;
  this->s = s;
  this->speed = speed;
  this->acceleration = 0;
  this->state = state;
  this->car_ahead = false;
  //car_left_ahead = false;
  //car_left_behind = false;
  //car_right_ahead = false;
  //car_right_behind = false;
  this->car_left = false;
  this->car_right = false;
}

Vehicle::~Vehicle() {}

void Vehicle::check_lanes(Vehicle car) {
  float distance = car.s - s;
/*
  if (lane == car.lane) {
    car_ahead = distance < car.MIN_SAFE_DISTANCE;
  } else if (lane == car.lane + 1){
    car_left_ahead = (distance < car.MIN_SAFE_DISTANCE) && (distance > 0);
    if ((distance < 3*car.MIN_SAFE_DISTANCE) && (distance > car.MIN_SAFE_DISTANCE)) {
      car_left_ahead_speed = car.speed;
    } else {
      car_left_ahead_speed = MAX_SPEED;
    }
    car_left_behind = (distance > -car.MIN_SAFE_DISTANCE) && (distance < 0);
  } else if (lane == car.lane - 1) {
    car_right_ahead = (distance < car.MIN_SAFE_DISTANCE) && (distance > 0);
    if ((distance < 3*car.MIN_SAFE_DISTANCE) && (distance > car.MIN_SAFE_DISTANCE)) {
      car_right_ahead_speed = car.speed;
    } else {
      car_right_ahead_speed = MAX_SPEED;
    }
    car_right_behind = (distance > -car.MIN_SAFE_DISTANCE) && (distance < 0);
  }
*/


  if (car.lane == this->lane) {
    // check if we are too close to the fron car
    this->car_ahead |= (car.s > this->s) && (car.s - this->s < 30);
  } else if (car.lane == this->lane - 1){
    // Car on the left
    this->car_left |= (this->s - 30 < car.s) && (this->s + 30 > car.s);
  } else if (car.lane = this->lane + 1) {
    // Car on the right
    this->car_right |= (this->s - 30 < car.s) && (this->s + 30 > car.s);
  }

/*
  if (lane == car.lane) {
    car_ahead = distance < car.MIN_SAFE_DISTANCE && distance > 0;
  } else if (lane == car.lane + 1) {
    car_left = (distance < car.MIN_SAFE_DISTANCE) && (distance > 0);
  } else if (lane == car.lane - 1) {
    car_right = (distance < car.MIN_SAFE_DISTANCE) && (distance > 0);
  }
*/
}

double Vehicle::choose_next_lane(double ref_vel) {
  //double speed_diff = 0;
/*
  if (car_ahead) {
    /*
    if ( !car_left_ahead && !car_left_behind && lane > 0 ) {
      // if there is no car left and there is a left lane
      lane--; // Change lane left
    }
    else if (!car_right_ahead && !car_right_behind && lane != 2){
      // if there is no car right and there is a right lane
      lane++; // change lane right
    } else {
      acceleration = -MAX_ACC;
    //}
  } else {
    if (lane != 1) { // if we are not on the center lane.
      if ((lane == 0 && !car_right_behind && !car_right_ahead) || (lane == 2 && !car_left_behind && !car_left_ahead)) {
        lane = 1; // back to center
      }
    }
    if (speed < MAX_SPEED) {
      acceleration = MAX_ACC;
    }
  }
*/
  double speed_diff = 0;
  const double MAX_SPEED = 49.5;
  const double MAX_ACC = .224;

  if ( car_ahead ) { // Car ahead
    if ( !car_left && lane > 0 ) {
      // if there is no car left and there is a left lane.
      lane--; // Change lane left.
    } else if ( !car_right && lane != 2 ){
      // if there is no car right and there is a right lane.
      lane++; // Change lane right.
    } else {
      speed_diff -= MAX_ACC;
    }
  } else {
    if ( lane != 1 ) { // if we are not on the center lane.
      if ( ( lane == 0 && !car_right ) || ( lane == 2 && !car_left ) ) {
        lane = 1; // Back to center.
      }
    }
    if ( ref_vel < MAX_SPEED ) {
      speed_diff += MAX_ACC;
    }
  }

  return ref_vel;

}

/*
float cost_state(string state) {
  if (state == "CLL") {
    if ((d==0) || car_left_behind || car_left_ahead) {
      return 1;
    } else {
      lane_speed = car_left_ahead_speed;
    }
  }

  if (state == "CLR") {
    if ((d==2) || car_right_behind || car_right_ahead) {
      return 1;
    } else {
      lane_speed = car_right_ahead_speed;
    }
  }

  if (state == "KL") {
    if (car_ahead) return 1;
  } else {
    lane_speed = MAX_SPEED;
  }

  return (2.0*MAX_SPEED - lane_speed)/MAX_SPEED;
}
*/
