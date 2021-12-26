#ifndef _FRAME_H_
#define _FRAME_H_

#include <wx/wx.h>

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void deal_with_10base(wxCommandEvent &evt);
    void deal_with_2base(wxCommandEvent &evt);
    void deal_with_8base(wxCommandEvent &evt);
    void deal_with_16base(wxCommandEvent &evt);

private:
    wxTextCtrl *text_ctrl_refs[4];

private:
    DECLARE_EVENT_TABLE()
};

enum {
    TEXT_CTRL_ID_BEGIN = wxID_HIGHEST + 1,
    TEXT_CTRL_ID_BASE2,
    TEXT_CTRL_ID_BASE8,
    TEXT_CTRL_ID_BASE10,
    TEXT_CTRL_ID_BASE16,
    TEXT_CTRL_ID_END,
};

enum {
    FRAME_ID_BEGIN = TEXT_CTRL_ID_END + 1,
    FRAME_ID_ONE,
};

#endif /* _FRAME_H_ */