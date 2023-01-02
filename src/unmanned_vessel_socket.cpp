#include "unmanned_vessel_socket.h"

#include "route_point.h"
#include "route_point_gui.h"
#include "routeman.h"
#include "ais_target_data.h"
#include "ais_decoder.h"
#include "unmanned_vessel_meesage_header.h"
#include "geography_point.h"
#include "unmanned_vessle_target_data.h"

#include "comm_util.h"
enum {
  // id for sockets
  SERVER_ID = 100,
  SOCKET_ID
};

enum MESSAGE_ID : uint16_t {
  OBSTACLE_MESSAGE_ID = 0x0014,
  TARGET_MESSAGE_ID = 0x0015
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

wxBEGIN_EVENT_TABLE(UnmannedVesselSocket, wxEvtHandler)
    EVT_SOCKET(SOCKET_ID, UnmannedVesselSocket::OnUDPReciveEvent)
        wxEND_EVENT_TABLE()

            extern WayPointman* pWayPointMan;
extern AisDecoder* g_pAIS;

UnmannedVesselSocket::UnmannedVesselSocket() : obstacle_points_() {
  listen_address_.Hostname("10.201.222.145");
  listen_address_.Service(29000);
  socket_ = new wxDatagramSocket(listen_address_);


  double longitude = 18.299;
  double latitude = -69.998;
  auto target_id = 12;

  char longitude_direction = 'N';
  char latitude_direction = 'S';

  latitude = std::abs(latitude);
  longitude = std::abs(latitude);

  auto longitude_minute = (longitude - static_cast<int>(longitude)) * 60;
  auto longitude_second = (longitude_minute - static_cast<int>(longitude_minute)) * 60;

  auto latitude_minute = (latitude - static_cast<int>(latitude)) * 60;
  auto latitude_second = (latitude_minute - static_cast<int>(latitude_minute)) * 60;
  int hh = 12;
  int mm = 58;
  double ss = 27.21;
  auto TLL_SENTENCE = wxString::Format(
      "$RATLL,%02d,%02d%02d.%03d,%c,%03d%02d.%03d,%c,%s,%02d%02d%f,T,*%d\r\n", target_id,
      static_cast<int>(latitude), static_cast<int>(latitude_minute),
      static_cast<int>(latitude_second), latitude_direction,
      static_cast<int>(longitude), static_cast<int>(longitude_minute),
      static_cast<int>(longitude_second), longitude_direction,
      wxString::Format("%s_%d", "target", target_id), hh, mm, ss, 22);

  if (socket_ == nullptr) {
    wxLogMessage(_T("UnmannedVesselSocket:: socket initialzation failed"));
    return;
  }

  if (socket_->IsOk()) {
    wxLogMessage(_T("UnmannedVesselSocket:: socket_->IsOk(): true"));
    socket_->SetEventHandler(*this, SOCKET_ID);
    socket_->SetNotify(wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
    socket_->Notify(true);
  }
}

UnmannedVesselSocket::~UnmannedVesselSocket() {
  socket_->Close();
  delete socket_;
  socket_ = nullptr;
}

void UnmannedVesselSocket::OnUDPReciveEvent(wxSocketEvent& event) {
  wxLogMessage(_T("begin UnmannedVesselSocket::OnUDPReciveEvent"));

  auto socket = event.GetSocket();
  if (socket == nullptr) {
    wxLogMessage(_T("UnmannedVesselSocket:: event::GetSocket() nullptr"));
    return;
  }
  wxIPV4address addr{};
  char buf[1024]{};
  auto read_size = socket->Read(buf, sizeof(buf)).LastCount();
  if (!read_size) {
    wxLogMessage("ERROR: failed to receive data");
    return;
  }

  wxLogMessage("Received \"%s\" from %s:%u.",
               wxString::From8BitData(buf, read_size), addr.IPAddress(),
               addr.Service());

  decltype(read_size) processed_size = 0;
  UnmannedVesselMessageHeader message_header{};
  memset(&message_header, 0, sizeof(message_header));
  memcpy_s(&message_header, sizeof(message_header), buf,
           sizeof(message_header));
  processed_size += sizeof(message_header);
  uint16_t message_identification = 0x5a5a;
  if (message_identification != message_header.flag) {
    wxLogMessage("Message not recognized message_identification = %u ",
                 message_header.flag);
    return;
  }
  auto data_buffer = buf + processed_size;
  auto data_buffer_size = read_size - processed_size;
  if (MESSAGE_ID::OBSTACLE_MESSAGE_ID == message_header.message_id) {
    ProcessObstacle(data_buffer, data_buffer_size);
  } else if (MESSAGE_ID::TARGET_MESSAGE_ID == message_header.message_id) {
    ProcessAisTaget(data_buffer, data_buffer_size);
  }

  if (DevID::DevID_OCC_MAP == message_header.destination_device_id ||
      DevID::DevID_SHOER_MAP == message_header.destination_device_id ||
      DevID::DevID_USV_MAP == message_header.destination_device_id) {
  }

  wxLogMessage(_T("end UnmannedVesselSocket::OnUDPReciveEvent"));
}

void UnmannedVesselSocket::ProcessAisTaget(const char* buffer,
                                           int buffer_size) {
  int processed_size = 0;
  unsigned char number_of_tager = 0;
  if (buffer_size > processed_size) {
    memcpy_s(&number_of_tager, sizeof(number_of_tager), buffer + processed_size,
             sizeof(number_of_tager));
    processed_size += sizeof(number_of_tager);
    wxLogMessage("number of target = %u ", number_of_tager);
  }
  std::vector<std::shared_ptr<UnmanedVesselTargetData>> targets{};

  for (decltype(number_of_tager) i = 0; i < number_of_tager; ++i) {
    auto new_target_data = std::make_shared<UnmanedVesselTargetData>();
    if (buffer_size > processed_size) {
      memcpy_s(new_target_data.get(), sizeof(UnmanedVesselTargetData),
               buffer + processed_size, sizeof(UnmanedVesselTargetData));
      processed_size += sizeof(UnmanedVesselTargetData);
      targets.push_back(new_target_data);
    }
  }

  for (auto target_data : targets) {

    double longitude = 0;
    double latitude = 0;

    Int32ToDouble(target_data->longtitude, longitude);
    Int32ToDouble(target_data->latitude, latitude);

    char longitude_direction;
    char latitude_direction;

    auto longitude_minute = (longitude - static_cast<int>(longitude))*60;
    auto longitude_second = (longitude_minute - static_cast<int>(longitude_minute)) * 60;

    auto latitude_minute = (latitude - static_cast<int>(latitude)) * 60;
    auto latitude_second = (latitude_minute - static_cast<int>(latitude_minute)) * 60;
    int hh = 12;
    int mm = 58;
    double ss = 27.21;
    wxString::Format(
        "$RATLL,%2d,%2d%d.%3d,%c,%3d%2d.%3d,%c,%s,%2d%2d%f,T,*%d\r\n",
        target_data->target_id, static_cast<int>(latitude),
        static_cast<int>(latitude_minute), static_cast<int>(latitude_second),
        latitude_direction, static_cast<int>(longitude),
        static_cast<int>(longitude_minute), static_cast<int>(longitude_second),
        longitude_direction,
        wxString::Format("%s_%d", "target", target_data->target_id), hh, mm, ss,
        22);
  }

  auto new_ais_target = AisTargetDataMaker::GetInstance().GetTargetData();

  new_ais_target->Lon = -109.806;
  new_ais_target->Lat = -88.4;
  const char* ship_name = "HELLO WORLD";
  memcpy_s(new_ais_target->ShipName, sizeof(new_ais_target->ShipName),
           ship_name, strnlen_s(ship_name, sizeof(new_ais_target->ShipName)));
}

void UnmannedVesselSocket::ProcessObstacle(const char* buf, int read_size) {
  int processed_size = 0;
  unsigned char number_of_obstacle = 0;
  if (read_size > processed_size) {
    memcpy_s(&number_of_obstacle, sizeof(number_of_obstacle),
             buf + processed_size, sizeof(number_of_obstacle));
    processed_size += sizeof(number_of_obstacle);
    wxLogMessage("number of obstacle = %u ", number_of_obstacle);
  }
  if (!obstacle_points_.empty()) {
    for (auto obstacle_point : obstacle_points_) {
      pWayPointMan->RemoveRoutePoint(obstacle_point);
      delete obstacle_point;
      obstacle_point = nullptr;
    }
    obstacle_points_.clear();
  }
  if (number_of_obstacle > 30 || number_of_obstacle < 0) {
    return;
  }

  for (decltype(number_of_obstacle) i = 0; i < number_of_obstacle; ++i) {
    std::vector<GeographyPoint> obstacle_outline_point{};
    uint32_t obstacle_id = 0;
    if (read_size > processed_size) {
      memcpy_s(&obstacle_id, sizeof(obstacle_id), buf + processed_size,
               sizeof(obstacle_id));
      processed_size += sizeof(obstacle_id);
    } else {
      return;
    }
    int32_t number_of_outline_point = 0;
    if (read_size > processed_size) {
      memcpy_s(&number_of_outline_point, sizeof(number_of_outline_point),
               buf + processed_size, sizeof(number_of_outline_point));
      processed_size += sizeof(number_of_outline_point);
      wxLogMessage("Obstacle %d has %d outline points", obstacle_id,
                   number_of_outline_point);
    } else {
      return;
    }
    if (number_of_outline_point > 30 || number_of_outline_point < 0) {
      return;
    }

    decltype(read_size) outline_point_data_size =
        sizeof(int32_t) * 2 * number_of_outline_point;
    if ((read_size - processed_size) < outline_point_data_size) {
      wxLogMessage("Incomplete data");
      return;
    }
    for (decltype(read_size) j = 0; j < number_of_outline_point; ++j) {
      float longtitude = 0;
      float latitude = 0;

      int32_t encode_longtitude = 0;
      int32_t encode_latitude = 0;

      if (read_size > processed_size) {
        memcpy_s(&encode_longtitude, sizeof(encode_longtitude),
                 buf + processed_size, sizeof(encode_longtitude));
        processed_size += sizeof(encode_longtitude);
      } else {
        return;
      }

      if (read_size > processed_size) {
        memcpy_s(&encode_latitude, sizeof(encode_latitude),
                 buf + processed_size, sizeof(encode_latitude));
        processed_size += sizeof(encode_latitude);
      } else {
        return;
      }

      longtitude = -((double)encode_longtitude / double(1 << 31)) * 180.0;
      latitude = -((double)encode_latitude / double(1 << 31)) * 180.0;
      obstacle_outline_point.push_back({longtitude, latitude});
    }
    if (obstacle_outline_point.size() > 1) {
      auto obstacle_name =
          wxString::Format(wxT("RadarObStacle_%d"), obstacle_id);
      RoutePoint* radar_obstacle =
          new RoutePoint(obstacle_outline_point[0].latitude,
                         obstacle_outline_point[0].longitude, "food",
                         obstacle_name, wxString(""), false);
      radar_obstacle->SetUseSca(true);
      radar_obstacle->SetScaMin(1);
      radar_obstacle->SetObstacle(true);
      radar_obstacle->SetUseSca(false);
      for (auto& point : obstacle_outline_point) {
        radar_obstacle->AddObstacleOutlinePoint(point);
      }
      pWayPointMan->AddRoutePoint(radar_obstacle);
      obstacle_points_.push_back(radar_obstacle);
    }
  }
}
