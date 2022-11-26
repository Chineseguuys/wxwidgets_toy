#include "MyFrame.h"


MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size) 
    : wxFrame(nullptr, wxID_ANY, title, pos, size) {

    std::cout << "1. Current thread " << std::this_thread::get_id() << std::endl;

    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    wxSizer *centeringSizer = new wxBoxSizer(wxHORIZONTAL);

    wxPanel *panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, this->FromDIP(wxSize(320, 240)));
    wxSizer *panelSizer = new wxBoxSizer(wxVERTICAL);

    label = new wxStaticText(panel, wxID_ANY, "Click Start", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
    progressBar = new wxGauge(panel, wxID_ANY, 1000);

    button = new wxButton(panel, wxID_ANY, "Start");
    button->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);

    otherButton = new wxButton(panel, wxID_ANY, "Dummy Button");

    panelSizer->Add(label, 1, wxEXPAND | wxALL, this->FromDIP(20));
    panelSizer->Add(progressBar, 1, wxEXPAND | wxALL, this->FromDIP(20));
    panelSizer->Add(button, 0, wxALIGN_CENTRE | wxALL, this->FromDIP(5));
    panelSizer->Add(otherButton, 0, wxALIGN_CENTER | wxBottom, this->FromDIP(20));

    panel->SetSizer(panelSizer);

    centeringSizer->Add(panel, 0, wxALIGN_CENTER);
    sizer->Add(centeringSizer, 1, wxALIGN_CENTER);

    this->SetSizerAndFit(sizer);

    this->Bind(wxEVT_CLOSE_WINDOW, &MyFrame::OnClose, this);
}

void MyFrame::OnButtonClick(wxCommandEvent& evt) {
    if (this->onProcessing) {
        printf("on Processing!\n");
        return;
    }

    this->onProcessing = true;

    std::cout << "2. Current thread " << std::this_thread::get_id() << std::endl;

    const auto f = [this]() {

        std::cout << "3. Current thread " << std::this_thread::get_id() << std::endl;

        std::vector<int> arr(50000, 5);
        arr.back() = 3;

        int n = arr.size();

        wxGetApp().CallAfter([this, n]() {
            this->label->SetLabelText(wxString::Format("Sorting the array of %d elements...", n));
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

            for (int j = 0; j < n - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                }
            }

            //  主线程当中点击了关闭窗口的按钮，状态变量被设置为 true
            if (this->quitRequested) {
                // this->onProcessing = false;
                // this->quitRequested = false;

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

        auto frontNum = arr.front();
        // 自线程执行的结果通知主线程
        wxGetApp().CallAfter([this, frontNum, timeDuration]() {
            this->mBackGroundThread.join();

            this->label->SetLabelText(wxString::Format("The first number is: %d, using time %.2f", frontNum, 
                std::chrono::duration<double, std::milli>(timeDuration).count()));

            this->Layout();
            this->onProcessing = false;
        });

        // this->onProcessing = false;
    };

    this->mBackGroundThread = std::thread{f};
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