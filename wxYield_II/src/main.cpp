#include <wx/wx.h>
#include <MyFrame.h>

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};


wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MyFrame *frame = new MyFrame("Hello World", wxPoint(50, 50), wxDefaultSize);
    frame->Show();

    return true;
}


