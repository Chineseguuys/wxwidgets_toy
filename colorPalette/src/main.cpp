#include "MyApp.h"
#include "MyFrame.h"
#include <thread>

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    std::cout << "0. APP thread " << std::this_thread::get_id() << std::endl;

    MyFrame *frame = new MyFrame("Color Palette", wxPoint(50, 50), wxSize(800, 600));
    frame->Show();

    return true;
}

