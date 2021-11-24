#include "frame.h"
#include "mydialog.h"
#include "logs.h"
#include <stdio.h>

/* https://wiki.wxwidgets.org/Writing_Your_First_Application-Using_The_WxTextCtrl */

#define wxID_OPEN_FILE_DIALOG   6001

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT,                 MyFrame::OnQuit)
    EVT_MENU(wxID_OPEN_FILE_DIALOG,     MyFrame::OnOpenFile)
END_EVENT_TABLE()


void MyFrame::OnQuit(wxCommandEvent& event)
{
    // Destroy the frame
    Close();
}

void MyFrame::OnOpenFile(wxCommandEvent& evt) {
    wxString caption = wxT("Choose a file");
    wxString wildcard = wxT("CPP files (*.cpp)|*.cpp|H files (*.h)|*.h");
    wxString defaultDir = wxT("/home/yjh/");
    wxString defaultFilename = wxEmptyString;

    wxFileDialog dialog(this, caption, defaultDir, defaultFilename, wildcard,
                        wxFD_DEFAULT_STYLE);
    if (dialog.ShowModal() == wxID_OK) {
        this->file_path = dialog.GetPath();
        this->file_name = dialog.GetFilename();
        int filterIndex = dialog.GetFilterIndex();
        ALOG("[%s:L%d]file name is %s, file path is %s\n", __FUNCTION__,
               __LINE__,
               static_cast<const char *>(this->file_name.mb_str(wxConvUTF8)),
               static_cast<const char *>(this->file_path.mb_str(wxConvUTF8)));
        this->main_edit_box->LoadFile(this->file_path);
    }
}

MyFrame::MyFrame(const wxString& title) 
    : wxFrame(NULL, wxID_ANY, title) {
    wxMenu* fileMenu = new wxMenu;
    wxMenu* helpMenu = new wxMenu;

    fileMenu->Append(wxID_EXIT, wxT("&Exit\tAlt-X"), wxT("Quit this program"));
    fileMenu->Append(wxID_OPEN_FILE_DIALOG, wxT("&Open File\tAlt-O"),
                     wxT("Open File"));
    
    // Now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(helpMenu, wxT("&Help"));
    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);

    this->main_edit_box = new wxTextCtrl(
        this, TEXT_Main, wxT("Please Open a File, or Create a New File!"),
        wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH,
        wxDefaultValidator, wxTextCtrlNameStr);

    Maximize();

    // Create a status bar just for fun
    CreateStatusBar(2);
    SetStatusText(wxT("Welcome to wxWidgets!"));
}