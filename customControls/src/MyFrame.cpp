#include "MyFrame.h"

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    // 一个垂直方向布局的 sizer
    wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    this->mCanvas  =  new DrawingCanvas(this, wxID_ANY, wxDefaultPosition, this->FromDIP(wxSize(640, 480)));

    // 创建用户放置两个按钮的 panel
    wxPanel* buttonPanel = this->createButtonPanel(this);

    // 绑定画布的回调事件的处理函数，画布触发事件之后，会自动调用
    this->mCanvas->Bind(CANVAS_RECT_ADDED, &MyFrame::onRectAdded, this);
    this->mCanvas->Bind(CANVAS_RECT_REMOVED, &MyFrame::onRectRemoved, this);

    this->rectCount = this->mCanvas->getObjectCount();

    // 我们希望 Canvas 可以随着主窗口的大小改变而发生改变，但是 button 我们希望保持其默认的大小，不随主窗口的调整而发生变化
    // wxBoxSizer 的第二个参数就是用来控制这个选项的。在 WxSizer 当中这个参数没有实际作用
    sizer->Add(this->mCanvas, 1, wxEXPAND | wxALL, 0);
    sizer->Add(buttonPanel, 0, wxEXPAND | wxALL, 0);

    this->SetSizerAndFit(sizer);

    this->CreateStatusBar(1);
    this->SetStatusText("Ready", 0);
}

void MyFrame::OnAddButtonClick(wxCommandEvent& evt) {
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