#ifndef _FRAME_H_
#define _FRAME_H_

#include <wx/wx.h>
#include <wx/progdlg.h>
#include <wx/tipdlg.h>

class MyFrame : public wxFrame {
public:
    MyFrame (const wxString& title);

    void OnQuit(wxCommandEvent& evt);
    void OnAbout(wxCommandEvent& evt);
    void ShowTip();
    void OnMessageDialog(wxCommandEvent &evt);
    void OnProcessDialog(wxCommandEvent &evt);

private:
    bool m_showAtStartup;

private:
  DECLARE_EVENT_TABLE()
};


#endif /* _FRAME_H_ */