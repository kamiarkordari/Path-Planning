#ifndef ROAD_H
#define ROAD_H

#include <map>
#include <string>
#include <vector>
#include "vehicle.h"

class Road {
 public:
  // Constructor
  Road::Road(int speed_limit, double traffic_density, std::vector<int> &lane_speeds);

  // Destructor
  virtual ~Road();

  // Road functions
  Vehicle Road::get_ego();

  void Road::populate_traffic();

  void Road::advance();

  void Road::display(int timestep);

  void Road::add_ego(int lane_num, int s, std::vector<int> &config_data);

  void Road::add_vehicle(int lane_num, float s, float speed);

  void cull();

  // Road variables
  int update_width = 70;

  int vehicles_added = 0;

  int ego_key = -1;

  int num_lanes, speed_limit, camera_center;

  double density;

  std::map<int, Vehicle> vehicles;

  std::string ego_rep = " *** ";

  std::vector<int> lane_speeds;
};

#endif  // ROAD_H
