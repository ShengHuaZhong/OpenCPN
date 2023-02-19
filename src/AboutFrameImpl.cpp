/***************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  About Dialog
 * Author:   David Register
 *
 ***************************************************************************
 *   Copyright (C) 2019 by David S. Register                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 **************************************************************************/

#include "AboutFrameImpl.h"
#include "comm_util.h"
#include "config.h"
#include "OCPNPlatform.h"
#include "gui_lib.h"

#include "unmanned_control_message.h"

#ifdef __WXMSW__
#define EXTEND_WIDTH 70
#define EXTEND_HEIGHT 70
#else
#define EXTEND_WIDTH 50
#define EXTEND_HEIGHT 50
#endif

extern OCPNPlatform* g_Platform;

typedef enum {
  CON_PATH_TRACKING = 0x1,
  CON_PATH_TRACKING1,
  CON_PATH_TRACKING2,

  CON_CIRCULAR_ROTATION,
  CON_CIRCULAR_ROTATION1,
  CON_CIRCULAR_ROTATION2,
  CON_CIRCULAR_ROTATION3,
  CON_CIRCULAR_ROTATION4,

  CON_FIXED_POINT_HOLD,
  CON_FIXED_POINT_HOLD1,
  CON_FIXED_POINT_HOLD2,
  CON_FIXED_POINT_HOLD3,
  CON_FIXED_POINT_HOLD4,

  CON_BOAT_SPEED1,
  CON_BOAT_SPEED2,
  CON_BOAT_SPEED3
};

wxBEGIN_EVENT_TABLE(PathtrackingDialog, wxDialog)
    EVT_BUTTON(wxID_ANY, PathtrackingDialog::OnButton)
