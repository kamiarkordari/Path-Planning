#include "vehicle.h"
#include <map>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::min;


// Initializes Vehicle
Vehicle::Vehicle(){}

Vehicle::Vehicle(int lane, float s, float v, string state) {
  this->lane = lane;
  this->s = s;
  this->speed = speed;
  this->acceleration = 0;
  this->state = state;
  this->car_ahead = false;
  this->car_ahead_speed = 0;
  this->car_ahead_distance = 10000;
  this->car_left_speed = 0;
  this->car_left_distance = 10000;
  this->car_right_speed = 0;
  this->car_right_distance = 10000;
  //car_left_behind = false;
  //car_right_ahead = false;
  //car_right_behind = false;
  this->car_left = false;
  this->car_right = false;
}

Vehicle::~Vehicle() {}

void Vehicle::check_lanes(Vehicle car) {
  float distance = car.s - this->s;

  if (car.lane == this->lane) {
    // check if we are too close to the fron car
    this->car_ahead |= (car.s > this->s) && (car.s - this->s < 30);

    if ((distance < this->car_ahead_distance) && (distance > 0)) {
      this->car_ahead_speed = car.speed;
    }
    //this->car_ahead = distance < 2*car.MIN_SAFE_DISTANCE && distance > 0; //(car.s > this->s) && (car.s - this->s < 30);
  } else if (car.lane == this->lane - 1){
    // Car on the left
    this->car_left |= (distance < car.MIN_SAFE_DISTANCE) && (distance > -car.MIN_SAFE_DISTANCE); //(this->s - 30 < car.s) && (this->s + 30 > car.s);
    if ((distance < this->car_left_distance) && (distance > 0)) {
      this->car_left_speed = car.speed;
    }
  } else if (car.lane = this->lane + 1) {
    // Car on the right
    this->car_right |= (distance < car.MIN_SAFE_DISTANCE) && (distance > -car.MIN_SAFE_DISTANCE); //(this->s - 30 < car.s) && (this->s + 30 > car.s);
    if ((distance < this->car_right_distance) && (distance > 0)) {
      this->car_right_speed = car.speed;
    }
  }

}

double Vehicle::choose_next_lane(double ref_vel) {
  //const double MAX_SPEED = 49.5;
  //const double MAX_ACC = 0.224;

  float cost_left = cost_state("CLL");
  float cost_right = cost_state("CLR");
  float cost_keep = cost_state("KL");

  this->acceleration = 0;

  float cost_min = min(cost_left, min(cost_right,cost_keep));

  if (cost_left == cost_min) {
    this->lane--;
  } else if (cost_right == cost_min) {
    this->lane++;
  } else {
    keep_lane(ref_vel);
  }

  /*
  if (this->car_ahead ) { // Car ahead
    if (!this->car_left && this->lane > 0) {
      // if there is no car left and there is a left lane.
      this->lane--; // Change lane left.
    } else if (!this->car_right && this->lane != 2){
      // if there is no car right and there is a right lane.
      this->lane++; // Change lane right.
    } else {
      //speed_diff -= MAX_ACC;
      this->acceleration -= MAX_ACC;
    }
  } else {
    if (this->lane != 1) { // if we are not on the center lane.
      if ((this->lane == 0 && !this->car_right) || (this->lane == 2 && !this->car_left)) {
        this->lane = 1; // Back to center.
      }
    }
    if (ref_vel < MAX_SPEED) {
      //speed_diff += MAX_ACC;
      this->acceleration += MAX_ACC;
    }
  }

  */

  ref_vel += this->acceleration;

  if (ref_vel > this->MAX_SPEED) {
    ref_vel = this->MAX_SPEED;
  }

  return ref_vel;
}


void Vehicle::keep_lane(double ref_vel) {
  if (this->car_ahead) {
    // slow down, there is a car ahead
    this->acceleration = -this->MAX_ACC;
  } else {
    if (ref_vel < this->MAX_SPEED) {
      // speed up, until speed reached to max, there is no car ahead
      this->acceleration = this->MAX_ACC;
    }
  }
}


float Vehicle::cost_state(string state) {
  float lane_speed = 0;
  if (state == "CLL") {
    if ((this->lane == 0) || this->car_left) {
      return 1;
    } else {
      lane_speed = this->car_left_speed;
    }
  }

  if (state == "CLR") {
    if ((this->lane == 2) || this->car_right) {
      return 1;
    } else {
      lane_speed = car_right_speed;
    }
  }

  if (state == "KL") {
    if (car_ahead) return 1;
  } else {
    lane_speed = this->MAX_SPEED;
  }

  return (this->MAX_SPEED - lane_speed)/this->MAX_SPEED;
}
