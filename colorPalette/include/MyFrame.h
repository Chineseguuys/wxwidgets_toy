#ifndef _MY_FRAME_H_
#define _MY_FRAME_H_

#include <wx/wx.h>
#include "MyApp.h"

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    virtual ~MyFrame() {}

protected:
    enum COLOR_COMPONENT {
        Y_COMPONENT,
        U_COMPONENT,
        V_COMPONENT
    };

    unsigned int mY;
    unsigned int mU;
    unsigned int mV;

    wxTextCtrl* mYValue;
    wxTextCtrl* mUValue;
    wxTextCtrl* mVValue;
    wxPanel* mColorPanel;

private:
    void setColorComponentValue(COLOR_COMPONENT comp, const std::string& num, int len);
    void onTextCtrlChanged(wxCommandEvent& evt);

    static bool isDigital(const std::string& numStr);
    static void yuv2rgb(unsigned int y, unsigned int cr, unsigned cb, unsigned int* rgb);
};

#endif /* _MY_FRAME_H_ */