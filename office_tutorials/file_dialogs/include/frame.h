#ifndef _FRAME_H_
#define _FRAME_H_

#include <wx/wx.h>
#include <wx/filedlg.h>
#include "mytypes.h"

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString &title);

private:
    void Newfile(wxCommandEvent &evt);
    void Closefile(wxCommandEvent &evt);
    void Savefile(wxCommandEvent &evt);
    void SavefileAs(wxCommandEvent &evt);
    void OnQuit(wxCommandEvent &evt);
    void OnOpenFile(wxCommandEvent &evt);

private:
    wxString    file_path;
    wxString    file_name;
    wxTextCtrl *main_edit_box;

private:
    DECLARE_EVENT_TABLE()
};

enum {
    TEXT_Main =
        wxID_HIGHEST + 1, // declares an id which will be used to call our button
    MENU_New,
    MENU_Open,
    MENU_Close,
    MENU_Save,
    MENU_SaveAs,
    MENU_Quit
};

#endif /* _FRAME_H_ */