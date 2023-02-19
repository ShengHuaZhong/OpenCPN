///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////
#include <sstream>
#include "OCPNPlatform.h"
#include "AboutFrame.h"
#include "ocpn_plugin.h"

extern OCPNPlatform* g_Platform;
///////////////////////////////////////////////////////////////////////////


AboutFrame::AboutFrame(wxWindow* parent, wxWindowID id, const wxString& title,
                       const wxPoint& pos, const wxSize& size, long style)
    : wxFrame(parent, id, title, pos, size, style) {
  // Connect Events
  this->Connect(wxEVT_ACTIVATE,
    wxActivateEventHandler(AboutFrame::AboutFrameOnActivate));
  this->Connect(wxEVT_CLOSE_WINDOW,
    wxCloseEventHandler(AboutFrame::AboutFrameOnClose));
}


AboutFrame::~AboutFrame() {
  // Disconnect Events
  this->Disconnect(wxEVT_ACTIVATE,
                   wxActivateEventHandler(AboutFrame::AboutFrameOnActivate));
  this->Disconnect(wxEVT_CLOSE_WINDOW,
                   wxCloseEventHandler(AboutFrame::AboutFrameOnClose));
}


