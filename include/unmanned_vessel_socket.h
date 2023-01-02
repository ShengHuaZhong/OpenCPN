#ifndef OPENCPN_INCLUDE_UNMANNED_VESSEL_SOCKET_H
#define OPENCPN_INCLUDE_UNMANNED_VESSEL_SOCKET_H

#include "wx/wx.h"
#include "wx/socket.h"
#include <wx/event.h>
#include <vector>

class RoutePoint;
 

class UnmannedVesselSocket: public wxEvtHandler {
public:
  UnmannedVesselSocket();
  ~UnmannedVesselSocket();

  void OnUDPReciveEvent(wxSocketEvent& event);

private:

  void ProcessAisTaget(const char* buffer, int buffer_size);
  void ProcessObstacle(const char* buffer, int buffer_size);

  std::vector<RoutePoint*> obstacle_points_;
  wxIPV4address listen_address_;
  wxDatagramSocket* socket_;
  
  wxDECLARE_EVENT_TABLE();
};

#endif //OPENCPN_INCLUDE_UNMANNED_VESSEL_SOCKET_H
