#include "unmanned_vessel_socket.h"

#include "route_point.h"
#include "route_point_gui.h"
#include "routeman.h"
#include "ais_target_data.h"
#include "ais_decoder.h"
#include "unmanned_vessel_meesage_header.h"
#include "geography_point.h"
#include "unmanned_vessle_target_data.h"
#include "unmanned_control_message.h"

#include "comm_util.h"
enum {
  // id for sockets
  SERVER_ID = 100,
  SOCKET_ID,
  HeartBeatTimer_ID
};
extern double vLat, vLon, gLat, gLon, gHdt;

wxBEGIN_EVENT_TABLE(UnmannedVesselSocket, wxEvtHandler)
    EVT_SOCKET(SOCKET_ID, UnmannedVesselSocket::OnUDPReciveEvent)
    EVT_TIMER(HeartBeatTimer_ID, UnmannedVesselSocket::OnHeartBeatTimerEvent)
wxEND_EVENT_TABLE()

            extern WayPointman* pWayPointMan;
extern AisDecoder* g_pAIS;

UnmannedVesselSocket::UnmannedVesselSocket() : obstacle_points_() {
  memset(&control_message_, 0, sizeof(control_message_));
  control_message_.data = CONTROL_MODE::CtrlMode_Hold;
  listen_address_.Hostname("192.168.1.153");
  listen_address_.Service(29000);
  socket_ = new wxDatagramSocket(listen_address_);

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
  heart_beat_timer.Start(1000, false);
  heart_beat_timer.SetOwner(this, HeartBeatTimer_ID);
  
}

UnmannedVesselSocket::~UnmannedVesselSocket() {
  socket_->Close();
  delete socket_;
  socket_ = nullptr;
}

void UnmannedVesselSocket::ChangedStatus(CONTROL_MODE val) {
  control_ = val;
}

void UnmannedVesselSocket::OnUDPReciveEvent(wxSocketEvent& event) {
#if _DEBUG

#endif  // _DEBUG

  wxLogMessage(_T("begin UnmannedVesselSocket::OnUDPReciveEvent"));

  auto socket = event.GetSocket();

  if (socket == nullptr) {
    wxLogMessage(_T("UnmannedVesselSocket:: event::GetSocket() nullptr"));
    return;
  }
  wxIPV4address addr{};
  std::vector<char> buffer{};
  buffer.resize(4096,0);
  auto buf = &buffer[0];
  auto read_size = socket->Read(buf, buffer.size()).LastCount();
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
  } else if (MESSAGE_ID::UNMANNED_POSTURE_MESSAGE_ID ==
             message_header.message_id) {
    UnmannedPostureMessage posture_message;

    memcpy_s(&posture_message, sizeof(posture_message), buf,
             sizeof(posture_message));
    wxLogMessage(_T("end UnmannedVesselSocket::UNMANNED_POSTURE_MESSAGE_ID"));
    auto tmp_hdt = posture_message.yaw / 1000.0 * 180 / 3.1415926;
    gHdt = tmp_hdt;
    if (std::abs(gHdt) < 2) {
      wxLogMessage(_T("yaw less = %d "), posture_message.yaw);
    }
    Int32ToDouble(posture_message.lat, gLat);
    Int32ToDouble(posture_message.lon, gLon);
   
  } else if (MESSAGE_ID::HEART_BEAT_MESSAGE_ID == message_header.message_id) {
    if (DevID::DevID_USV_BS == message_header.source_device_id &&
        DevID::DevID_USV_MAP == message_header.destination_device_id)
      ProcessMainControl(data_buffer, data_buffer_size);
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
  int id = 0;
  
  for (auto target_data : targets) {
    double longitude = 0;
    double latitude = 0;

    Int32ToDouble(target_data->longtitude, longitude);
    Int32ToDouble(target_data->latitude, latitude);

    auto new_ais_target = AisTargetDataMaker::GetInstance().GetTargetData();
    new_ais_target->HDG = (target_data->bearing / 1000.0) * 180 / 3.1415926;
    new_ais_target->Lon = longitude;
    new_ais_target->Lat = latitude;
    new_ais_target->SOG = target_data->velocity / 100.0 / 1852;
    new_ais_target->b_positionOnceValid = true;
    new_ais_target->MMSI = id;
    id++;
    auto obstacle_name =
      wxString::Format(wxT("Dynamic_%d"), id);
    const char* ship_name = obstacle_name;
    memcpy_s(new_ais_target->ShipName, sizeof(new_ais_target->ShipName),
      ship_name, strnlen_s(ship_name, sizeof(new_ais_target->ShipName)));
    g_pAIS->CommitAISTarget(new_ais_target, "", true, true);
  }
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
    // 读取预留值
    int32_t other = 0;
    if (read_size > processed_size) {
      memcpy_s(&other, sizeof(other),
        buf + processed_size, sizeof(other));
      processed_size += sizeof(other);
    }
    else {
      return;
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
      radar_obstacle->AddObstacleOutlinePoint(obstacle_outline_point[0]);
      if (pWayPointMan != nullptr) {
        pWayPointMan->AddRoutePoint(radar_obstacle);
        obstacle_points_.push_back(radar_obstacle);
      }
    }
  }
}

void UnmannedVesselSocket::SendTo(const wxIPV4address& address, const char* buffer, int buffer_size) {

  auto send_size = socket_
    ->SendTo(address, buffer,
      buffer_size)
    .LastWriteCount();
}

void UnmannedVesselSocket::OnHeartBeatTimerEvent(wxTimerEvent& event) {


  control_message_.message_header.flag = 0x5a5a;
  control_message_.message_header.message_id = MESSAGE_ID::HEART_BEAT_MESSAGE_ID;
  control_message_.message_header.source_device_id = DevID::DevID_USV_MAP;
  control_message_.message_header.destination_device_id = DevID::DevID_USV_BS;
  control_message_.message_header.len = sizeof(control_message_);

  wxIPV4address main_control_address;
  main_control_address.Hostname("192.168.1.161");
  main_control_address.Service(29003);

  auto send_size = socket_
    ->SendTo(main_control_address, &control_message_,
      sizeof(control_message_))
    .LastWriteCount();
}

void UnmannedVesselSocket::ProcessMainControl(const char* buffer,
                                              int buffer_size) {
  UnmannedControlMessage control_message;
  memset(&control_message, 0, sizeof(control_message));
  control_message.message_header.flag = 0x5a5a;
  control_message.message_header.message_id = MESSAGE_ID::HEART_BEAT_MESSAGE_ID;
  control_message.message_header.source_device_id = DevID::DevID_USV_MAP;
  control_message.message_header.destination_device_id = DevID::DevID_USV_BS;
  control_message.message_header.len = sizeof(control_message);
  memcpy_s(&control_message.data, sizeof(control_message.data), buffer, sizeof(control_message.data));

  wxIPV4address main_control_address;
  main_control_address.Hostname("192.168.1.150");
  main_control_address.Service(29002);

  auto send_size = socket_
                       ->SendTo(main_control_address, &control_message,
                                sizeof(control_message))
                       .LastWriteCount();
}
