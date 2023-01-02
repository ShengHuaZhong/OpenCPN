#ifndef OPENCPN_INCLUDE_GEOGRAPHY_POINT_H
#define OPENCPN_INCLUDE_GEOGRAPHY_POINT_H

#pragma pack(1)
struct GeographyPoint {
  GeographyPoint(float lon, float lat) : longitude(lon), latitude(lat) {}
  GeographyPoint() : longitude(0), latitude(0) {}
  float longitude;
  float latitude;
};
#pragma pack()

#endif  // !OPENCPN_INCLUDE_GEOGRAPHY_POINT_H
