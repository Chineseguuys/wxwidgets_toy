#include <wx/wx.h>
#include "frame.h"

/**
 * @brief cross-platform GUI programming with wxwidgets chapter 7
 */

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};


bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame(wxT("Minimal wxWidgets APP"));
    frame->Show(true);
    frame->ShowTip();

    return true;
}

DECLARE_APP(MyApp);
IMPLEMENT_APP(MyApp);