wxEND_EVENT_TABLE()

        PathtrackingDialog::PathtrackingDialog(UnmannedVesselSocket* socket,
          wxWindow* parent, wxWindowID id,
                                               const wxString& title,
                                               const wxPoint& pos,
                                               const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style), socket_(socket){
  this->SetSizeHints(wxDefaultSize, wxDefaultSize);

  wxBoxSizer* bSizer70;
  bSizer70 = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* bSizer27;
  bSizer27 = new wxBoxSizer(wxVERTICAL);

  m_staticText102 = new wxStaticText(this, wxID_ANY, wxT("璺?寰勭偣鍧愭爣锛?"),
                                     wxDefaultPosition, wxDefaultSize, 0);
  m_staticText102->Wrap(-1);
  bSizer27->Add(m_staticText102, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

  wxFlexGridSizer* fgSizer60;
  fgSizer60 = new wxFlexGridSizer(0, 2, 0, 0);
  fgSizer60->SetFlexibleDirection(wxBOTH);
  fgSizer60->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

  m_staticText98 = new wxStaticText(this, wxID_ANY, wxT("经度:"),
                                    wxDefaultPosition, wxDefaultSize, 0);
  m_staticText98->Wrap(-1);
  fgSizer60->Add(m_staticText98, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

  longtitude_text_ctrl =
      new wxTextCtrl(this, CON_PATH_TRACKING1, wxEmptyString, wxDefaultPosition,
                     wxDefaultSize, wxTE_PROCESS_ENTER);
  fgSizer60->Add(longtitude_text_ctrl, 0, wxALL, 5);

  bSizer27->Add(fgSizer60, 1, wxEXPAND, 5);

  wxFlexGridSizer* fgSizer601;
  fgSizer601 = new wxFlexGridSizer(0, 2, 0, 0);
  fgSizer601->SetFlexibleDirection(wxBOTH);
  fgSizer601->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

  m_staticText981 = new wxStaticText(this, wxID_ANY, wxT("纬度:"),
                                     wxDefaultPosition, wxDefaultSize, 0);
  m_staticText981->Wrap(-1);
  fgSizer601->Add(m_staticText981, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

  latitude_text_ctrl =
      new wxTextCtrl(this, CON_PATH_TRACKING2, wxEmptyString, wxDefaultPosition,
                     wxDefaultSize, wxTE_PROCESS_ENTER);
  fgSizer601->Add(latitude_text_ctrl, 0, wxALL, 5);

  bSizer27->Add(fgSizer601, 1, wxEXPAND, 5);

  ok_button = new wxButton(this, wxID_ANY, wxT("确定"), wxDefaultPosition,
                           wxDefaultSize, 0);
  bSizer27->Add(ok_button, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
  bSizer70->Add(bSizer27, 0, wxEXPAND, 5);

  this->SetSizer(bSizer70);
  this->Layout();
  bSizer70->Fit(this);

  this->Centre(wxBOTH);
}

PathtrackingDialog::~PathtrackingDialog() {}

void PathtrackingDialog::OnButton(wxCommandEvent& WXUNUSED(event)) {
  double latitude = 0.0;
  double longitude = 0.0;
  latitude_text_ctrl->GetValue().ToDouble(&latitude);
  longtitude_text_ctrl->GetValue().ToDouble(&longitude);
  

  if (socket_) {
  }
}

wxBEGIN_EVENT_TABLE(CircularRotationSettingDialog, wxDialog)
  EVT_BUTTON(wxID_ANY, CircularRotationSettingDialog::OnOKButton)
wxEND_EVENT_TABLE()
CircularRotationSettingDialog::CircularRotationSettingDialog(UnmannedVesselSocket* socket,wxWindow* parent, wxWindowID id, const wxString& title,
                     const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style), socket_(socket) {
  this->SetSizeHints(wxDefaultSize, wxDefaultSize);

  wxBoxSizer* bSizer70;
  bSizer70 = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* bSizer27;
  bSizer27 = new wxBoxSizer(wxVERTICAL);

  m_staticText105 = new wxStaticText(this, wxID_ANY, wxT("圆心坐标:"),
                                     wxDefaultPosition, wxDefaultSize, 0);
  m_staticText105->Wrap(-1);
  bSizer27->Add(m_staticText105, 0, wxALL, 5);

  wxFlexGridSizer* fgSizer68;
  fgSizer68 = new wxFlexGridSizer(0, 2, 0, 0);
  fgSizer68->SetFlexibleDirection(wxBOTH);
  fgSizer68->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

  m_staticText108 = new wxStaticText(this, wxID_ANY, wxT("经度:"),
                                     wxDefaultPosition, wxDefaultSize, 0);
  m_staticText108->Wrap(-1);
  fgSizer68->Add(m_staticText108, 0,
                 wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL,
                 5);

  longitude_text_ctrl =
      new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                     wxDefaultSize, wxTE_PROCESS_ENTER);
  fgSizer68->Add(longitude_text_ctrl, 0,
                 wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL,
                 5);

  m_staticText109 = new wxStaticText(this, wxID_ANY, wxT("纬度:"),
                                     wxDefaultPosition, wxDefaultSize, 0);
  m_staticText109->Wrap(-1);
  fgSizer68->Add(m_staticText109, 0,
                 wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL,
                 5);

  latitude_text_ctrl =
      new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                     wxDefaultSize, wxTE_PROCESS_ENTER);
  fgSizer68->Add(latitude_text_ctrl, 0,
                 wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
                 5);

  bSizer27->Add(fgSizer68, 1, wxEXPAND, 5);

  bSizer70->Add(bSizer27, 0, wxEXPAND, 5);

  wxBoxSizer* bSizer65;
  bSizer65 = new wxBoxSizer(wxVERTICAL);

  bSizer65->SetMinSize(wxSize(150, -1));
  wxBoxSizer* bSizer157;
  bSizer157 = new wxBoxSizer(wxVERTICAL);

  m_staticText106 = new wxStaticText(this, wxID_ANY, wxT("期望航速:"),
                                     wxDefaultPosition, wxDefaultSize, 0);
  m_staticText106->Wrap(-1);
  bSizer157->Add(m_staticText106, 0, wxALL, 5);

  wxFlexGridSizer* fgSizer70;
  fgSizer70 = new wxFlexGridSizer(2, 2, 0, 0);
  fgSizer70->SetFlexibleDirection(wxBOTH);
  fgSizer70->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

  m_staticText113 = new wxStaticText(this, wxID_ANY, wxT("航速:"),
                                     wxDefaultPosition, wxDefaultSize, 0);
  m_staticText113->Wrap(-1);
  fgSizer70->Add(m_staticText113, 0,
                 wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
                 5);

  m_textCtrl21 =
      new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                     wxDefaultSize, wxTE_PROCESS_ENTER);

  fgSizer70->Add(m_textCtrl21, 0, wxALL, 5);

  radius_static_text = new wxStaticText(this, wxID_ANY, wxT("半径:"),
    wxDefaultPosition, wxDefaultSize, 0);
  radius_static_text->Wrap(-1);

  fgSizer70->Add(radius_static_text, 1,
    wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
    5);

  radius_text_ctrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
    wxDefaultSize, wxTE_PROCESS_ENTER);

  fgSizer70->Add(radius_text_ctrl, 1, wxALL, 5);

  fgSizer70->Add(0, 15, 0, wxEXPAND, 5);

  bSizer157->Add(fgSizer70, 1, wxEXPAND, 5);

  bSizer65->Add(bSizer157, 1, wxEXPAND, 5);

  bSizer70->Add(bSizer65, 0, wxEXPAND, 5);

  wxBoxSizer* bSizer107;
  bSizer107 = new wxBoxSizer(wxVERTICAL);

  wxFlexGridSizer* fgSizer13;
  fgSizer13 = new wxFlexGridSizer(0, 2, 0, 0);
  fgSizer13->SetFlexibleDirection(wxBOTH);
  fgSizer13->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

  clockwise_button = new wxButton(this, wxID_ANY, wxT("顺时针"), wxDefaultPosition,
                            wxSize(100, 40), 0);
  fgSizer13->Add(clockwise_button, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
  clockwise_button->Bind(wxEVT_BUTTON, &CircularRotationSettingDialog::OnClockWiseButton, this);

  anti_clockwise_button = new wxButton(this, wxID_ANY, wxT("逆时针"), wxDefaultPosition,
                            wxSize(100, 40), 0);
  fgSizer13->Add(anti_clockwise_button, 0, wxALL, 5);
  anti_clockwise_button->Bind(wxEVT_BUTTON, &::CircularRotationSettingDialog::OnAntiClockWiseButton, this);

  bSizer107->Add(fgSizer13, 1, wxEXPAND, 5);

  bSizer107->Add(0, 15, 0, wxEXPAND, 5);

  ok_button = new wxButton(this, wxID_ANY, wxT("确定"), wxDefaultPosition,
                            wxDefaultSize, 0);
  bSizer107->Add(ok_button, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
  ok_button->Bind(wxEVT_BUTTON, &::CircularRotationSettingDialog::OnOKButton, this);

  bSizer70->Add(bSizer107, 0, wxEXPAND, 5);

  this->SetSizer(bSizer70);
  this->Layout();
  bSizer70->Fit(this);

  this->Centre(wxBOTH);
}

CircularRotationSettingDialog::~CircularRotationSettingDialog() {}

void CircularRotationSettingDialog::OnOKButton(wxCommandEvent& WXUNUSED(event)) {
  message_.crc_value = 0;
  message_.message_header.flag = 0x5a5a;
  message_.message_header.message_id = FIX_GYRATION_POINT_MESSAGE_ID;
  message_.message_header.destination_device_id = DevID::DevID_USV_MAP;
  message_.message_header.source_device_id = DevID::DevID_USV_AC;

  double latitude = 0;
  double longitude = 0;
  longitude_text_ctrl->GetValue().ToDouble(&longitude);
  latitude_text_ctrl->GetValue().ToDouble(&latitude);
  DoubleToInt32(longitude, message_.longitude);
  DoubleToInt32(latitude, message_.latitude);
  double v = 0;
  m_textCtrl21->GetValue().ToDouble(&v);
  message_.velocity = v * 100;

  double r = 0;
  radius_text_ctrl->GetValue().ToDouble(&r);
  message_.gyration_radius = r;
  char buffer[2049]{};
  message_.message_header.len = sizeof(message_);
  memcpy_s(buffer, sizeof(message_), &message_, sizeof(message_));
  if (socket_) {
    socket_->ChangedStatus(CONTROL_MODE::CtrlMode_AutoCircle);
    wxIPV4address main_control_address;
    main_control_address.Hostname("192.168.1.161");
    main_control_address.Service(29001);
    socket_->SendTo(main_control_address, buffer, message_.message_header.len);
  }
}

void CircularRotationSettingDialog::OnClockWiseButton(wxCommandEvent& WXUNUSED(event)) {
  message_.direction = 0;
}
void CircularRotationSettingDialog::OnAntiClockWiseButton(wxCommandEvent& WXUNUSED(event)) {
  message_.direction = 1;
}
///////////////////////////////////////////////////////////////////////////
///  MyDialog7 (Fixed point hold)
///////////////////////////////////////////////////////////////////////////////

FixPointSettingDialog::FixPointSettingDialog(UnmannedVesselSocket* socket, wxWindow* parent, wxWindowID id, const wxString& title,
                     const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style), socket_(socket) {
  this->SetSizeHints(wxDefaultSize, wxDefaultSize);

  wxBoxSizer* bSizer70;
  bSizer70 = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* bSizer27;
  bSizer27 = new wxBoxSizer(wxVERTICAL);

  m_staticText105 = new wxStaticText(this, wxID_ANY, wxT("驻波点坐标 :"),
                                     wxDefaultPosition, wxDefaultSize, 0);
  m_staticText105->Wrap(-1);
  bSizer27->Add(m_staticText105, 0, wxALL, 5);

  wxFlexGridSizer* fgSizer68;
  fgSizer68 = new wxFlexGridSizer(0, 2, 0, 0);
  fgSizer68->SetFlexibleDirection(wxBOTH);
  fgSizer68->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

  m_staticText108 = new wxStaticText(this, wxID_ANY, wxT("经度:"),
                                     wxDefaultPosition, wxDefaultSize, 0);
  m_staticText108->Wrap(-1);
  fgSizer68->Add(m_staticText108, 0,
                 wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL,
                 5);

  longitude_text_ctrl =
      new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                     wxDefaultSize, wxTE_PROCESS_ENTER);
  fgSizer68->Add(longitude_text_ctrl, 0,
                 wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL,
                 5);

  m_staticText109 = new wxStaticText(this, wxID_ANY, wxT("纬度:"),
                                     wxDefaultPosition, wxDefaultSize, 0);
  m_staticText109->Wrap(-1);
  fgSizer68->Add(m_staticText109, 0,
                 wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL,
                 5);

  latitude_text_ctrl =
      new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                     wxDefaultSize, wxTE_PROCESS_ENTER);
  fgSizer68->Add(latitude_text_ctrl, 0,
                 wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
                 5);

  fgSizer68->Add(0, 10, 0, 0, 5);

  bSizer27->Add(fgSizer68, 1, wxEXPAND, 5);

  bSizer70->Add(bSizer27, 0, wxEXPAND, 5);

  wxBoxSizer* bSizer65;
  bSizer65 = new wxBoxSizer(wxVERTICAL);

  bSizer65->SetMinSize(wxSize(150, -1));
  wxBoxSizer* bSizer157;
  bSizer157 = new wxBoxSizer(wxVERTICAL);

  m_staticText106 = new wxStaticText(this, wxID_ANY, wxT("回转半径:"),
                                     wxDefaultPosition, wxDefaultSize, 0);
  m_staticText106->Wrap(-1);
  bSizer157->Add(m_staticText106, 0, wxALL, 5);

  wxFlexGridSizer* fgSizer70;
  fgSizer70 = new wxFlexGridSizer(0, 2, 0, 0);
  fgSizer70->SetFlexibleDirection(wxBOTH);
  fgSizer70->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

  m_staticText113 = new wxStaticText(this, wxID_ANY, wxT("半径:"),
                                     wxDefaultPosition, wxDefaultSize, 0);
  m_staticText113->Wrap(-1);
  fgSizer70->Add(m_staticText113, 0,
                 wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
                 5);

  radius_text_ctrl =
      new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                     wxDefaultSize, wxTE_PROCESS_ENTER);
  fgSizer70->Add(radius_text_ctrl, 0, wxALL, 5);

  fgSizer70->Add(0, 10, 0, 0, 5);

  bSizer157->Add(fgSizer70, 1, wxEXPAND, 5);

  bSizer65->Add(bSizer157, 1, wxEXPAND, 5);

  bSizer70->Add(bSizer65, 0, wxEXPAND, 5);

  wxBoxSizer* bSizer107;
  bSizer107 = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* bSizer173;
  bSizer173 = new wxBoxSizer(wxVERTICAL);

  m_staticText129 = new wxStaticText(this, wxID_ANY, wxT("偏离回航速度:"),
                                     wxDefaultPosition, wxDefaultSize, 0);
  m_staticText129->Wrap(-1);
  bSizer173->Add(m_staticText129, 0, wxALL, 5);

  wxFlexGridSizer* fgSizer78;
  fgSizer78 = new wxFlexGridSizer(0, 3, 0, 0);
  fgSizer78->SetFlexibleDirection(wxBOTH);
  fgSizer78->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

  m_staticText132 = new wxStaticText(this, wxID_ANY, wxEmptyString,
                                     wxDefaultPosition, wxDefaultSize, 0);
  m_staticText132->Wrap(-1);
  fgSizer78->Add(m_staticText132, 0, wxALL, 5);

  velocity_text_ctrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(-1, -1),
                                wxDefaultSize, wxTE_PROCESS_ENTER);
  fgSizer78->Add(velocity_text_ctrl, 0, wxALL, 5);

  m_staticText130 = new wxStaticText(this, wxID_ANY, wxT("节"),
                                     wxDefaultPosition, wxDefaultSize, 0);
  m_staticText130->Wrap(-1);
  fgSizer78->Add(m_staticText130, 0,
                 wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL,
                 5);

  bSizer173->Add(fgSizer78, 1, wxEXPAND, 5);

  bSizer173->Add(0, 20, 0, 0, 5);

  bSizer107->Add(bSizer173, 1, wxEXPAND, 5);

  m_button94 = new wxButton(this, wxID_ANY, wxT("确定"), wxDefaultPosition,
                            wxDefaultSize, 0);
  bSizer107->Add(m_button94, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

  bSizer70->Add(bSizer107, 0, wxEXPAND, 5);
  m_button94->Bind(wxEVT_BUTTON, &FixPointSettingDialog::OnOKButton, this);
  this->SetSizer(bSizer70);
  this->Layout();
  bSizer70->Fit(this);

  this->Centre(wxBOTH);
}

