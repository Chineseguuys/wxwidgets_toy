#include "frame.h"
#include "mondrian.xpm"
#include "mydialog.h"
#include "mystaticboxsizer.h"
#include "mygridsizer.h"
#include "myflexgridsizer.h"
#include "mygridbagsizer.h"

#define wxID_STATICBOXSIZER     6001
#define wxID_GRIDSIZER          6002
#define wxID_FLEXGRIDSIZER      6003
#define wxID_GRIDBAGSIZER       6004

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT,     MyFrame::OnQuit)
    EVT_MENU(wxID_ABOUT,    MyFrame::OnAbout)
    EVT_MENU(wxID_STATICBOXSIZER,   MyFrame::OnStaticBoxSizer)
    EVT_MENU(wxID_GRIDSIZER,        MyFrame::OnGridSizer)
    EVT_MENU(wxID_FLEXGRIDSIZER,    MyFrame::OnFlexGridSizer)
    EVT_MENU(wxID_GRIDBAGSIZER,     MyFrame::OnGridBagSizer)
    EVT_SIZE(               MyFrame::OnSize)
    EVT_BUTTON(wxID_OK,     MyFrame::OnButtonOK)
END_EVENT_TABLE()


void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg;
    msg.Printf(wxT("Hello and welcome to %s"),
    wxVERSION_STRING);
    //wxMessageBox(msg, wxT("About Minimal"),
    //    wxOK | wxICON_INFORMATION, this);
    MyDialog* dialog = new  MyDialog(this, wxID_ANY, "Dialog");
    dialog->Show();
}

void MyFrame::OnStaticBoxSizer(wxCommandEvent &evt) {
    MyStaticBoxSizer *dialog = new MyStaticBoxSizer(this, wxID_ANY, "Dialog");
    dialog->Show();
}

void MyFrame::OnGridSizer(wxCommandEvent &evt) {
    MyGridSizer *dialog = new MyGridSizer(this, wxID_ANY, "Dialog");
    dialog->Show();
}

void MyFrame::OnFlexGridSizer(wxCommandEvent &evt) {
    MyFlexGridSizer *dialog = new MyFlexGridSizer(this, wxID_ANY, "Dialog");
    dialog->Show();
}

void MyFrame::OnGridBagSizer(wxCommandEvent &evt) {
    MyGridBagSizer *dialog = new MyGridBagSizer(this, wxID_ANY, "Dialog");
    dialog->Show();
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
    helpMenu->Append(wxID_STATICBOXSIZER, wxT("&static...\tF2"),
                     wxT("show a static box sizer"));
    helpMenu->Append(wxID_GRIDSIZER, wxT("&gridsizer...\tF3"),
                     wxT("show a grid box sizer"));
    helpMenu->Append(wxID_FLEXGRIDSIZER, wxT("&flexgridsizer...\tF4"),
                     wxT("show a flex grid box sizer"));
    helpMenu->Append(wxID_GRIDBAGSIZER, wxT("&gridbagsizer...\tF5"),
                     wxT("show a grid bag sizer"));
    

    fileMenu->Append(wxID_EXIT, wxT("&Exit\tAlt-X"), wxT("Quit this program"));

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