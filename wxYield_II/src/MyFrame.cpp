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

    this->Bind(wxEVT_CLOSE_WINDOW, &MyFrame::OnClose, this);
}

void MyFrame::OnButtonClick(wxCommandEvent& evt) {
    if (!this->sortOp) {
        std::vector<int> arr(50000, 5);
        arr.back() = 3;

        this->sortOp = std::make_unique<ChunkedSort<int> >(std::move(arr));

        this->label->SetLabelText(wxString::Format("Sorting the array of %zu elements...", this->sortOp->mArr.size()));
        this->Layout();

        this->startTime = std::chrono::steady_clock::now();
        this->Bind(wxEVT_IDLE, &MyFrame::OnIdel, this);
    }
}

void MyFrame::OnClose(wxCloseEvent& evt) {
    this->Destroy();
}

void MyFrame::OnIdel(wxIdleEvent& evt) {
    if (this->sortOp) {
        if (this->sortOp->finished()) {
            std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
            auto diff = endTime - this->startTime;
            this->label->SetLabelText(wxString::Format("The first number is %d.\nProcessing time: %.2f[ms]", this->sortOp->mArr[0], 
                std::chrono::duration<double, std::milli>(diff).count()));
            this->Layout();

            this->Unbind(wxEVT_IDLE, &MyFrame::OnIdle, this);
            this->sortOp.reset();
        }
        else {
            this->sortOp->processChunk();
            this->progressBar->SetValue(this->sortOp->getProgress(this->progressBar->GetRange()));
            this->Layout();

            evt.RequestMore();
        }
    }
}