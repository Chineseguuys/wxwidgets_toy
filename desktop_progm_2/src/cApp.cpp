#include "cApp.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp()  {

}

cApp::~cApp() {

}

bool cApp::OnInit() {
    m_frame1 = new cMain();
    m_frame1->Show();
    return true;
}

int cApp::OnExit() {
    //delete m_frame1; // 这个没有必要delete wx widgets 会自动进行 delete 操作
    printf("main frame exits\n");
    return 0;
}