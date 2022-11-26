#ifndef _MY_APP_H_
#define _MY_APP_H_

#include <wx/wx.h>
#include <wx/app.h>

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

DECLARE_APP(MyApp);

#endif /* _MY_APP_H_ */