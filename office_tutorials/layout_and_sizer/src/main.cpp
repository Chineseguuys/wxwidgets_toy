#include <wx/wx.h>
#include <wx/listctrl.h>

#define _SENCE_4_

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp); // 在这里构建 main()

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
};

bool MyApp::OnInit() {
    MyFrame *frame = new MyFrame("Layout Example", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}

#ifdef _SENCE_1_

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size) :
    wxFrame(nullptr, wxID_ANY, title, pos, size) {
    /*
	 这里 new 出来的对象并不需要手动的去进行 delete ,因为所有的子窗口的资源都是父窗口来进行管理的，父窗口在
	 进行析构的时候，会自动的释放所有的资源
	*/
    wxPanel *panel_top = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
    wxPanel *panel_buttom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
    wxPanel *panel_buttom_right = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));

    panel_top->SetBackgroundColour(wxColour(100, 100, 200));          // 偏蓝色
    panel_buttom->SetBackgroundColour(wxColour(100, 200, 100));       // 偏绿色
    panel_buttom_right->SetBackgroundColour(wxColour(200, 100, 100)); // 偏红色

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL); // 垂直方向的 sizer
    // 组件加入到 sizer 当中的时候，按照从上到下的顺序进行排列
    wxBoxSizer *sizer_buttom = new wxBoxSizer(wxHORIZONTAL); // 水平方向的 sizer
    // 组件加入到 sizer 当中的时候，按照从左到右的顺序进行排列

    //sizer->Add(panel, 0);	// 参数0表示，panel 不会随着 sizer 的变化而变化
    //sizer->Add(panel, 1);	// 在垂直的方向上， panel 会随着 sizer 的变化而变化
    //sizer->Add(panel, 0, wxEXPAND); // 在水平方向上随着 sizer 的变化而变化
    //sizer->Add(panel, 1, wxEXPAND); // 水平和垂直的方向上都会变化
    //sizer->Add(panel, 0, wxEXPAND | wxALL); // 在水平方向上随着 sizer 的变化而变化
    //sizer->Add(panel_top, 1, wxEXPAND | wxALL, 10); // panel 的四个边上面都有 5像素的边框
    //sizer->Add(panel_buttom, 2, wxEXPAND | wxALL, 10);
    //sizer->Add(panel, 1, wxEXPAND | wxLEFT, 5); //  只在左边有边框
    //sizer->Add(panel, 0, wxEXPAND | wxALL, 5);
    // 在水平方向上随着 sizer 的变化而变化, panel 的四个边上面都有 5像素的边框

    sizer_buttom->Add(panel_buttom, 1, wxEXPAND | wxRIGHT, 5);
    sizer_buttom->Add(panel_buttom_right, 2, wxEXPAND | wxALL, 0);

    sizer->Add(panel_top, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 5);
    sizer->Add(sizer_buttom, 1, wxEXPAND | wxALL, 5);

    this->SetSizerAndFit(sizer);
}

#endif

#ifdef _SENCE_2_

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size) :
    wxFrame(nullptr, wxID_ANY, title, pos, size) {
    /*
	 这里 new 出来的对象并不需要手动的去进行 delete ,因为所有的子窗口的资源都是父窗口来进行管理的，父窗口在
	 进行析构的时候，会自动的释放所有的资源
	*/
    wxPanel *panel_top = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
    wxPanel *panel_buttom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
    wxPanel *panel_buttom_right = new wxPanel(panel_buttom, wxID_ANY, wxDefaultPosition, wxSize(200, 100));

    panel_top->SetBackgroundColour(wxColour(100, 100, 200));
    panel_buttom->SetBackgroundColour(wxColour(100, 200, 100));
    panel_buttom_right->SetBackgroundColour(wxColour(200, 100, 100));

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL); // 垂直方向的 sizer
    // 组件加入到 sizer 当中的时候，按照从上到下的顺序进行排列
    wxBoxSizer *sizer_buttom = new wxBoxSizer(wxHORIZONTAL); // 水平方向的 sizer
    // 组件加入到 sizer 当中的时候，按照从左到右的顺序进行排列

    //sizer->Add(panel, 0);	// 参数0表示，panel 不会随着 sizer 的变化而变化
    //sizer->Add(panel, 1);	// 在垂直的方向上， panel 会随着 sizer 的变化而变化
    //sizer->Add(panel, 0, wxEXPAND); // 在水平方向上随着 sizer 的变化而变化
    //sizer->Add(panel, 1, wxEXPAND); // 水平和垂直的方向上都会变化
    //sizer->Add(panel, 0, wxEXPAND | wxALL); // 在水平方向上随着 sizer 的变化而变化
    //sizer->Add(panel_top, 1, wxEXPAND | wxALL, 10); // panel 的四个边上面都有 5像素的边框
    //sizer->Add(panel_buttom, 2, wxEXPAND | wxALL, 10);
    //sizer->Add(panel, 1, wxEXPAND | wxLEFT, 5); //  只在左边有边框
    //sizer->Add(panel, 0, wxEXPAND | wxALL, 5);
    // 在水平方向上随着 sizer 的变化而变化, panel 的四个边上面都有 5像素的边框

    //sizer_buttom->Add(panel_buttom_right, 1, wxEXPAND | wxALL, 5);
    sizer_buttom->Add(panel_buttom_right, 1, wxALIGN_BOTTOM | wxALL, 5);
    // 无论 sizer_buttom 的形状如何的变化， panel_buttom_right 都紧靠 sizer_buttom 的底部

    sizer->Add(panel_top, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 5);
    sizer->Add(panel_buttom, 1, wxEXPAND | wxALL, 5);

    panel_buttom->SetSizerAndFit(sizer_buttom);

    this->SetSizerAndFit(sizer);
}

