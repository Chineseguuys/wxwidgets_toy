#include "myapp.h"
#include "myframe.h"


bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("hello world", wxPoint(450, 250), wxSize(800, 600));
    frame->Show();
    /**
     * 为了进入事件循环，这里的值必须是 true
    */
    return true;
}

