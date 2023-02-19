#ifndef OPENCPN_INCLUDE_UNMANNED_VESSEL_SOCKET_H
#define OPENCPN_INCLUDE_UNMANNED_VESSEL_SOCKET_H

#include "wx/wx.h"
#include "wx/socket.h"
#include <wx/event.h>
#include <vector>
#include "unmanned_control_message.h"
class RoutePoint;
 

class UnmannedVesselSocket: public wxEvtHandler {
public:
  UnmannedVesselSocket();
  ~UnmannedVesselSocket();

  void OnUDPReciveEvent(wxSocketEvent& event);
  void OnHeartBeatTimerEvent(wxTimerEvent& event);

  void SendTo(const wxIPV4address& address, const char* buffer, int buffer_size);

  void ChangedStatus(CONTROL_MODE value);

  void Pause() {
    control_message_.data = CONTROL_MODE::CtrlMode_Hold;
  }

  void Start() {
    control_message_.data = control_;
  }

  void Termination() {
    control_ = CONTROL_MODE::CtrlMode_Hold;
    control_message_.data = control_;
  }
private:

  void ProcessAisTaget(const char* buffer, int buffer_size);
  void ProcessObstacle(const char* buffer, int buffer_size);
  void ProcessMainControl(const char* buffer, int buffer_size);

  std::vector<RoutePoint*> obstacle_points_;
  wxIPV4address listen_address_;
  wxDatagramSocket* socket_;

  wxTimer heart_beat_timer;
  UnmannedControlMessage control_message_;

  CONTROL_MODE control_;
  wxDECLARE_EVENT_TABLE();
};

#endif //OPENCPN_INCLUDE_UNMANNED_VESSEL_SOCKET_H
