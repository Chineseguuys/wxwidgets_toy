#include <wx/wx.h>
#include "MyFrame.h"
#include "drawingcanvas.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);


bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame("WITH-GTK", wxPoint(50, 50), wxDefaultSize);
    frame->Show();

    return true;
}