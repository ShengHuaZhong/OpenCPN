/***************************************************************************
 *
 * Project:  OpenCPN
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

#pragma once
#ifndef _ABOUTFRAMEIMPL_H_
#define _ABOUTFRAMEIMPL_H_

#include "AboutFrame.h"
#include "unmanned_vessel_socket.h"
#include "unmanned_control_message.h"

class PathtrackingDialog : public wxDialog {
public:
  PathtrackingDialog(UnmannedVesselSocket* socket, wxWindow* parent,
    wxWindowID id = wxID_ANY,
    const wxString& title = wxT("路径跟踪"),
    const wxPoint& pos = wxDefaultPosition,
    const wxSize& size = wxDefaultSize,
    long style = wxDEFAULT_DIALOG_STYLE);
  ~PathtrackingDialog();

protected:
  void OnButton(wxCommandEvent& WXUNUSED(event));

private:
  wxStaticText* m_staticText102;
  wxStaticText* m_staticText98;
  wxTextCtrl* longtitude_text_ctrl;
  wxStaticText* m_staticText981;
  wxTextCtrl* latitude_text_ctrl;
  wxButton* ok_button;
  UnmannedVesselSocket* socket_;
  wxDECLARE_EVENT_TABLE();
};
///////////////////////////////////////////////////////////////////////////
/// Class MyDialog6 (Circular rotation)
///////////////////////////////////////////////////////////////////////////////
class CircularRotationSettingDialog : public wxDialog {
private:
  wxDECLARE_EVENT_TABLE();
protected:

  void OnOKButton(wxCommandEvent& WXUNUSED(event));
  void OnClockWiseButton(wxCommandEvent& WXUNUSED(event));
  void OnAntiClockWiseButton(wxCommandEvent& WXUNUSED(event));

  wxStaticText* m_staticText105;
  wxStaticText* m_staticText108;
  wxTextCtrl* longitude_text_ctrl;
  wxStaticText* m_staticText109;
  wxTextCtrl* latitude_text_ctrl;
  wxStaticText* m_staticText106;
  wxStaticText* m_staticText113;
  wxTextCtrl* m_textCtrl21;
  wxStaticText* radius_static_text;
  wxTextCtrl* radius_text_ctrl;
  wxButton* clockwise_button;
  wxButton* anti_clockwise_button;
  wxButton* ok_button;
  FixGyrationMessage message_;
  UnmannedVesselSocket* socket_;
public:
  CircularRotationSettingDialog(UnmannedVesselSocket* socket, wxWindow* parent, wxWindowID id = wxID_ANY,
    const wxString& title = wxT("定圆回转"),
    const wxPoint& pos = wxDefaultPosition,
    const wxSize& size = wxDefaultSize,
    long style = wxDEFAULT_DIALOG_STYLE);
  ~CircularRotationSettingDialog();
};

class FixPointSettingDialog : public wxDialog {
private:
  // wxDECLARE_EVENT_TABLE();
protected:

  wxStaticText* m_staticText105;
  wxStaticText* m_staticText108;
  wxTextCtrl* longitude_text_ctrl;
  wxStaticText* m_staticText109;
  wxTextCtrl* latitude_text_ctrl;
  wxStaticText* m_staticText106;
  wxStaticText* m_staticText113;
  wxTextCtrl* radius_text_ctrl;
  wxStaticText* m_staticText129;
  wxStaticText* m_staticText132;
  wxTextCtrl* velocity_text_ctrl;
  wxStaticText* m_staticText130;
  wxButton* m_button94;
  UnmannedVesselSocket* socket_;
  void OnOKButton(wxCommandEvent& WXUNUSED(event));

public:
  FixPointSettingDialog(UnmannedVesselSocket* socket, wxWindow* parent, wxWindowID id = wxID_ANY,
    const wxString& title = wxT("定点保持"),
    const wxPoint& pos = wxDefaultPosition,
    const wxSize& size = wxDefaultSize,
    long style = wxDEFAULT_DIALOG_STYLE);
  ~FixPointSettingDialog();
};

class AboutFrameImpl : public AboutFrame {
protected:
  void AboutFrameOnClose(wxCloseEvent& event);
  void OnLinkDonate(wxHyperlinkEvent& event) { event.Skip(); }
  void OnLinkGetInvolved(wxHyperlinkEvent& event) { event.Skip(); }
  void OnLinkLogfile(wxHyperlinkEvent& event) { event.Skip(); }
  void OnLinkConfigfile(wxHyperlinkEvent& event) { event.Skip(); }
  void OnLinkHelp(wxHyperlinkEvent& event);
  void OnLinkLicense(wxHyperlinkEvent& event);
  void OnLinkAuthors(wxHyperlinkEvent& event);
  void AboutFrameOnActivate(wxActivateEvent& event);
  void OnStartButtion(wxCommandEvent& WXUNUSED(event));
  void OnPauseButtion(wxCommandEvent& WXUNUSED(event));
  void OnTerminationButtion(wxCommandEvent& WXUNUSED(event));
  void OnChangeVelocityButtion(wxCommandEvent& WXUNUSED(event));
public:
  ~AboutFrameImpl(){};

  AboutFrameImpl(UnmannedVesselSocket* socket, wxWindow* parent, wxWindowID id = wxID_ANY,
                 const wxString& title = _("控制界面"),
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxSize(360, 500),
                 long style = wxCAPTION | wxCLOSE_BOX |
                              wxFRAME_FLOAT_ON_PARENT | wxFRAME_NO_TASKBAR |
                              wxRESIZE_BORDER | wxTAB_TRAVERSAL);

private:
  void MyDlg5(wxCommandEvent& event);
  void MyDlg6(wxCommandEvent& event);
  void MyDlg7(wxCommandEvent& event);

  wxButton* m_button7;
  wxButton* m_button8;
  wxButton* m_button9;
  wxButton* change_velocity_button;
  wxButton* m_button18;
  wxTextCtrl* velocity_text_ctrl;
  wxStaticText* m_staticText31;
  wxBitmapButton* m_bpButton11;
  wxStaticText* m_staticText8;
  wxBitmapButton* m_bpButton13;
  wxStaticText* m_staticText9;
  wxBitmapButton* m_bpButton14;
  wxStaticText* m_staticText10;
  wxStaticText* m_staticText147;

  UnmannedVesselSocket* socket_;
  wxDECLARE_EVENT_TABLE();
};

#endif  // _ABOUTFRAMEIMPL_H_
