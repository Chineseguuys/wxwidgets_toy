#include "cMain.h"
#include "delete_line.h"
#include "mondrian.xpm" // icon image encoded into c++ arrays

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
    //    EVT_BUTTON(10001, cMain::OnButtonClicked)
    EVT_TEXT(10001, cMain::OnTextCtrl_TextChanged)
        wxEND_EVENT_TABLE()

            cMain::cMain() :
    wxFrame(nullptr, wxID_ANY, "One Line", wxPoint(30, 30), wxSize(800, 600)) {
    // m_btn1 = new wxButton(this, 10001, "Click Me", wxPoint(10,10), wxSize(150, 50));
    SetIcon(wxIcon(mondrian_xpm)); // 设置底栏当中的图标，如果不设置的话，底栏上面是一个半透明的方块
    wxGridSizer *grid = new wxGridSizer(1, 2, 0, 0);

    m_tc1 = new wxTextCtrl(this, 10001, "",
                           wxPoint(10, 60), wxSize(300, 300),
                           wxTE_MULTILINE);

    m_list1 = new wxTextCtrl(this, wxID_ANY, "",
                             wxPoint(10, 370), wxSize(300, 300),            // 如果设置了 grid，那么位置的设置就实际上失效了
                             wxTE_READONLY | wxTE_WORDWRAP | wxTE_MULTILINE // 只读|句子自动换行|多行显示
    );

    grid->Add(m_tc1, 1, wxEXPAND | wxALL); // 自动扩展 | 占领整个格子
    grid->Add(m_list1, 1, wxEXPAND | wxALL);

    this->SetSizer(grid);
    grid->Layout();
}

cMain::~cMain() {
}

void cMain::OnButtonClicked(wxCommandEvent &evt) {
    evt.Skip();
}

void cMain::OnTextCtrl_TextChanged(wxCommandEvent &evt) {
    // printf("cMain::OnTextCtrl_TextChanged() have been called\n");
    wxString texts = m_tc1->GetValue();
    // printf("texts's len = %zu\n", texts.length());
    // printf("texts's size = %zu\n", texts.size());
    // std::wstring raw_string( texts.wc_str() );
    // wxString new_string = wxString( delete_lines(raw_string));
    wxString new_string = delete_lines_wxString(texts);
    m_list1->Clear();
    m_list1->AppendText(new_string);

    // 使用系统的剪切板， wxTheClipboard 是一个宏，返回一个剪切板的对象
    // 全局只有一个剪切板
    // Open() 函数获取剪切板的 所有权，Close() 释放所有权
    if (wxTheClipboard->Open()) {
        wxTheClipboard->Clear();
        wxTheClipboard->SetData(new wxTextDataObject(new_string));
        wxTheClipboard->Close();
    }

    evt.Skip();
}
