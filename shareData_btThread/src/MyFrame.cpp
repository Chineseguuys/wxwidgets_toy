#include "MyFrame.h"
#include <random>

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size) 
    : wxFrame(nullptr, wxID_ANY, title, pos, size), mSharedData(50000) {
    // 自由生成一组随机浮点数列
    this->RandomizeSharedData();
    this->CreateStatusBar(1);

    std::cout << "1. Current thread " << std::this_thread::get_id() << std::endl;

    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    wxPanel *panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    wxSizer *panelSizer = new wxBoxSizer(wxHORIZONTAL);

    button = new wxButton(panel, wxID_ANY, "Start");
    button->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);

    progressBar = new wxGauge(panel, wxID_ANY, 1000, wxDefaultPosition, this->FromDIP(wxSize(320, 20)));

    panelSizer->Add(button, 0, wxALIGN_CENTRE | wxRIGHT, this->FromDIP(5));
    panelSizer->Add(progressBar, 0, wxALIGN_CENTER);

    this->mGrid = new VisualGrid(   this, wxID_ANY, wxDefaultPosition, this->FromDIP(wxSize(1000, 800)), 250, 
                                    this->mSharedData, this->mDataMutex);

    panel->SetSizer(panelSizer);

    sizer->Add(panel, 0, wxEXPAND | wxALL, this->FromDIP(5));
    sizer->Add(this->mGrid, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, this->FromDIP(5));

    this->SetSizerAndFit(sizer);

    this->Bind(wxEVT_CLOSE_WINDOW, &MyFrame::OnClose, this);

    this->SetStatusText("Click Start.", 0);

    // 设置 grid 刷新的定时器
    this->mGridRefleshTimer = new wxTimer(this, GRID_REFLESHTIMER_ID);
    this->Bind(wxEVT_TIMER, [this](wxTimerEvent& ) {
#ifdef DEBUG_COMPILER
        this->mGrid->dbgRefReqs++;
#endif /* DEBUG_COMPILER */
        this->mGrid->Refresh();
    }, GRID_REFLESHTIMER_ID );

    this->mGridRefleshTimer->Start(150);    // 每 150ms 刷新一次
}

void MyFrame::OnButtonClick(wxCommandEvent& evt) {
    if (this->onProcessing) {
        printf("on Processing!\n");
        return;
    }

    this->onProcessing = true;

    std::cout << "2. Current thread " << std::this_thread::get_id() << std::endl;

    this->mBackGroundThread = std::thread{&MyFrame::BackGroundTask, this};
    // 新创建的线程设置为 detach, 那么当前的消息的处理可以马上返回，不会卡主线程的其他渲染流程
}

void MyFrame::OnClose(wxCloseEvent& evt) {
    if (this->onProcessing) {
        // 如果子线程还在处理数据，主线程现拒绝此次的关闭指令，之后告知子线程需要退出
        evt.Veto();
        this->quitRequested = true;
    }
    else {
        this->Destroy();
    }
}


void MyFrame::BackGroundTask() {
    std::cout << "3. Current thread " << std::this_thread::get_id() << std::endl;

    int n = this->mSharedData.size();

    wxGetApp().CallAfter([this, n]() {
        this->SetStatusText(wxString::Format("Sorting the array of %d elements...", n));
        this->Layout();
    });

    auto timeStart = std::chrono::steady_clock::now();

    for (int i = 0; i < n - 1; ++i) {
        // progressBar 的更新不能放在当前的线程当中，应该放在独立的线程当中来进行，使用下面的函数来告诉 wxwidget 主线程，将下面的任务插入到
        // 主线程的 event loop 当中去
        // 在外层循环当中来做通知， 内层做通知消息过于频繁
        wxGetApp().CallAfter([this, i, n]() {
            this->progressBar->SetValue(i * this->progressBar->GetRange() / (n - 2));
        });

        std::lock_guard<std::mutex> gLock(this->mDataMutex);

        for (int j = 0; j < n - i - 1; ++j) {
            if (this->mSharedData[j] > this->mSharedData[j + 1]) {
                std::swap(this->mSharedData[j], this->mSharedData[j + 1]);
            }
        }

        //  主线程当中点击了关闭窗口的按钮，状态变量被设置为 true
        if (this->quitRequested) {
            // 同样的，窗口的销毁也不可以在当前的线程中进行，需要通知主线程执行
            wxGetApp().CallAfter([this]() {
                this->mBackGroundThread.join();
                // 状态变量的修改放到主线程的 event loop 当中，通过 event loop 的顺序执行的特点可以排除一些潜在的线程间访问的冲突
                this->onProcessing = false;
                this->quitRequested = false;
                this->Destroy();
            });
            // 退出当前线程
            return;
        }
    }

    auto timeEnd = std::chrono::steady_clock::now();
    auto timeDuration = timeEnd - timeStart;

    auto frontNum = this->mSharedData.front();
    // 自线程执行的结果通知主线程
    wxGetApp().CallAfter([this, frontNum, timeDuration]() {
        this->mBackGroundThread.join();
        this->progressBar->SetValue(this->progressBar->GetRange());
        this->SetStatusText(wxString::Format("The first number is: %f, using time %.2f", frontNum, 
            std::chrono::duration<double, std::milli>(timeDuration).count()));

        this->Layout();
        this->onProcessing = false;
    });
}

void MyFrame::RandomizeSharedData() {
    std::random_device rad_device;
    std::mt19937 gen(rad_device());
    std::uniform_real_distribution<> distr(0, 1);

    for (int idx = 0; idx < this->mSharedData.size(); ++idx) {
        this->mSharedData[idx] = distr(gen);
    }
}