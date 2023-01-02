#ifndef OPENCPN_INCLUDE_UNMANNED_VESSEL_MESSAGE_HEADER_H
#define OPENCPN_INCLUDE_UNMANNED_VESSEL_MESSAGE_HEADER_H
#include <cstdint>

#pragma pack(1)
struct UnmannedVesselMessageHeader {
  UnmannedVesselMessageHeader()
      : flag(0),
        len(0),
        message_id(0),
        source_device_id(0),
        destination_device_id(0),
        stamp(0) {}
  uint16_t flag;
  uint16_t len;
  uint16_t message_id;
  uint16_t source_device_id;
  uint16_t destination_device_id;
  uint32_t stamp;
};
#pragma pack()

#endif  // !OPENCPN_INCLUDE_UNMANNED_VESSEL_MESSAGE_HEADER_H