FixPointSettingDialog::~FixPointSettingDialog() {}

void FixPointSettingDialog::OnOKButton(wxCommandEvent& WXUNUSED(event)) {
  FixPointMessage message_{};
  message_.crc_value = 0;
  message_.message_header.flag = 0x5a5a;
  message_.message_header.message_id = FIX_POINT_MESSAGE_ID;
  message_.message_header.destination_device_id = DevID::DevID_USV_MAP;
  message_.message_header.source_device_id = DevID::DevID_USV_AC;

  double latitude = 0;
  double longitude = 0;
  longitude_text_ctrl->GetValue().ToDouble(&longitude);
  latitude_text_ctrl->GetValue().ToDouble(&latitude);
  DoubleToInt32(longitude, message_.longitude);
  DoubleToInt32(latitude, message_.latitude);

  double v = 0;
  velocity_text_ctrl->GetValue().ToDouble(&v);
  message_.velocity = v * 100; // 速度2位小数点精度，乘100;
  double radius = 0;
  if (radius_text_ctrl->GetValue().ToDouble(&radius)) {
    message_.fix_point_radius = radius;
  }
  char buffer[2049]{};
  message_.message_header.len = sizeof(message_);
  memcpy_s(buffer, sizeof(message_), &message_, sizeof(message_));
  if (socket_) {
    socket_->ChangedStatus(CONTROL_MODE::CtrlMode_AutoFixPoint);
    wxIPV4address main_control_address;
    main_control_address.Hostname("192.168.1.161");
    main_control_address.Service(29001);
    socket_->SendTo(main_control_address, buffer, message_.message_header.len);
  }
}

