#ifndef _IPANEL_H_
#define _IPANEL_H_

#include <wx/wx.h>

class MyPanel : public wxPanel {
public:
    MyPanel(wxWindow *parent, wxWindowID id) :
        wxPanel(parent, id) {
    }

protected:
    // 每一个不同的 Panel 拥有自己不同的 layout
    virtual void build_layout() = 0;
};

#endif /*_IPANEL_H_*/