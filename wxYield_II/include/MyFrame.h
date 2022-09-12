#ifndef _MY_FRAME_H_
#define _MY_FRAME_H_

#include <wx/wx.h>
#include <chrono>
#include <memory>
#include <ChunkedSort.h>

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    virtual ~MyFrame() {}

private:
    wxButton        *button;
    wxButton        *otherButton;
    wxStaticText    *label;
    wxGauge         *progressBar;
    std::unique_ptr<ChunkedSort<int> >      sortOp;
    std::chrono::steady_clock::time_point   startTime;

private:
    void OnButtonClick(wxCommandEvent& evt);
    void OnClose(wxCloseEvent& evt);
    void OnIdel(wxIdleEvent& evt);
};

#endif /* _MY_FRAME_H_ */