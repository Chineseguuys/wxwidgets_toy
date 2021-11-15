#ifndef _MY_STATICBOXSIZER_H_
#define _MY_STATICBOXSIZER_H_

#include <wx/wx.h>

#ifndef ID_CHECKBOX
#define ID_CHECKBOX     6101
#endif /* ID_CHECKBOX */

class MyStaticBoxSizer : public wxDialog {
public:
    MyStaticBoxSizer(wxWindow *parent, wxWindowID id, const wxString &title);
};



#endif 