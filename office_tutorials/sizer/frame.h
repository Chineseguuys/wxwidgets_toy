#include <wx/wx.h>

class MyFrame : public wxFrame {
public:
    MyFrame (const wxString& title);

    void OnQuit(wxCommandEvent& evt);
    void OnAbout(wxCommandEvent& evt);
    void OnSize(wxSizeEvent& evt);
    void OnButtonOK(wxCommandEvent& evt);
    void OnStaticBoxSizer(wxCommandEvent &evt);
    void OnGridSizer(wxCommandEvent &evt);
    void OnFlexGridSizer(wxCommandEvent &evt);
    void OnGridBagSizer(wxCommandEvent &evt);


private:
    DECLARE_EVENT_TABLE()
};