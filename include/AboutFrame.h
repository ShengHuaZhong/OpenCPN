///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/hyperlink.h>
#include <wx/scrolwin.h>
#include <wx/html/htmlwin.h>
#if wxUSE_WEBVIEW && defined(HAVE_WEBVIEW)
#include <wx/webview.h>
#endif
#include <wx/panel.h>
#include <wx/frame.h>

#include <wx/bmpbuttn.h>
#include <wx/textctrl.h>
#include <wx/dialog.h>


/////////////////////////////////////////////////////////////////////////////
///// Class MyDialog51 (Speed)
/////////////////////////////////////////////////////////////////////////////////
// class MyDialog51 : public wxDialog
//{
// private:
//	//wxDECLARE_EVENT_TABLE();
// protected:
//	wxTextCtrl* m_textCtrl14;
//	wxStaticText* m_staticText143;
//	wxButton* m_button92;
// public:
//	MyDialog51(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString&
// title = wxT("航速"), const wxPoint& pos = wxDefaultPosition, const wxSize&
// size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE); 	~MyDialog51();
//};

///////////////////////////////////////////////////////////////////////////////
/// Class AboutFrame
///////////////////////////////////////////////////////////////////////////////
class AboutFrame : public wxFrame {
private:
 

protected:

#if wxUSE_WEBVIEW && defined(HAVE_WEBVIEW)
 
#else
  wxHtmlWindow* m_htmlWinHelp;
#endif

  // Virtual event handlers, overide them in your derived class
  virtual void AboutFrameOnActivate(wxActivateEvent& event) { event.Skip(); }
  virtual void AboutFrameOnClose(wxCloseEvent& event) { event.Skip(); }
  virtual void m_btnBackOnButtonClick(wxCommandEvent& event) { event.Skip(); }
  virtual void OnLinkAuthors(wxHyperlinkEvent& event) { event.Skip(); }
  virtual void OnLinkDonate(wxHyperlinkEvent& event) { event.Skip(); }
  virtual void OnLinkGetInvolved(wxHyperlinkEvent& event) { event.Skip(); }
  virtual void OnLinkLogfile(wxHyperlinkEvent& event) { event.Skip(); }
  virtual void OnLinkConfigfile(wxHyperlinkEvent& event) { event.Skip(); }
  virtual void m_htmlWinHelpOnHtmlLinkClicked(wxHtmlLinkEvent& event) {
    event.Skip();
  }
  virtual void OnLinkHelp(wxHyperlinkEvent& event) { event.Skip(); }
  virtual void OnLinkLicense(wxHyperlinkEvent& event) { event.Skip(); }

public:
  AboutFrame(wxWindow* parent, wxWindowID id = wxID_ANY,
             const wxString& title = _("Control Interface"),
             const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxDefaultSize,
             long style = wxCAPTION | wxCLOSE_BOX | wxFRAME_FLOAT_ON_PARENT |
                          wxFRAME_NO_TASKBAR | wxRESIZE_BORDER |
                          wxTAB_TRAVERSAL);

  ~AboutFrame();

protected:

};

enum {
  DIALOGS_MODAL,

};
