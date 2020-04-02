#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Vehicle {
 public:
  // Constructors
  Vehicle();
  Vehicle(int lane, float s, float speed, string state="CS");

  void check_lanes(Vehicle car);

  double choose_next_lane(double ref_vel);

  float cost_state(string state);

  void keep_lane(double ref_vela);

  // Destructor
  virtual ~Vehicle();

  const int MIN_SAFE_DISTANCE = 30;
  const double MAX_SPEED = 49.5;
  const double MAX_ACC = 0.224;

  int lane;
  float s, d, speed, acceleration;
  string state;
  bool car_ahead, car_right, car_left;
  float car_ahead_speed, car_ahead_distance;
  float car_left_speed, car_left_distance;
  float car_right_speed, car_right_distance;
};

#endif  // VEHICLE_H
