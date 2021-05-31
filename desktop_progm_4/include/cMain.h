#include <wx/wx.h>

#include "cEditorFrame.h"

class cMain : public wxMDIParentFrame {
public:
    cMain();
    ~cMain();
public:

private:
    wxToolBar *m_ToolBar = nullptr;
    wxMenuBar *m_MenuBar = nullptr;

    void OnMenuNew(wxCommandEvent &evt);
    void OnMenuOpen(wxCommandEvent &evt);
    void OnMenuSave(wxCommandEvent &evt);
    void OnMenuExit(wxCommandEvent &evt);

    // 点击 toolbar 的按钮的时候需要出发的事件
    void OnSelectColour(wxCommandEvent &evt);

    wxDECLARE_EVENT_TABLE(); 
};