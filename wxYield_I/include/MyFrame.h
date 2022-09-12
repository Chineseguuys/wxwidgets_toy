#ifndef _MY_FRAME_H_
#define _MY_FRAME_H_

#include <wx/wx.h>
#include <chrono>

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    virtual ~MyFrame() {}

private:
    wxButton        *button;
    wxButton        *otherButton;
    wxStaticText    *label;
    wxGauge         *progressBar;
    bool            onProcessing = false;
    bool            quitRequested = false;

private:
    void OnButtonClick(wxCommandEvent& evt);
    void OnClose(wxCloseEvent& evt);
};

#endif /* _MY_FRAME_H_ */