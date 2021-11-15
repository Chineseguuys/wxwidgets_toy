#include "frame.h"
#include "TileBitmap.h"

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT,     MyFrame::OnQuit)
    EVT_MENU(wxID_ABOUT,    MyFrame::OnAbout)
    EVT_MOTION(MyFrame::OnMotion)
    EVT_ERASE_BACKGROUND(MyFrame::OnErase)
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

void MyFrame::OnMotion(wxMouseEvent& event) {
    if (event.Dragging()) 
    {
        wxClientDC dc(this);
        wxPen pen(*wxBLACK, 1);
        dc.SetPen(pen);
        dc.DrawPoint(event.GetPosition());
        dc.SetPen(wxNullPen);
    }
}

void MyFrame::OnErase(wxEraseEvent& event) {
    wxClientDC* clientDC = NULL;
    if (!event.GetDC()) 
        clientDC = new wxClientDC(this);
    
    wxDC* dc = clientDC ? clientDC : event.GetDC();
    wxSize sz = GetClientSize();
    wxApp* theApp = wxTheApp;
    
    //TileBitmap(wxRect(0, 0, sz.x, sz.y), *dc, theApp->GetBackgroundBitmap());    
}


MyFrame::MyFrame(const wxString& title) 
    : wxFrame(NULL, wxID_ANY, title) {
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