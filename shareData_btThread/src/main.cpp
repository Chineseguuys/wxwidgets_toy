#include <wx/wx.h>
#include <MyFrame.h>
#include "MyApp.h"


wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    std::cout << "0. APP thread " << std::this_thread::get_id() << std::endl;

    MyFrame *frame = new MyFrame("Hello World", wxPoint(50, 50), wxDefaultSize);
    frame->Show();

    return true;
}


