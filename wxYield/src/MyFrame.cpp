#include "MyFrame.h"


MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size) 
    : wxFrame(nullptr, wxID_ANY, title, pos, size) {
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
}

void MyFrame::OnButtonClick(wxCommandEvent& evt) {
    if (this->onProcessing) {
        printf("on Processing!\n");
        return;
    }

    this->onProcessing = true;

    std::vector<int> arr(50000, 5);
    arr.back() = 3;

    int n = arr.size();

    this->label->SetLabelText(wxString::Format("Sorting the array of %d elements...", n));
    this->Layout();

    auto timeStart = std::chrono::steady_clock::now();

    for (int i = 0; i < n - 1; ++i) {
        this->progressBar->SetValue(i * this->progressBar->GetRange() / (n - 2));
        // 每执行完一次内层的循环，就释放一次当前 event 事件的 loop 执行，让出时间给其他的事件执行
        wxYield();

        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }

    auto timeEnd = std::chrono::steady_clock::now();
    auto timeDuration = timeEnd - timeStart;

    this->label->SetLabelText(wxString::Format("The first number is: %d, using time %.2f", arr.front(), std::chrono::duration<double, std::milli>(timeDuration).count()));
    this->Layout();
    this->onProcessing = false;
}