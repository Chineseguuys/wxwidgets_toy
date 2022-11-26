#ifndef _MY_FRAME_H_
#define _MY_FRAME_H_

#include <wx/wx.h>
#include <chrono>
#include <thread>
#include <atomic>
#include "MyApp.h"

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    virtual ~MyFrame() {}

private:
    wxButton        *button;
    wxButton        *otherButton;
    wxStaticText    *label;
    wxGauge         *progressBar;

    // onProcessing 现在只在主线程的 event loop 当中进行使用，不存在线程间的访问，可以移除 atomic
    std::atomic<bool> onProcessing{false};
    std::atomic<bool> quitRequested{false};

    std::thread mBackGroundThread;

private:
    void OnButtonClick(wxCommandEvent& evt);
    void OnClose(wxCloseEvent& evt);
};

#endif /* _MY_FRAME_H_ */