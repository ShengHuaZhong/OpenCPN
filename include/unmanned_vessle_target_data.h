#ifndef OPENCPN_INCLUDE_UNMANNED_VESSEL_TARGET_DATA_H
#define OPENCPN_INCLUDE_UNMANNED_VESSEL_TARGET_DATA_H
#include <cstdint>
#pragma pack(1)
struct UnmanedVesselTargetData
{
  UnmanedVesselTargetData();
  UnmanedVesselTargetData(UnmanedVesselTargetData const& other);
  UnmanedVesselTargetData& operator=(UnmanedVesselTargetData const& other);
  int32_t target_id;
  int32_t longtitude;
  int32_t latitude;
  uint16_t velocity;  // m/s *100
  uint16_t bearing;   // rad *1000
  int32_t other;
};
#pragma pack()

#endif // !OPENCPN_INCLUDE_UNMANNED_VESSEL_TARGET_DATA_H
