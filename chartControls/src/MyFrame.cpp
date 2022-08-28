#include "MyFrame.h"

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    // 一个垂直方向布局的 sizer
    wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    this->mChart = new ChartControl(this, wxID_ANY, wxDefaultPosition, this->FromDIP(wxSize(640, 480)));

    this->mChart->mTitle = "Important Chart";
    this->mChart->mValues = {-16.32, 150, 1000, 784.5, 800, 998};

    // 画布的大小需要随着主窗口的变化而变化
    sizer->Add(this->mChart, 1, wxEXPAND | wxALL, 0);

    this->SetSizerAndFit(sizer);

    this->CreateStatusBar(1);
    this->SetStatusText("Ready", 0);
}

void MyFrame::OnAddButtonClick(wxCommandEvent& evt) {
    if (this->mCanvas == nullptr) return;

    static std::uniform_int_distribution<int> sizeDistrib(this->FromDIP(50), this->FromDIP(100));
    std::uniform_int_distribution<int> xDistrib(0, this->mCanvas->GetSize().GetWidth());
    std::uniform_int_distribution<int> yDistrib(0, this->mCanvas->GetSize().GetHeight());
    static std::uniform_real_distribution<double> angleDistrib(0.0, M_PI * 2.0);
    static std::uniform_int_distribution<int> colorDistrib(0, 0x0ffffff);

    this->rectCount++;
    this->mCanvas->addRect(sizeDistrib(this->randomGen), sizeDistrib(this->randomGen), 
            xDistrib(randomGen), yDistrib(randomGen), 
            angleDistrib(randomGen), 
            wxColor(colorDistrib(randomGen)), 
            "rect #" + std::to_string(this->rectCount)
    );
}

void MyFrame::onRemoveButtonClick(wxCommandEvent& evt) {
    if (this->mCanvas == nullptr) return;

    this->mCanvas->removeTopRect();
}

void MyFrame::onRectAdded(wxCommandEvent& evt) {
    this->SetStatusText("Rect named + " + evt.GetString() + " added!", 0);
}

void MyFrame::onRectRemoved(wxCommandEvent& evt) {
    this->SetStatusText("Rect named + " + evt.GetString() + " removed!", 0);
}

wxPanel* MyFrame::createButtonPanel(wxWindow* parent) {
    wxPanel* panel = new wxPanel(parent);
    wxButton* addRectButton = new wxButton(panel, wxID_ANY, "Add rect");
    wxButton* removeRectButton = new wxButton(panel, wxID_ANY, "Remove rect");

    wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(addRectButton, 0, wxEXPAND | wxALL, 3);
    sizer->Add(removeRectButton, 0, wxEXPAND | wxALL, 3);

    panel->SetSizer(sizer);

    addRectButton->Bind(wxEVT_BUTTON, &MyFrame::OnAddButtonClick, this);
    removeRectButton->Bind(wxEVT_BUTTON, &MyFrame::onRemoveButtonClick, this);

    return panel;
}