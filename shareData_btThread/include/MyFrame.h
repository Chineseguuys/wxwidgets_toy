#ifndef _MY_FRAME_H_
#define _MY_FRAME_H_

#include <wx/wx.h>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include "MyApp.h"
#include "visualGrid.h"

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    virtual ~MyFrame() {}

private:
    wxButton        *button;
    wxGauge         *progressBar;
    VisualGrid      *mGrid;

    // onProcessing 现在只在主线程的 event loop 当中进行使用，不存在线程间的访问，可以移除 atomic
    std::atomic<bool> onProcessing{false};
    std::atomic<bool> quitRequested{false};

    std::vector<float> mSharedData;
    std::mutex mDataMutex;

    std::thread mBackGroundThread;
    wxTimer* mGridRefleshTimer;
    static constexpr int GRID_REFLESHTIMER_ID = 6621;

private:
    void OnButtonClick(wxCommandEvent& evt);
    void OnClose(wxCloseEvent& evt);
    void BackGroundTask();
    void RandomizeSharedData();
};

#endif /* _MY_FRAME_H_ */