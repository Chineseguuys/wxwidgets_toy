#ifndef _MY_FLEXGRIDSIZER_H_
#define _MY_FLEXGRIDSIZER_H_

#include <wx/wx.h>

#define FLEX_ID_BUTTON1      6201
#define FLEX_ID_BUTTON2      6202
#define FLEX_ID_BUTTON3      6203
#define FLEX_ID_BUTTON4      6204
#define FLEX_ID_BUTTON5      6205
#define FLEX_ID_BUTTON6      6206

class MyFlexGridSizer : public wxDialog {
public:
    MyFlexGridSizer(wxWindow *parent, wxWindowID id, const wxString &title);
};

#endif /* _MY_FLEXGRIDSIZER_H_ */