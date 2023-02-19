#ifndef OPENCPN_INCLUDE_UNMANNED_CONTROL_MESSAGE_H
#define OPENCPN_INCLUDE_UNMANNED_CONTROL_MESSAGE_H
#include "unmanned_vessel_meesage_header.h"
#pragma pack(1)

struct UnmannedControlMessage {
  UnmannedVesselMessageHeader message_header;
  int32_t data;
  unsigned char crc_value;
};


struct UnmannedPostureMessage {
  UnmannedVesselMessageHeader message_header;
  int32_t lon;             // 度，LSB:180/2^31
  int32_t lat;             // 度，LSB:180/2^31
  int32_t roll;           // 弧度, *1000
  int32_t pitch;          // 弧度, *1000
  int32_t yaw;            // 弧度, *1000，艏相角
  int32_t vel_north;      // 北向速度(m/s)  *100 
  int32_t vel_east;       // 东向速度(m/s)  *100
  int32_t rollspeed;     // 橫摇(rad/s)  *1000
  int32_t pitchspeed;    // 纵摇(rad/s)  *1000
  int32_t yawspeed;      // 艏摇(rad/s)  *1000
  int32_t height;        //	高度 米 *100
  uint64_t micro_sec;  //  毫秒
};


struct FixGyrationMessage {
  UnmannedVesselMessageHeader message_header;
  int32_t longitude;
  int32_t latitude;
  uint16_t velocity;
  unsigned char direction;
  uint16_t gyration_radius;
  int32_t other;
  unsigned char crc_value;
};

struct FixPointMessage {
  UnmannedVesselMessageHeader message_header;
  int32_t longitude;
  int32_t latitude;
  uint16_t velocity;
  uint16_t fix_point_radius;
  int32_t other;
  unsigned char crc_value;
};

struct ChangVelocityMessage {
  UnmannedVesselMessageHeader message_header;
  uint16_t velocity;
  int32_t other;
  unsigned char crc_value;
};

#pragma pack()

#endif //OPENCPN_INCLUDE_UNMANNED_CONTROL_MESSAGE_H
