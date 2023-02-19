#ifndef OPENCPN_INCLUDE_UNMANNED_VESSEL_MESSAGE_HEADER_H
#define OPENCPN_INCLUDE_UNMANNED_VESSEL_MESSAGE_HEADER_H
#include <cstdint>


constexpr int velocity_factor = 100; // 速度变量保留2位小数精度，乘上100转换为整数变量。

enum MESSAGE_ID : uint16_t {
  UNMANNED_POSTURE_MESSAGE_ID = 0x0010,
  HEART_BEAT_MESSAGE_ID = 0X0011,
  OBSTACLE_MESSAGE_ID = 0x0014,
  TARGET_MESSAGE_ID = 0x0015,
  ROUTE_MESSAGE_ID = 0x0016,
  FIX_GYRATION_POINT_MESSAGE_ID = 0x0017,
  FIX_POINT_MESSAGE_ID = 0x0018,
  CHANG_VELOCITY_MESSAGE_ID = 0x0019
};

//设备标识 每个软件分配一个设备号，
typedef enum {
  DevID_USV = 0xa000,      /// 船基站端 开始
  DevID_USV_CM = 0xa001,   //船基站端监控软件
  DevID_USV_MAP = 0xa002,  //船基站端海图态势软件
  DevID_USV_AC = 0xa003,   //船控制端 航行主控软件
  DevID_USV_BS = 0xa004,   //船控制端 设备管控软件（嵌入式）

  DevID_SHOER = 0xb000,      /// 岸基端 开始
  DevID_SHOER_CM = 0xb001,   /// 岸基端 监控软件
  DevID_SHOER_MAP = 0xb002,  /// 岸基端 海图态势软件

  DevID_OCC = 0xc000,      /// 指控中心端  开始
  DevID_OCC_CM = 0xc001,   /// 指控中心端 监控软件
  DevID_OCC_MAP = 0xc002,  /// 指控中心端 海图态势软件

} DevID;

enum CONTROL_MODE :int32_t {
  CtrlMode_ManualRC = 1,       /// 遥控器驾驶模式
  CtrlMode_ManualCaptain = 2,   /// 船长模式
  CtrlMode_Hold = 4,           /// 暂停
  CtrlMode_AutoBase = 32,      /// 自主航行　(路径跟踪)
  CtrlMode_AutoCircle = 37,     /// 自主航行 (定圆心回转)
  CtrlMode_AutoFixPoint = 38,  /// 自主航行（定点保持）
  CtrlMode_None = 128,         /// 未知

};

#pragma pack(1)
struct UnmannedVesselMessageHeader {
  UnmannedVesselMessageHeader()
      : flag(0x5a5a),
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
