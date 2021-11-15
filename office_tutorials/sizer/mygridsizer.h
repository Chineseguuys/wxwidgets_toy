#ifndef _MY_GRID_SIZER_H_
#define _MY_GRID_SIZER_H_

#define ID_BUTTON1      6201
#define ID_BUTTON2      6202
#define ID_BUTTON3      6203
#define ID_BUTTON4      6204
#define ID_BUTTON5      6205
#define ID_BUTTON6      6206

#include <wx/wx.h>

class MyGridSizer : public wxDialog {
public:
    MyGridSizer(wxWindow *parent, wxWindowID id, const wxString &title);
};

#endif /* _MY_GRID_SIZER_H_ */