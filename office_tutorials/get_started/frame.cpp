#include "frame.h"
#include "7513466.xpm"

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
END_EVENT_TABLE()


void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg;
    msg.Printf(wxT("Hello and welcome to %s"),
    wxVERSION_STRING);
    wxMessageBox(msg, wxT("About Minimal"),
        wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnQuit(wxCommandEvent& event)
{
    // Destroy the frame
    Close();
}


MyFrame::MyFrame(const wxString& title) 
    : wxFrame(NULL, wxID_ANY, title) {
    SetIcon(wxIcon(_f816d0670624058de4e5f7feef247deGdrpRUtMe7H98Mic));
    wxMenu* fileMenu = new wxMenu;
    wxMenu* helpMenu = new wxMenu;

    helpMenu->Append(wxID_ABOUT, wxT("&About...\tF1"),
        wxT("Show about dialog"));
    fileMenu->Append(wxID_EXIT, wxT("&Exit\tAlt-X"),
        wxT("Quit this program"));

    // Now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(helpMenu, wxT("&Help"));
    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
    // Create a status bar just for fun
    CreateStatusBar(2);
    SetStatusText(wxT("Welcome to wxWidgets!"));
}