#include <wx/wx.h>
#include "frame.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

bool MyApp::OnInit() {
    MyFrame *frame = new MyFrame("BASE CHANGE", wxDefaultPosition, wxSize(1200, 600));
    frame->SetMinSize(wxSize(600, 400)); // 最小大小，不能比这个更小了
    frame->Show(true);
    return true;
}

DECLARE_APP(MyApp);
IMPLEMENT_APP(MyApp);