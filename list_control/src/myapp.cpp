#include "myapp.h"
#include "myframe.h"


bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("hello world", wxPoint(450, 250), wxSize(800, 600));
    frame->Show();
    return true;
}

