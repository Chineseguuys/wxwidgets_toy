#ifndef _MYDIALOG_H_
#define _MYDIALOG_H_

#include <wx/wx.h>

class MyDialog : public wxDialog {
public:
    MyDialog(wxWindow *parent, wxWindowID id, const wxString &title);
};

#endif