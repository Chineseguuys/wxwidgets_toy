#include "frame.h"
#include "loupe.xpm"
#include "mydialog.h"

#define wxID_MESSAGEDIALOG          6002
#define wxID_PROCESSDIAPLG          6003

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT,     MyFrame::OnQuit)
    EVT_MENU(wxID_ABOUT,    MyFrame::OnAbout)
    EVT_MENU(wxID_MESSAGEDIALOG,    MyFrame::OnMessageDialog)
    EVT_MENU(wxID_PROCESSDIAPLG,    MyFrame::OnProcessDialog)
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

void MyFrame::ShowTip() {
    static size_t s_index = (size_t)-1;
    if ( s_index == (size_t)-1 )
    {
        // randomize...
        srand(time(NULL));
        // ...and pick a new tip
        s_index = rand() % 5;
    }

    // pass a tips file and tip index
    wxTipProvider *tipProvider =
    wxCreateFileTipProvider(wxT("./resources/tips.txt"), s_index);
    m_showAtStartup = wxShowTip(this, tipProvider, true);
    delete tipProvider;
}

void MyFrame::OnQuit(wxCommandEvent& event)
{
    // Destroy the frame
    Close();
}

void MyFrame::OnMessageDialog(wxCommandEvent &evt) {
    wxMessageDialog dialog( NULL, wxT("Do you want exit?"),
    wxT("Message box text"),
    wxNO_DEFAULT|wxYES_NO|wxCANCEL|wxICON_ERROR);
    switch ( dialog.ShowModal() )
    {
        case wxID_YES:
            wxLogStatus(wxT("You pressed \"Yes\""));
            Close();
        break;
        case wxID_NO:
            wxLogStatus(wxT("You pressed \"No\""));
        break;
        case wxID_CANCEL:
            wxLogStatus(wxT("You pressed \"Cancel\""));
        break;
        default:
        wxLogError(wxT("Unexpected wxMessageDialog return code!"));
    }
}

void MyFrame::OnProcessDialog(wxCommandEvent& evt) {
    static const int max = 20;
    wxProgressDialog dialog(
        wxT("Progress dialog example"), wxT("An informative message"), max,
        // range
        this,
        // parent
        wxPD_CAN_ABORT | wxPD_APP_MODAL | wxPD_ELAPSED_TIME |
            wxPD_ESTIMATED_TIME | wxPD_REMAINING_TIME);
    bool cont = true;
    for ( int i = 0; i <= max; i++ )
    {
        wxSleep(1);
        if ( i == max )
            cont = dialog.Update(i, wxT("That’s all, folks!"));
        else if ( i == max / 2 )
            cont = dialog.Update(i, wxT("Only a half left(very long message) !"));
        else
            cont = dialog.Update(i);
        if ( !cont )
        {
            // 点击 cancel 之后，弹出对话框
            if ( wxMessageBox(wxT("Do you really want to cancel?"),
            wxT("Progress dialog question"),
            wxYES_NO | wxICON_QUESTION) == wxYES )
                break;
            dialog.Resume();
        }
    }
    if ( !cont )
        wxLogStatus(wxT("Progress dialog aborted!"));
    else
        wxLogStatus(wxT("Countdown from %d finished"), max);
}

MyFrame::MyFrame(const wxString& title) 
    : wxFrame(NULL, wxID_ANY, title) {
    SetIcon(wxIcon(_711e833533f4ed2e28c87eeb045ee4dWr9CPUn3NCste8jg));
    wxMenu* fileMenu = new wxMenu;
    wxMenu* helpMenu = new wxMenu;
    

    helpMenu->Append(wxID_ABOUT, wxT("&About...\tF1"),
        wxT("Show about dialog"));
    helpMenu->Append(wxID_MESSAGEDIALOG, wxT("&message...\tF2"),
                     wxT("show message dialog"));
    helpMenu->Append(wxID_PROCESSDIAPLG, wxT("&process...\tF3"),
                     wxT("show preocess dialog"));


    fileMenu->Append(wxID_EXIT, wxT("&Exit\tAlt-X"), wxT("Quit this program"));

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