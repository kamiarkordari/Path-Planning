#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

class Vehicle {
 public:
  // Constructors
  Vehicle();
  Vehicle(int lane, float s, float v, string state="CS");

  int get_lane(float d, float lane_width);

  void check_lanes(Vehicle car);

  int choose_next_lane(Vehicle ego_car);

  float cost_lane(lane);

  // Destructor
  virtual ~Vehicle();

  const int MIN_SAFE_DISTANCE = 30;
  const double MAX_SPEED = 49.5;
  const double MAX_ACC = 0.224;

  int lane;
  float s, d, speed, acceleration;
  string state;
  bool car_ahead, car_left_ahead, car_left_behind, car_right_ahead, car_right_behind;
  float car_ahead_speed, car_left_ahead_speed, car_left_behind_speed, car_right_ahead_speed, car_right_behind_speed;
};

#endif  // VEHICLE_H