wxBEGIN_EVENT_TABLE(AboutFrameImpl, wxFrame)
    EVT_BUTTON(CON_PATH_TRACKING, AboutFrameImpl::MyDlg5)
    EVT_BUTTON(CON_CIRCULAR_ROTATION, AboutFrameImpl::MyDlg6)
    EVT_BUTTON(CON_FIXED_POINT_HOLD, AboutFrameImpl::MyDlg7)
wxEND_EVENT_TABLE()

void AboutFrameImpl::MyDlg5(wxCommandEvent& event) {
  PathtrackingDialog dialog(socket_,this);
  dialog.ShowModal();
}
void AboutFrameImpl::MyDlg6(wxCommandEvent& event) {
  CircularRotationSettingDialog dialog(socket_,this);
  dialog.ShowModal();
}
void AboutFrameImpl::MyDlg7(wxCommandEvent& event) {
  FixPointSettingDialog dialog( socket_,this);
  dialog.ShowModal();
}

AboutFrameImpl::AboutFrameImpl(UnmannedVesselSocket* socket, wxWindow* parent,
                               wxWindowID id, const wxString& title,
                               const wxPoint& pos, const wxSize& size,
                               long style)
    : AboutFrame(parent, id, title, pos, size, style), socket_(socket) {

  wxBitmap logo(wxString::Format("%s/opencpn.png",
                                 g_Platform->GetSharedDataDir().c_str()),
                wxBITMAP_TYPE_ANY);

#if wxUSE_WEBVIEW && defined(HAVE_WEBVIEW)
  
#else
  m_htmlWinHelp->LoadFile(wxString::Format(
      "%s/doc/help_en_US.html", g_Platform->GetSharedDataDir().c_str()));
#endif

  this->SetSizeHints(wxSize(360, 450), wxSize(360, 450));

  wxBoxSizer* bSizerMain;
  bSizerMain = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* bSizerContentMain;
  bSizerContentMain = new wxBoxSizer(wxHORIZONTAL);

  wxBoxSizer* bSizerLeftColumn;
  bSizerLeftColumn = new wxBoxSizer(wxVERTICAL);
  bSizerContentMain->Add(bSizerLeftColumn, 0, wxEXPAND, 5);

  wxBoxSizer* bSizerContent;
  bSizerContent = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* bSizerAbout;
  bSizerAbout = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* bSizerParticipate;
  bSizerParticipate = new wxBoxSizer(wxHORIZONTAL);

  bSizerAbout->Add(bSizerParticipate, 0, wxEXPAND, 5);

  wxBoxSizer* bSizerLogFile;
  bSizerLogFile = new wxBoxSizer(wxHORIZONTAL);

  bSizerAbout->Add(bSizerLogFile, 1, wxEXPAND | wxTOP, 15);

  wxBoxSizer* bSizerIniFile;
  bSizerIniFile = new wxBoxSizer(wxHORIZONTAL);

  bSizerAbout->Add(bSizerIniFile, 1, wxEXPAND, 5);

  bSizerContentMain->Add(bSizerContent, 1, wxEXPAND, 5);

  bSizerMain->Add(bSizerContentMain, 1, wxEXPAND, 5);

  wxBoxSizer* bSizerMainLnks;
  bSizerMainLnks = new wxBoxSizer(wxHORIZONTAL);

  wxBoxSizer* bSizerLinksInner;
  bSizerLinksInner = new wxBoxSizer(wxHORIZONTAL);

  bSizerLinksInner->Add(0, 0, 1, wxEXPAND, 5);

  bSizerLinksInner->Add(0, 0, 1, wxEXPAND, 5);

  bSizerMain->Add(bSizerMainLnks, 0, wxEXPAND, 0);

  this->SetSizer(bSizerMain);
  this->Layout();

  this->Centre(wxBOTH);

  // Connect Events


 
  this->SetBackgroundColour(
      wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));

  wxBoxSizer* bSizer32;
  bSizer32 = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* bSizer34;
  bSizer34 = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* bSizer29;
  bSizer29 = new wxBoxSizer(wxVERTICAL);

  m_button7 = new wxButton(this, CON_PATH_TRACKING, wxT("路径追踪"),
                           wxDefaultPosition, wxSize(150, 50), 0);
  bSizer29->Add(m_button7, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

  bSizer29->Add(0, 10, 1, wxEXPAND, 5);

  bSizer34->Add(bSizer29, 0, wxEXPAND, 5);

  wxBoxSizer* bSizer30;
  bSizer30 = new wxBoxSizer(wxVERTICAL);

  m_button8 = new wxButton(this, CON_CIRCULAR_ROTATION, wxT("定圆回转"),
                           wxDefaultPosition, wxSize(150, 50), 0);
  bSizer30->Add(m_button8, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

  bSizer30->Add(0, 10, 0, 0, 5);

  bSizer34->Add(bSizer30, 0, wxEXPAND, 5);

  wxBoxSizer* bSizer31;
  bSizer31 = new wxBoxSizer(wxVERTICAL);

  m_button9 = new wxButton(this, CON_FIXED_POINT_HOLD, wxT("定圆保持"),
                           wxDefaultPosition, wxSize(150, 50), 0);
  bSizer31->Add(m_button9, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

  bSizer31->Add(0, 10, 1, wxEXPAND, 5);

  bSizer34->Add(bSizer31, 0, wxEXPAND, 5);

  wxFlexGridSizer* fgSizer22;
  fgSizer22 = new wxFlexGridSizer(0, 6, 0, 0);
  fgSizer22->SetFlexibleDirection(wxBOTH);
  fgSizer22->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

  fgSizer22->Add(10, 0, 0, 0, 5);

  change_velocity_button = new wxButton(this, wxID_ANY, wxT("航速设定"),
                             wxPoint(-1, -1), wxSize(100, 50), 0);
  change_velocity_button->Bind(wxEVT_BUTTON, &AboutFrameImpl::OnChangeVelocityButtion, this);
  fgSizer22->Add(change_velocity_button, 0, wxALL, 5);

  fgSizer22->Add(10, 0, 0, 0, 5);

  m_button18 = new wxButton(this, wxID_ANY, wxT("航速"), wxDefaultPosition,
                            wxSize(75, 25), 0);
  fgSizer22->Add(m_button18, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

  velocity_text_ctrl = new wxTextCtrl(this, wxID_ANY, wxT("6"), wxDefaultPosition,
                                wxSize(70, 25), wxTE_PROCESS_ENTER);
  fgSizer22->Add(velocity_text_ctrl, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

  m_staticText31 = new wxStaticText(this, wxID_ANY, wxT("节"),
                                    wxDefaultPosition, wxDefaultSize, 0);
  m_staticText31->Wrap(-1);
  fgSizer22->Add(m_staticText31, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

  bSizer34->Add(fgSizer22, 0, wxEXPAND, 5);

  bSizer34->Add(0, 10, 0, 0, 5);

  bSizer32->Add(bSizer34, 0, wxEXPAND, 5);

  wxFlexGridSizer* fgSizer1;
  fgSizer1 = new wxFlexGridSizer(0, 4, 0, 0);
  fgSizer1->SetFlexibleDirection(wxBOTH);
  fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

  fgSizer1->SetMinSize(wxSize(-1, 80));

  fgSizer1->Add(40, 0, 0, 0, 5);

  wxBoxSizer* bSizer64;
  bSizer64 = new wxBoxSizer(wxVERTICAL);

  wxFlexGridSizer* fgSizer24;
  fgSizer24 = new wxFlexGridSizer(0, 2, 0, 0);
  fgSizer24->SetFlexibleDirection(wxBOTH);
  fgSizer24->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

  m_bpButton11 =
      new wxBitmapButton(this, wxID_ANY, wxNullBitmap, wxDefaultPosition,
                         wxDefaultSize, wxBU_AUTODRAW | 0);

  m_bpButton11->SetBitmap(wxBitmap(wxT("./uidata/start2.png"),
                                   wxBITMAP_TYPE_ANY));
  m_bpButton11->SetBitmapDisabled(wxNullBitmap);
  m_bpButton11->SetBitmapPressed(wxNullBitmap);
  m_bpButton11->SetBitmapFocus(wxNullBitmap);
  m_bpButton11->SetBitmapCurrent(wxNullBitmap);
  m_bpButton11->SetBitmapMargins(wxSize(5, 5));
  m_bpButton11->Bind(wxEVT_BUTTON, &AboutFrameImpl::OnStartButtion, this);
  fgSizer24->Add(m_bpButton11, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  m_staticText8 = new wxStaticText(this, wxID_ANY, wxT("开始"),
                                   wxDefaultPosition, wxSize(-1, -1), 0);
  m_staticText8->Wrap(-1);
  fgSizer24->Add(m_staticText8, 0,
                 wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
                 5);

  bSizer64->Add(fgSizer24, 0, wxEXPAND, 5);

  fgSizer1->Add(bSizer64, 1, wxEXPAND, 5);

  wxBoxSizer* bSizer121;
  bSizer121 = new wxBoxSizer(wxVERTICAL);

  wxFlexGridSizer* fgSizer26;
  fgSizer26 = new wxFlexGridSizer(0, 2, 0, 0);
  fgSizer26->SetFlexibleDirection(wxBOTH);
  fgSizer26->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

  m_bpButton13 =
      new wxBitmapButton(this, wxID_ANY, wxNullBitmap, wxDefaultPosition,
                         wxDefaultSize, wxBU_AUTODRAW | 0);

  m_bpButton13->SetBitmap(wxBitmap(wxT("./uidata/pause2.png"),
                                   wxBITMAP_TYPE_ANY));
  m_bpButton13->SetBitmapMargins(wxSize(5, 5));
  fgSizer26->Add(m_bpButton13, 0, wxALL, 5);
  m_bpButton13->Bind(wxEVT_BUTTON, &AboutFrameImpl::OnPauseButtion, this);
  m_staticText9 = new wxStaticText(this, wxID_ANY, wxT("暂停"),
                                   wxDefaultPosition, wxDefaultSize, 0);
  m_staticText9->Wrap(-1);
  fgSizer26->Add(m_staticText9, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

  bSizer121->Add(fgSizer26, 0, wxEXPAND, 5);

  fgSizer1->Add(bSizer121, 1, wxEXPAND, 5);

  wxBoxSizer* bSizer122;
  bSizer122 = new wxBoxSizer(wxVERTICAL);

  wxFlexGridSizer* fgSizer27;
  fgSizer27 = new wxFlexGridSizer(0, 2, 0, 0);
  fgSizer27->SetFlexibleDirection(wxBOTH);
  fgSizer27->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

  m_bpButton14 =
      new wxBitmapButton(this, wxID_ANY, wxNullBitmap, wxDefaultPosition,
                         wxDefaultSize, wxBU_AUTODRAW | 0);

  m_bpButton14->SetBitmap(wxBitmap(wxT("./uidata/end2.png"),
                                   wxBITMAP_TYPE_ANY));
  m_bpButton14->SetBitmapMargins(wxSize(5, 5));
  fgSizer27->Add(m_bpButton14, 0, wxALL, 5);
  m_bpButton14->Bind(wxEVT_BUTTON, &AboutFrameImpl::OnTerminationButtion, this);
  m_staticText10 = new wxStaticText(this, wxID_ANY, wxT("结束"),
                                    wxDefaultPosition, wxDefaultSize, 0);
  m_staticText10->Wrap(-1);
  fgSizer27->Add(m_staticText10, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

  bSizer122->Add(fgSizer27, 0, wxEXPAND, 5);

  fgSizer1->Add(bSizer122, 1, wxEXPAND, 5);

  bSizer32->Add(fgSizer1, 0, wxEXPAND, 5);

  wxBoxSizer* bSizer181;
  bSizer181 = new wxBoxSizer(wxVERTICAL);

  m_staticText147 = new wxStaticText(this, wxID_ANY, wxT("\n"),
                                     wxDefaultPosition, wxDefaultSize, 0);
  m_staticText147->Wrap(-1);
  bSizer181->Add(m_staticText147, 0, wxALIGN_CENTER_HORIZONTAL, 5);

  bSizer32->Add(bSizer181, 0,
                wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 5);

  this->SetSizer(bSizer32);
  this->Layout();

  this->Centre(wxBOTH);
}

void  AboutFrameImpl::OnStartButtion(wxCommandEvent& WXUNUSED(event)) {
  socket_->Start();
}
void  AboutFrameImpl::OnPauseButtion(wxCommandEvent& WXUNUSED(event)) {
  socket_->Pause();
}
void  AboutFrameImpl::OnTerminationButtion(wxCommandEvent& WXUNUSED(event)) {
  socket_->Termination();
}

void AboutFrameImpl::OnChangeVelocityButtion(wxCommandEvent& WXUNUSED(event)) {

  double velocity = 0;
  velocity_text_ctrl->GetValue().ToDouble(&velocity);
  ChangVelocityMessage message{};
  message.velocity = velocity * velocity_factor;
  message.message_header.flag = 0x5a5a;
  message.message_header.message_id = CHANG_VELOCITY_MESSAGE_ID;
  message.message_header.len = sizeof(message);
  message.message_header.source_device_id = DevID::DevID_USV_MAP;
  message.message_header.destination_device_id = DevID::DevID_USV_AC;
  char buffer[1024];
  memcpy_s(buffer, sizeof(message), &message, sizeof(message));
  if (socket_) {
    wxIPV4address main_control_address;
    main_control_address.Hostname("192.168.1.161");
    main_control_address.Service(29001);
    socket_->SendTo(main_control_address,buffer, sizeof(message));
  }
}

void AboutFrameImpl::OnLinkHelp(wxHyperlinkEvent& event) {
#ifdef __WXGTK__
  wxString testFile = wxString::Format("/%s/doc/help_en_US.html",
                                       g_Platform->GetSharedDataDir().c_str());
  if (!::wxFileExists(testFile)) {
    wxString msg = _("OpenCPN Help documentation is not available locally.");
    msg += _T("\n");
    msg +=
        _("Would you like to visit the opencpn.org website for more "
          "information?");

    if (wxID_YES ==
        OCPNMessageBox(NULL, msg, _("OpenCPN Info"), wxYES_NO | wxCENTER, 60)) {
      wxLaunchDefaultBrowser(_T("https://opencpn.org"));
    }
  } else
#endif
  {
   
  }
}

void AboutFrameImpl::OnLinkLicense(wxHyperlinkEvent& event) {
  Layout();
}

void AboutFrameImpl::OnLinkAuthors(wxHyperlinkEvent& event) {
  Layout();
}

void AboutFrameImpl::AboutFrameOnActivate(wxActivateEvent& event) {
  Layout();
}
void AboutFrameImpl::AboutFrameOnClose(wxCloseEvent& event) {
  Hide();
  SetSize(GetMinSize());
  Centre();
  event.Veto();
}