#endif

#ifdef _SENCE_3_

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size) :
    wxFrame(nullptr, wxID_ANY, title, pos, size) {
    wxListView *list = new wxListView(this, wxID_ANY, wxDefaultPosition, wxSize(300, 200));
    list->InsertColumn(0, "Name");
    list->InsertItem(0, "Item");

    wxButton *ok_button = new wxButton(this, wxID_ANY, "ok");
    wxButton *cancel_button = new wxButton(this, wxID_ANY, "cancel");

    wxBoxSizer *s1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *s2 = new wxBoxSizer(wxHORIZONTAL);

    s1->Add(list, 1, wxEXPAND | wxALL, 5);
    s2->Add(ok_button, 0, wxRIGHT, 5);
    s2->Add(cancel_button, 0);

    s1->Add(s2, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 5);

    this->SetSizerAndFit(s1);
}

#endif

#ifdef _SENCE_4_
MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size) :
    wxFrame(nullptr, wxID_ANY, title, pos, size) {
    wxBoxSizer *h_box = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *v_box_10b = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *v_box_2b = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *v_box_16b = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *v_box_8b = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *base10_txt = new wxStaticText(this, wxID_ANY, wxT("10 进制:"));
    wxTextCtrl *  base10_input = new wxTextCtrl(this, wxID_ANY, wxT(""));

    wxStaticText *base2_txt = new wxStaticText(this, wxID_ANY, wxT("2  进制:"));
    wxTextCtrl *  base2_input = new wxTextCtrl(this, wxID_ANY, wxT(""));

    wxStaticText *base8_txt = new wxStaticText(this, wxID_ANY, wxT("8  进制:"));
    wxTextCtrl *  base8_input = new wxTextCtrl(this, wxID_ANY, wxT(""));

    wxStaticText *base16_txt = new wxStaticText(this, wxID_ANY, wxT("16 进制:"));
    wxTextCtrl *  base16_input = new wxTextCtrl(this, wxID_ANY, wxT(""));
    v_box_10b->Add(base10_txt, 0, wxTOP | wxRIGHT | wxLEFT | wxBOTTOM | wxALIGN_CENTRE, 8);
    v_box_10b->Add(base10_input, 1, wxRIGHT | wxALIGN_CENTRE, 8);

    v_box_2b->Add(base2_txt, 0, wxTOP | wxRIGHT | wxLEFT | wxBOTTOM | wxALIGN_CENTRE, 8);
    v_box_2b->Add(base2_input, 1, wxRIGHT | wxALIGN_CENTRE, 8);

    v_box_8b->Add(base8_txt, 0, wxTOP | wxRIGHT | wxLEFT | wxBOTTOM | wxALIGN_CENTRE, 8);
    v_box_8b->Add(base8_input, 1, wxRIGHT | wxALIGN_CENTRE, 8);

    v_box_16b->Add(base16_txt, 0, wxTOP | wxRIGHT | wxLEFT | wxBOTTOM | wxALIGN_CENTRE, 8);
    v_box_16b->Add(base16_input, 1, wxRIGHT | wxALIGN_CENTRE, 8);

    h_box->Add(v_box_10b, 1, wxEXPAND | wxALL);
    h_box->Add(v_box_2b, 1, wxEXPAND | wxALL);
    h_box->Add(v_box_8b, 1, wxEXPAND | wxALL);
    h_box->Add(v_box_16b, 1, wxEXPAND | wxALL);

    this->SetSizerAndFit(h_box);
}
#endif