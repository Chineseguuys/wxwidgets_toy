#include <wx/wx.h>
#include <wx/clipbrd.h>
#include <wx/dataobj.h>

class cMain : public wxFrame {
public:
    cMain();
    ~cMain();
public:
    //wxButton *m_btn1 = nullptr;
    wxTextCtrl *m_tc1 = nullptr;
    wxTextCtrl *m_list1 = nullptr;
    wxPanel *m_left_panel = nullptr;

    wxStatusBar *m_status_bar = nullptr;

    void OnButtonClicked(wxCommandEvent &evt);
    void OnTextCtrl_TextChanged(wxCommandEvent &evt);


    wxDECLARE_EVENT_TABLE(); 
};