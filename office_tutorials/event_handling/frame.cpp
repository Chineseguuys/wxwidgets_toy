#include "frame.h"
#include "mondrian.xpm"

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT,     MyFrame::OnQuit)
    EVT_MENU(wxID_ABOUT,    MyFrame::OnAbout)
    EVT_SIZE(               MyFrame::OnSize)
    EVT_BUTTON(wxID_OK,     MyFrame::OnButtonOK)
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

void MyFrame::OnSize(wxSizeEvent& evt) {
    //wxSize size = evt.GetSize();
    //printf("windows size changed to (%d, %d)\n", size.x, size.y);
}

void MyFrame::OnButtonOK(wxCommandEvent& evt) {
    printf("Button has been clicked\n");
}


MyFrame::MyFrame(const wxString& title) 
    : wxFrame(NULL, wxID_ANY, title) {
    SetIcon(wxIcon(mondrian_xpm));
    wxMenu* fileMenu = new wxMenu;
    wxMenu* helpMenu = new wxMenu;
    

    helpMenu->Append(wxID_ABOUT, wxT("&About...\tF1"),
        wxT("Show about dialog"));
    fileMenu->Append(wxID_EXIT, wxT("&Exit\tAlt-X"),
        wxT("Quit this program"));

    wxButton* button = new wxButton(this, wxID_OK, wxT("OK"), wxPoint(200, 200));
    //wxWindow* win = new wxWindow(this, wxID_ANY, wxPoint(100, 100), wxSize(50, 50), wxSUNKEN_BORDER);

    wxPanel* panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(200, 200));

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