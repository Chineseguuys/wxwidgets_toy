#include "frame.h"
#include "cut.xpm"
#include "paste.xpm"
#include "copy.xpm"
#include "mondrian.xpm"
#include <wx/notebook.h>

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

    // Now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(helpMenu, wxT("&Help"));
    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
    // Create a status bar just for fun
    CreateStatusBar(2);
    SetStatusText(wxT("Welcome to wxWidgets!"));

    // notebook 窗口
    wxNotebook* notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxSize(500, 400));
    // 不知道为什么有 bug。干脆不用图标了
    // wxImageList 要求所有的图标的大小要一致，但是即使是一致的，还是报错了，不知道是什么原因
    //wxImageList* imageList = new wxImageList(16, 16, true, 3);
    //imageList->Add(wxIcon(copy_xpm));
    //imageList->Add(wxIcon(copy_xpm));
    //imageList->Add(wxIcon(copy_xpm));

    wxPanel* windows1 = new wxPanel(notebook, wxID_ANY);
    wxPanel* windows2 = new wxPanel(notebook, wxID_ANY);
    wxPanel* windows3 = new wxPanel(notebook, wxID_ANY);

    notebook->AddPage(windows1, wxT("Tab One"), true);
    notebook->AddPage(windows2, wxT("Tab Two"), true);
    notebook->AddPage(windows3, wxT("Tab Three"), true);
}