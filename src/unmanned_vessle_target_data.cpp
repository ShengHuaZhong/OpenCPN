#include "unmanned_vessle_target_data.h"

UnmanedVesselTargetData::UnmanedVesselTargetData():
  target_id(0),
  longtitude(0),
  latitude(0),
  velocity(0),
  bearing(0),
  other(0)
{
}

UnmanedVesselTargetData::UnmanedVesselTargetData(UnmanedVesselTargetData const& other)
{
  target_id = other.target_id;
  longtitude = other.longtitude;
  latitude = other.latitude;
  velocity = other.velocity;
  bearing = other.bearing;
  this->other = other.other;
}

UnmanedVesselTargetData& UnmanedVesselTargetData::operator=(UnmanedVesselTargetData const& other)
{
  if (this != &other) {
    target_id = other.target_id;
    longtitude = other.longtitude;
    latitude = other.latitude;
    velocity = other.velocity;
    bearing = other.bearing;
    this->other = other.other;
  }
  return *this;
}

