#include <wx/wx.h>
#include "frame.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};


bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame(wxT("Minimal wxWidgets APP"));

    frame->Show(true);

    return true;
}

DECLARE_APP(MyApp);
IMPLEMENT_APP(MyApp);


